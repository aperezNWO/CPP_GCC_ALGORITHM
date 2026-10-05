/*
    // WINDOWS
    g++ -std=c++17 -O3 CppWebServer.cpp -I. Dijkstra.cpp -o cpp_web_server.exe -mconsole -lws2_32
    
    // LINUX
    g++ -std=c++17 -O3 CppWebServer.cpp -I. Dijkstra.cpp -o cpp_web_server -lpthread
    
*/
#include "httplib.h"
#include "FractalEngine.cpp"
#include "Dijkstra.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

std::map<string, string> configMap;

struct EndpointInfo {
    std::string endpointName;
    std::string endpointDescription;
};

// Key is a string identifier (e.g., "HEALTH_ENDPOINT")
std::unordered_map<std::string, EndpointInfo> endpointDictionary = {
    {"HEALTH_ENDPOINT"         , {"/health"                     , "Print all endpoints"}},
    {"PING_ENDPOINT"           , {"/zero"                       , "Render workaround"}},
    {"APP_VERSION_ENDPOINT"    , {"/getAppVersion"                 , "Get Application Version"}},
    {"STD_VERSION_ENDPOINT"    , {"/getSTDVersion"              , "Get Standard C++ Version"}},
    {"SERVER_VERSION_ENDPOINT ", {"/getServerVersion"           , "Get Http Server Version"}},
    {"FRACTAL_ENDPOINT"        , {"/api/fractals/generate"      , "Fractal Generation Endpoint"}},
    {"DIJKSTRA_ENDPOINT"       , {"/GenerateRandomVertex_CPP"   , "Generate Random Vertex via Dijkstra"}}
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
        std::string jsonResponse = "{\n  \"server\": \"Server Working!\",\n  \"endpoints\": [\n";
        
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
	    int p_vertexSize = 9;
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