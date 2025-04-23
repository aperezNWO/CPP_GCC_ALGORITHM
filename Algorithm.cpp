///////////////////////////////////////////////////////////////////////////
// ALGORITHM.DLL
///////////////////////////////////////////////////////////////////////////
/*

		-- [_] TOOLCHAIN : C:\msys64\ucrt64\bin.
*/

///////////////////////////////////////////////////////////////////////////
// CONFIGURACION DLL
///////////////////////////////////////////////////////////////////////////
/*
	1) SELECCIONAR ARCHIVO *.CPP DLL
	2) TERMINAL > RUN BUILD TASK > (3) (DLL) C/C++: g++.exe build active file
	3) SE GENERA ARCHIVO "ALGORITMO.DLL" STATIC DLL X64
	4) DISTRIBUIR LOS SIGUIENTES ARCHIVOS  EN CARPETA "/_DIST":

		a) Algorithm.dll
		b) Algorithm.ini
		c) cdCatalog.xml
*/
///////////////////////////////////////////////////////////////////////////


#include "include/Algorithm.h"
#include "include/Dijkstra.h"
#include "include/SortBenchMark.h"
#include "include/RegExManager.h"
#include "include/Sudoku.cpp"

#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall

	Algorithm::Algorithm()
	{
		 //
		 ReadConfigFile();
	}
	//
	Algorithm::~Algorithm()
	{
		//
	}
	//
	string Algorithm::HtmlEncode(const std::string& input)
	{
		//
		std::ostringstream encoded;
		//
		for (char c : input) {
			//
			if (std::isspace(c))
			{
				encoded << "&nbsp;";
			}
			//
			switch (c) {
				case '&': encoded << "&amp;";
					break;
				case '<': encoded << "&lt;";
					break;
				case '>': encoded << "&gt;";
					break;
				case '\"': encoded << "&quot;";
					break;
				case '\'': encoded << "&apos;";
					break;
				case '\n': encoded << "<br/>";
					break;
				case '\t': encoded << "&nbsp;";
					break;
				case '[': encoded << "<mark>";
					break;
				case ']': encoded << "</mark>";
					break;
				default: encoded << c;
			}
		}
		return encoded.str();
	}
	//
	string Algorithm::StringTrim(const std::string& str)
	{
		//
		size_t start = str.find_first_not_of(" \t\n\r");   // Find the first non-whitespace character
		size_t end   = str.find_last_not_of(" \t\n\r");    // Find the last non-whitespace character
		//
		if (start == std::string::npos || end == std::string::npos) {
			// The string is empty or contains only whitespaces
			return "";
		}
		//
		return str.substr(start, end - start + 1);
	};
	//
	vector<string> Algorithm::StringSplit(const char* p_inputString, std::string p_delimiter)
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
	//
	vector<int> Algorithm::FisherYates(int count, vector<int> deck)
	{
	   //
	   for (short i = 0; i <= count - 2; i++)
	   {
		   // Create a random number generator engine
		   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		   std::default_random_engine generator(seed);
		   std::uniform_int_distribution<int> dist(0, count - i);
		   int j         = dist(generator);

		   //
		   if (j > 0)
		   {
			   int curVal  = deck[i];
			   deck[i]     = deck[i + j];
			   deck[i + j] = curVal;
		   }
	   }
	   //
	   for (short i = count - 1; i >= 1; i--)
	   {
		   // Seed the generator with a random value om a hardware device
		   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		   std::default_random_engine generator(seed);
		   std::uniform_int_distribution<int> dist(0, i + 1);
		   int j              = dist(generator);

		   //
		   if (j != i)
		   {
			   int curVal = deck[i];
			   deck[i]    = deck[j];
			   deck[j]    = curVal;
		   }
	   }
	   //
	   return deck;
	}
	//
	int Algorithm::ReadConfigFile()
	{
		 // Open the configuration file
		std::ifstream configFile("Algorithm.ini");

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
				this->configMap[key] = value;
			}
		}

		// Close the configuration file
		configFile.close();

		//
		return 0;
	}

	void Algorithm::ReplaceAll(std::string &str, const std::string &from, const std::string &to) 
	{
		//
		size_t startPos = 0;
		//
		while ((startPos = str.find(from, startPos)) != std::string::npos) {
			str.replace(startPos, from.length(), to);
			startPos += to.length(); // Move to the next position after replacement
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// ENTRY POINTS
	///////////////////////////////////////////////////////////////////////////
	// DUJKSTRA
	DLL_EXPORT const char* Dijkstra_GenerateRandomVertex_CPP(int p_vertexSize, int p_sourcePoint)
	{
		//
		std::unique_ptr<Dijkstra> uniquePtr = std::make_unique<Dijkstra>();
		//
		return uniquePtr->GetRandomPoints(p_vertexSize, p_sourcePoint).c_str();
	};
	// SORT BENCHMARK
	DLL_EXPORT const char* SortBenchMark_GetSort_CPP(int p_sortAlgoritm, char* p_unsortedList)
	{
		//
		std::unique_ptr<SortBenchMark> uniquePtr = std::make_unique<SortBenchMark>(
					p_unsortedList
		);
		return uniquePtr->GetSort(p_sortAlgoritm).c_str();
	};
	// REGULAR EXPRESSIONS
	DLL_EXPORT const char*  RegExManager_RegExEval(char* p_tagSearch, char* p_textSearch)
	{
		//
		std::unique_ptr<RegExManager> uniquePtr = std::make_unique<RegExManager>();
		//
		return uniquePtr->RegExEval(p_tagSearch, p_textSearch).c_str();
	}
	// SUDOKU - 64 bit version
	DLL_EXPORT const char* Sudoku_Generate_CPP_64()
	{
		//
		const static int   N = 9;
		int                K = 20;

		//
		std::unique_ptr<SudokuGenerator> uniquePtr = std::make_unique<SudokuGenerator>(N, K);
		string           str_matrix                = uniquePtr->Run();

		//
		return str_matrix.c_str();
	}
	// SUDOKU
	DLL_EXPORT const char*  Sudoku_Generate_CPP()
	{
		//
		const static int   N = 9;
		int                K = 20;

		//
		std::unique_ptr<SudokuGenerator> uniquePtr = std::make_unique<SudokuGenerator>(N, K);
		string           str_matrix                = uniquePtr->Run();

		//
		return str_matrix.c_str();
	}
	// SUDOKU
	DLL_EXPORT const char*  Sudoku_Solve_CPP(char* p_matrix)
	{
		//
		// [{2,0,8,5,1,3,4,6,7},{0,3,6,2,4,0,1,9,8},{0,0,0,8,6,0,2,5,3},{3,2,5,4,7,6,0,1,9},{0,6,9,1,8,2,3,7,5},{8,7,0,3,0,5,0,0,2},{0,4,7,9,2,8,0,3,1},{1,8,0,7,5,4,0,2,6},{9,5,2,0,0,1,7,0,4}]

		//
		Algorithm*   algorithm     = new Algorithm();
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
		fileManager->SaveLineToFile("\nSudoku To Solve\n","Sudoku.txt");

		//
		const static int   N          = 9;
		int                grid[N][N] =
			{{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1}};
	/*
			{{0, 4, 0, 1, 0, 2, 6, 5, 7},
			{2, 7, 3, 6, 8, 5, 4, 1, 9},
			{0, 6, 0, 9, 0, 4, 2, 8, 3},
			{0, 9, 0, 3, 2, 8, 7, 0, 5},
			{0, 5, 7, 4, 0, 9, 0, 6, 2},
			{4, 2, 8, 5, 6, 7, 3, 9, 1},
			{0, 3, 2, 0, 0, 1, 0, 7, 4},
			{7, 1, 4, 2, 0, 6, 9, 3, 8},
			{0, 8, 0, 7, 4, 0, 1, 2, 6}};
	*/
		//
		vector<string>   str_p_matrix_rows = algorithm->StringSplit(str_p_matrix_c_str,"|");
		//
		int i = 0;
		//
		for (string row : str_p_matrix_rows) {
			//
			fileManager->SaveLineToFile(row,"Sudoku.txt");
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
		std::unique_ptr<SudokuSolver> uniquePtr = std::make_unique<SudokuSolver>();
		string           str_matrix             = uniquePtr->Solve(grid);

		//
		return str_matrix.c_str();
	}
	// APP_VERSION
	DLL_EXPORT const char*  GetDLLVersion()
	{
		//
		std::unique_ptr<Algorithm> uniquePtr = std::make_unique<Algorithm>();
		//
		return uniquePtr->configMap["DLL_VERSION"].c_str();
	}

//////////////////////////////////////////////////////////////////////////

