/*
    // WINDOWS
    g++ -std=c++17 -O3 CppWebServer.cpp -I. TFileManager.cpp Dijkstra.cpp SortBenchMark.cpp  Sudoku.cpp RegExManager.cpp -o cpp_web_server.exe -mconsole -lws2_32
    
    // LINUX -- DOCKER (NO .EXE EXTENSION FOR DOCKER!!!)
    	// EDIT DOCKER FILE TO ADD NEEDED FILES
     		 COPY --from=builder /app/cdcatalog.xml /app/cdcatalog.xml  	
   			 COPY --from=builder /app/Algorithm.ini /app/Algorithm.ini
			 COPY --from=builder /app/cpp_web_server /app/cpp_web_server
        // COPY C++ COMMAND TO DOCKER FILE	
			 RUN  <COMMAND_LINE>		 
        g++ -std=c++17 -O3 CppWebServer.cpp -I. TFileManager.cpp Dijkstra.cpp SortBenchMark.cpp  Sudoku.cpp RegExManager.cpp -o cpp_web_server -lpthread 
    
*/
#include "httplib.h"
#include "FractalEngine.cpp"
#include "SortBenchMark.h"
#include "Dijkstra.h"
#include "Sudoku.cpp"
#include "RegExManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <filesystem>

std::map<string, string> configMap;

struct EndpointInfo {
    std::string endpointName;
    std::string endpointDescription;
};

// Key is a string identifier (e.g., "HEALTH_ENDPOINT")
std::unordered_map<std::string, EndpointInfo> endpointDictionary = {
    {"HEALTH_ENDPOINT"            , {"/health"                     , "Print all endpoints"}},
    {"PING_ENDPOINT"              , {"/zero"                       , "Render workaround"}},
    {"APP_VERSION_ENDPOINT"       , {"/getAppVersion"              , "Get Application Version"}},
    {"STD_VERSION_ENDPOINT"       , {"/getSTDVersion"              , "Get Standard C++ Version"}},
    {"SERVER_VERSION_ENDPOINT"    , {"/getServerVersion"           , "Get Http Server Version"}},
    {"FRACTAL_ENDPOINT"           , {"/api/fractals/generate"      , "Fractal Generation Endpoint"}},
    {"DIJKSTRA_ENDPOINT"          , {"/api/algorithm/GenerateRandomVertex_CPP"   , "Generate Random Vertex via Dijkstra"}},
    {"SORT_ENDPOINT"              , {"/api/algorithm/GetSort_CPP"                , "Benchmark Bubble Sort and Quick Sort Algorithms"}},
    {"SUDOKU_GENERATE_ENDPOINT"   , {"/api/algorithm/Sudoku_Generate_CPP"        , "Generate a random sudoku board ready for fill"}},
    {"SUDOKU_SOLVE_ENDPOINT"      , {"/api/algorithm/Sudoku_Solve_CPP"           , "Solve a random renerated sudoku board"}},
    {"REGEX_EVAL_ENDPOINT"        , {"/api/algorithm/Regex_Eval_CPP"             , "Evaluate a regular expression from a existing xml file"}},
};

//
const char* GetCPPSTDVersion(long int cppVersion)	
{
	switch (cppVersion) {
	        case 199711L: return "C++98/C++03";
	        case 201103L: return "C++11";
	        case 201402L: return "C++14";
	        case 201703L: return "C++17";
	        case 202002L: return "C++20";
	        case 202302L: return "C++23";
	        default: return "Unknown C++ Standard";
	}
}

// Get HTTP Server Version (cpp-httplib)
const char* GetCPPHttpVersion()
{
    #ifdef CPPHTTPLIB_VERSION
        return CPPHTTPLIB_VERSION;
    #else
        return "Unknown cpp-httplib Version";
    #endif
}

//
int ReadConfigFile(const char* fileName)
{
	 // Open the configuration file
	std::ifstream configFile(fileName);

	// Check if the file is opened successfully
	if (!configFile.is_open()) {
		std::cerr << "Error opening the configuration file." << std::endl;
		return 1;
	}

	// Read the file line by line
	std::string line;
	while (std::getline(configFile, line)) {
		// Skip empty lines or lines starting with '#' (comments)
		if (line.empty() || line[0] == '#') {
			continue;
		}

		// Split the line into key and value
		std::istringstream iss(line);
		std::string key, value;
		if (std::getline(iss, key, '=') && std::getline(iss, value))
		{
			// Trim leading and trailing whitespaces from key and value
			key.erase(0, key.find_first_not_of(" \t"));
			key.erase(key.find_last_not_of(" \t") + 1);
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);

			// Insert key-value pair into the map
			configMap[key] = value;
		}
	}

	// Close the configuration file
	configFile.close();

	//
	return 0;
}	

//
void ReplaceAll(std::string &str, const std::string &from, const std::string &to) 
{
    //
    size_t startPos = 0;
    //
    while ((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length(); // Move to the next position after replacement
    }
}

//
vector<string> StringSplit(const char* p_inputString, std::string p_delimiter)
{
	//
	std::string s(p_inputString);
	//
	std::vector<std::string> outputArr;
	size_t pos = 0;
	std::string token;
	//
	while ((pos = s.find(p_delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + p_delimiter.length());
		outputArr.push_back(token);
	}
	outputArr.push_back(s);
	//
	return outputArr;
};

////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	//
    httplib::Server svr;

    // HTTP Interceptor & Global CORS Middleware
    svr.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        // 1. Request Logging Interceptor
        std::cout << "[Interceptor] " << req.method << " " << req.path << std::endl;

        // 2. Global CORS Header Policy
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Origin, Content-Type, Accept, Authorization");
        res.set_header("Access-Control-Allow-Credentials", "true");

        // 3. Handle browser preflight OPTIONS requests automatically
        if (req.method == "OPTIONS") {
            res.status = 204; // No Content
            return httplib::Server::HandlerResponse::Handled;
        }

        // Proceed to route handlers
        return httplib::Server::HandlerResponse::Unhandled;
    });

    // Ping / Zero Endpoint
    svr.Get(endpointDictionary["PING_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
    });

    // Server Diagnostics (Health Endpoint listing all routes)
    svr.Get(endpointDictionary["HEALTH_ENDPOINT"].endpointName.c_str(), [&](const httplib::Request&, httplib::Response& res) {
    	//
		std::string webServerVersion = GetCPPHttpVersion();
        //
		std::string jsonResponse     = "{\n  \"server\": \"C++ Http Server 'cpp-httplib' - v[" + webServerVersion  + "] Working!\",\n  \"endpoints\": [\n";
        //
        size_t count = 0;
        for (const auto& pair : endpointDictionary) {
            const std::string& key = pair.first;
            const EndpointInfo& info = pair.second;
            
            std::string comma = (++count < endpointDictionary.size()) ? "," : "";

            jsonResponse += "    {\n";
            jsonResponse += "      \"key\": \"" + key + "\",\n";
            jsonResponse += "      \"path\": \"" + info.endpointName + "\",\n";
            jsonResponse += "      \"description\": \"" + info.endpointDescription + "\"\n";
            jsonResponse += "    }" + comma + "\n";
        }
        
        jsonResponse += "  ]\n}";
        
        res.set_content(jsonResponse, "application/json");
        res.status = 200;
    });
    
    // Get Standard C++ Version
    svr.Get(endpointDictionary["STD_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
    		std::string jsonResponse  = GetCPPSTDVersion(__cplusplus); 
            res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });
    
        
    // Get Application Version
    svr.Get(endpointDictionary["APP_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
    	
    		//
			ReadConfigFile("Algorithm.ini");

			//
    		std::string jsonResponse  = configMap["DLL_VERSION"]; 
    		
    		//
            res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });
    
	// Get Http Server Version
    svr.Get(endpointDictionary["SERVER_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
    		std::string jsonResponse  = GetCPPHttpVersion();
            res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });

    // Fractal Generation Endpoint
    svr.Get(endpointDictionary["FRACTAL_ENDPOINT"].endpointName.c_str(), [&](const httplib::Request& req, httplib::Response& res) {
    	//
    	FractalEngine engine;
   
        try {
            if (!req.has_param("kind")) {
                res.status = 400;
                res.set_content("{\"error\":{\"type\":\"ValidationException\",\"message\":\"Missing or invalid 'kind' parameter.\"}}", "application/json");
                return;
            }

            int kindParam = std::stoi(req.get_param_value("kind"));
            FractalKind fractalKind = FractalKind::mandelbrot;
            
            switch (kindParam) {
                case 1: fractalKind = FractalKind::mandelbrot; break;
                case 2: fractalKind = FractalKind::julia; break;
                case 3: fractalKind = FractalKind::leaf; break;
                default:
                    res.status = 400;
                    res.set_content("{\"error\":{\"type\":\"ValidationException\",\"message\":\"Invalid fractal kind value.\"}}", "application/json");
                    return;
            }

            Bounds defaultBounds = (fractalKind == FractalKind::mandelbrot)
                ? Bounds{-2.0, 1.0, -1.2, 1.2}
                : Bounds{-1.5, 1.5, -1.5, 1.5};

            Bounds bounds = defaultBounds;
            if (req.has_param("xMin") && req.has_param("xMax") && req.has_param("yMin") && req.has_param("yMax")) {
                bounds = Bounds{
                    std::stod(req.get_param_value("xMin")),
                    std::stod(req.get_param_value("xMax")),
                    std::stod(req.get_param_value("yMin")),
                    std::stod(req.get_param_value("yMax"))
                };
            }

            int maxIterations = 500;
            if (req.has_param("maxIterations")) {
                maxIterations = std::stoi(req.get_param_value("maxIterations"));
            }

            // Generate fractal points using FractalEngine
            std::vector<FractalPoint> points = engine.getFractal(fractalKind, bounds, maxIterations);

            // Serialize points to JSON array
            std::string jsonResponse = "[";
            for (size_t i = 0; i < points.size(); ++i) {
                jsonResponse += points[i].toJson();
                if (i + 1 < points.size()) jsonResponse += ",";
            }
            jsonResponse += "]";

            res.set_content(jsonResponse, "application/json");
            res.status = 200;

        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":{\"type\":\"ServerError\",\"message\":\"An unexpected internal server error occurred.\"}}", "application/json");
        }
    });

    svr.Get(endpointDictionary["DIJKSTRA_ENDPOINT"].endpointName.c_str(), [](const httplib::Request& req, httplib::Response& res) {
    	
  	    // Default values if query parameters are omitted
	    int p_vertexSize  = 9;
	    int p_sourcePoint = 0;
	
	    // Check and parse p_vertexSize from query string
	    if (req.has_param("p_vertexSize")) {
	        try {
	            p_vertexSize = std::stoi(req.get_param_value("p_vertexSize"));
	        } catch (...) {
	            // Fallback or handle invalid integer format if desired
	        }
	    }
	
	    // Check and parse p_sourcePoint from query string
	    if (req.has_param("p_sourcePoint")) {
	        try {
	            p_sourcePoint = std::stoi(req.get_param_value("p_sourcePoint"));
	        } catch (...) {
	            // Fallback or handle invalid integer format if desired
	        }
	    }
	
	    std::unique_ptr<Dijkstra> uniquePtr = std::make_unique<Dijkstra>();
	    
	    // Note: avoid 'static std::string response' here if multiple concurrent requests 
	    // might overwrite it; a local variable is safer for multi-threaded request handling.
	    std::string response = uniquePtr->GetRandomPoints(p_vertexSize, p_sourcePoint);
	    
	    // Define the UTF-8 byte sequence for ■
	    std::string separator = "\xE2\x96\xA0";
	    
	    // Replace all occurrences of "~" with "■"
	    ReplaceAll(response, "~", separator);
	
	    res.set_content(response, "text/plain; charset=utf-8");
	    res.status = 200;
	});

    // 1 = BUBBLE SORT , 2 = QUICK SORT
    // http://localhost:8080/api/algorithm/GetSort_CPP?p_sortAlgoritm=1&p_unsortedList=23|7|10|16|1|4|22|2|6|24|8|14|11|15|21|13|19|20|18|0|17|5|3|9|12
    svr.Get(endpointDictionary["SORT_ENDPOINT"].endpointName.c_str(), [](const httplib::Request& req, httplib::Response& res) {
	    	
	  	// Default values if query parameters are omitted
	    std::string response       = "";
	    int         p_sortAlgoritm = 0;
	    std::string p_unsortedList = ""; // Change from const char* to std::string
	
	    // Check and parse p_sortAlgoritm from query string
	    if (req.has_param("p_sortAlgoritm")) {
	        try {
	            p_sortAlgoritm = std::stoi(req.get_param_value("p_sortAlgoritm"));
	        } catch (const std::exception& e) {
	            std::cout << "[Error occurred] " << e.what() << std::endl;	
	        }
	    }
	
	    // Check and parse p_unsortedList from query string
	    if (req.has_param("p_unsortedList")) {
	        try {
	            // Store it safely in a persistent std::string object
	            p_unsortedList = req.get_param_value("p_unsortedList");
	            
	            std::cout << "unsorted list : " << p_unsortedList << std::endl;
	        } catch (const std::exception& e) {
	            std::cout << "[Error occurred] " << e.what() << std::endl;	
	        }
	    }
	
	    try {
	        FormatType format = FormatType::HTML; 
	        
	        // Pass the std::string (or its .c_str() safely while p_unsortedList is alive)
	        SortBenchMark benchmark(p_unsortedList.c_str(), format);
	        
	        response = benchmark.GetSort(p_sortAlgoritm);
	        
	        std::string separator = "\xE2\x96\xA0";
	        ReplaceAll(response, "~", separator);
	
	    } catch (const std::exception& e) {
	        std::cout << "[Error occurred] " << e.what() << std::endl;	
	    }
	    
	    res.set_content(response, "text/plain; charset=utf-8");
	    res.status = 200;
	});

	///////////////////////////////////////////////	
	// SUDOKU ENDPOINTS
	///////////////////////////////////////////////	
   	// http://localhost:8080/api/algorithm/Sudoku_Generate_CPP
	svr.Get(endpointDictionary["SUDOKU_GENERATE_ENDPOINT"].endpointName.c_str(), [](const httplib::Request& req, httplib::Response& res) {
	    	
	  	// Default values if query parameters are omitted
	    std::string response       = "";
	  	
	    try {
	        
			//
			const static int   N = 9;
			int                K = 20;
	
			//
			std::unique_ptr<SudokuGenerator> uniquePtr = std::make_unique<SudokuGenerator>(N, K);
			string           str_matrix                = uniquePtr->Run();
			
			//
			response                                   = str_matrix;
		
	    } catch (const std::exception& e) {
	        std::cout << "[Error occurred] " << e.what() << std::endl;	
	    }
	    
	    //
	    res.set_content(response, "text/plain; charset=utf-8");
	    res.status = 200;
	});
	/*
	DLL_EXPORT const char*  Sudoku_Solve_CPP(char* p_matrix)
	{
	    //
		Algorithm*   algorithm     = new Algorithm(false);
		string       str_p_matrix  = p_matrix;
		FileManager* fileManager   = new FileManager();

		//
		std::map<std::string, std::string> replaceMap;

		// Inserting values into the map
		replaceMap["["]      = "";
		replaceMap["]"]      = "";
		replaceMap["},"]     = "|";
		replaceMap["{"]      = "";
		//replaceMap["}"]      = "";  // ERROR EN ESTE REEMPLAZO
		// SE DEBE REEMPLAZAR ESPECIFICMENTE MAS ABAJO

		// Iterating through the map
		for (const auto& pair : replaceMap) {
			//
			algorithm->ReplaceAll(str_p_matrix, pair.first, pair.second);
		}
		//
		algorithm->ReplaceAll(str_p_matrix, "}", "");

		//
		const char* str_p_matrix_c_str     = str_p_matrix.c_str();
		//fileManager->SaveLineToFile("\nSudoku To Solve\n","SudokuGenerated.txt");

		//
		const static int   N          = 9;
		int                grid[N][N] =
			{
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1} 
			};

		//
		vector<string>   str_p_matrix_rows = algorithm->StringSplit(str_p_matrix_c_str,"|");
		//
		int i = 0;
		//
		for (string row : str_p_matrix_rows) {
			//
			//fileManager->SaveLineToFile(row,"SudokuGenerated.txt");
			//
			int j = 0;
			//				
			vector<string>   str_p_matrix_cols = algorithm->StringSplit(row.c_str(),",");
			//
			for (string col : str_p_matrix_cols) {
				//
				int num = stoi(col);
				//
				grid[i][j] = num;
				//
				j++;	
			}
			//
			i++;
		}

		//
		std::unique_ptr<SudokuSolver> uniquePtrSolve = std::make_unique<SudokuSolver>();
		string           str_matrix                  = uniquePtrSolve->Solve(grid);

		//
		//fileManager->SaveLineToFile("\nSudoku Solved \n","SudokuSolved.txt");
		//
		return str_matrix.c_str();
	}
	*/   
	// http://localhost:8080/api/algorithm/Sudoku_Solve_CPP?p_matrix=[{0,0,0,0,4,5,6,7,8},{3,4,5,6,7,8,2,9,1},{6,7,8,1,2,9,3,4,5},{2,3,7,8,9,1,5,6,4},{5,6,9,2,3,4,8,1,7},{4,8,1,5,6,7,9,3,2},{1,2,6,4,5,3,7,8,9},{0,0,0,0,0,0,0,0,3},{0,0,0,0,0,0,0,0,6
	svr.Get(endpointDictionary["SUDOKU_SOLVE_ENDPOINT"].endpointName.c_str(), [](const httplib::Request& req, httplib::Response& res) {

		// Default values if query parameters are omitted
	    std::string response       = "";
	    std::string p_matrix       = "";
	    
	    // Check and parse p_matrix from query string
	    if (req.has_param("p_matrix")) {
	        try {
	            //
				p_matrix = req.get_param_value("p_matrix");
	            
	            //
				//FileManager* fileManager   = new FileManager();

				//
				std::map<std::string, std::string> replaceMap;
		
				// Inserting values into the map
				replaceMap["["]      = "";
				replaceMap["]"]      = "";
				replaceMap["},"]     = "|";
				replaceMap["{"]      = "";
				//replaceMap["}"]      = "";  // ERROR EN ESTE REEMPLAZO
				// SE DEBE REEMPLAZAR ESPECIFICMENTE MAS ABAJO
		
				// Iterating through the map
				for (const auto& pair : replaceMap) {
					//
					ReplaceAll(p_matrix, pair.first, pair.second);
				}
				//
				ReplaceAll(p_matrix, "}", "");
		
				//
				const char* str_p_matrix_c_str     = p_matrix.c_str();
				//fileManager->SaveLineToFile("\nSudoku To Solve\n","SudokuGenerated.txt");
		
				//
				const static int   N          = 9;
				int                grid[N][N] =
					{
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1},
						{-1, -1, -1, -1, -1, -1, -1, -1, -1} 
					};
		
				//
				vector<string>   str_p_matrix_rows = StringSplit(str_p_matrix_c_str,"|");
				//
				int i = 0;
				//
				for (string row : str_p_matrix_rows) {
					//
					//fileManager->SaveLineToFile(row,"SudokuGenerated.txt");
					//
					int j = 0;
					//				
					vector<string>   str_p_matrix_cols = StringSplit(row.c_str(),",");
					//
					for (string col : str_p_matrix_cols) {
						//
						int num = stoi(col);
						//
						grid[i][j] = num;
						//
						j++;	
					}
					//
					i++;
				}
		
				//
				std::unique_ptr<SudokuSolver> uniquePtrSolve = std::make_unique<SudokuSolver>();
				string           str_matrix_output           = uniquePtrSolve->Solve(grid);
				
				//
				response         = str_matrix_output;
		
	        } catch (const std::exception& e) {
	            std::cout << "[Error occurred] " << e.what() << std::endl;	
	        }
	    }
	    
	    //
	    res.set_content(response, "text/plain; charset=utf-8");
	    res.status = 200;
	});    	

	///////////////////////////////////////////////	
	// REGULAR EXPRESSIONS
	///////////////////////////////////////////////
	/*
	DLL_EXPORT const char*  RegExManager_RegExEval(char* p_tagSearch, char* p_textSearch)
	{
		//
		std::unique_ptr<RegExManager> uniquePtr = std::make_unique<RegExManager>();
		//
		static std::string response; 
		response  = uniquePtr->RegExEval(p_tagSearch, p_textSearch);
		
		//
		return response.c_str();
	}  
	*/
	// http://localhost:8080/api/algorithm/Regex_Eval_CPP?p_tagSearch=company&p_textSearch=BMG 
	
	svr.Get(endpointDictionary["REGEX_EVAL_ENDPOINT"].endpointName.c_str(), [](const httplib::Request& req, httplib::Response& res) {
	    	

	
	  	// Default values if query parameters are omitted
	    std::string response          = "";
		std::string p_tagSearch       = "";
		std::string p_textSearch      = "";
	  	
	    try {
	        
	        /*
	        for (const auto& entry : std::filesystem::directory_iterator("/app")) {
		    	std::cout << "[Container File] " << entry.path().filename().string() << std::endl;
			}*/
			
		    // Check and parse p_sortAlgoritm from query string
		    if (req.has_param("p_tagSearch")) {
		        try {
		            //
					p_tagSearch = req.get_param_value("p_tagSearch");
		            //
		            std::cout << "p_tagSearch: " << p_tagSearch << std::endl;
		        } catch (const std::exception& e) {
		            std::cout << "[Error occurred] " << e.what() << std::endl;	
		        }
		    }
		
		    // Check and parse p_unsortedList from query string
		    if (req.has_param("p_textSearch")) {
		        try {
		            // Store it safely in a persistent std::string object
		            p_textSearch = req.get_param_value("p_textSearch");
		            
		            std::cout << "p_textSearch: " << p_textSearch << std::endl;
		        } catch (const std::exception& e) {
		            std::cout << "[Error occurred] " << e.what() << std::endl;	
		        }
		    }
			
			//
			try {
				
				std::unique_ptr<RegExManager> uniquePtr = std::make_unique<RegExManager>();
				
				// If it strictly requires raw char* (non-const), you can use &str[0] 
				// provided the string is not empty:
				response = uniquePtr->RegExEval(&p_tagSearch[0], &p_textSearch[0]);
		        
		        //
				std::cout << "Response : " << response << std::endl;
				
	        } catch (const std::exception& e) {
	            std::cout << "[Error occurred] " << e.what() << std::endl;	
	        }
		
	    } catch (const std::exception& e) {
	        std::cout << "[Error occurred] " << e.what() << std::endl;	
	    }
	    
	    //
	    res.set_content(response, "text/plain; charset=utf-8");
	    res.status = 200;
	});
	
	///////////////////////////////////////////////
	//PROGRAM MAIN ENTRANCE
	///////////////////////////////////////////////
	
    int port = 8080;
    if (getenv("PORT")) {
        port = std::stoi(getenv("PORT"));
    }

    std::cout << "C++ REST Server listening on port " << port << "...\n";
    svr.listen("0.0.0.0", port);

    return 0;
}