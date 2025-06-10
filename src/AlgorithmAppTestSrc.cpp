/*******************************************************************/
//  DESCRIPCION
/*******************************************************************/
/*
  0) ALGORITHM UNIT TESTING.
  1) EJEMPLO DE LISTAS DINÁMICAS RECURSIVAS E ITERATIVAS.
  2) DEMOSTRACIÓN DE USO DE ARCHIVOS DE ENCABEZADO ".H".
  3) ESCRITO EN LENGUAJE C++.
  4) COMPILADOR MINGW / ENTORNO VISUAL STUDIO CODE.
  5) GITHUB : https://github.com/aperezNWO/cpp_gcc_algorithm
*/

///////////////////////////////////////////////////////////////////////////
// VISUAL STUDIO CODE
///////////////////////////////////////////////////////////////////////////
/*

	1) SELECCIONAR ARCHIVO *.CPP. 
	2) TERMINAL > RUN BUILD TASK > (2) (EXE) C/C++: g++.exe build active file.
	3) SE GENERA ARCHIVO "ALGORITMO.EXE".
	4) EJECUTA  DESDE VISUAL STUDIO CODE : .\AlgorithmApp.

*/

///////////////////////////////////////////////////////////////////////////
// EMBARCADERO DEV C++  / COMMAND LINE
///////////////////////////////////////////////////////////////////////////
/*

 "C:\msys64\ucrt64\bin\g++.exe" -std=c++20 -g AlgorithmAppTestSrc.cpp  include\Dijkstra.cpp include\RegExManager.cpp include\SortBenchMark.cpp include\Sudoku.cpp include\TFileManager.cpp -o AlgorithmAppTestSrc.exe -Iinclude -DALGORITHM_EXPORTS -m64
	
  RunTestExe.bat
 	            
*/

///////////////////////////////////////////////////////////////////////////


#include "include/iterativeList.h"
#include "include/recursiveList.h"
#include "Algorithm.cpp"


///////////////////////////////////////////////////////////////////////////
// CLASSES
///////////////////////////////////////////////////////////////////////////

class AlgorithmAppTestSrc :
	   public Algorithm
{
   	 public :
	 		AlgorithmAppTestSrc();
	 		~AlgorithmAppTestSrc();
	 public :
	 	int IterativeTest(int limit);
		int RecursiveTest(int limit);
		int GetDLLVersionTest();
		int SortBenchMarkTest();
		int DijkstraTest();
		int RegExTest();
		int SudokuTest();
	 	int Run();
	 public :
	 	FileManager      _fileManager;
};

///////////////////////////////////////////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////////////////////////////////////////
AlgorithmAppTestSrc::AlgorithmAppTestSrc() : Algorithm(false)
{
	//
	this->ReadConfigFile("AlgorithmAppTestSrc.ini");
}
//
AlgorithmAppTestSrc::~AlgorithmAppTestSrc()
{
	//
}
//
int AlgorithmAppTestSrc::IterativeTest(int limit)
{
	//
	cout << "---------------"<< endl;
	cout << "ITERATIVE TEST" << endl;
	cout << "---------------"<< endl;
	
	//
	IterativeList* iterativeList = new IterativeList();  
	iterativeList->Set(limit);
	cout<<iterativeList->getTrace()<<endl;
	
	//
	return 0;
}

//  
int AlgorithmAppTestSrc::RecursiveTest(int limit)
{
	//
	cout << "---------------" << endl;
	cout << "RECURSIVE TEST " << endl;
	cout << "---------------" << endl;
	
	//
	RecursiveList* recursiveList = new RecursiveList();
	recursiveList->Set(limit);
	cout<<recursiveList->getTrace()<<endl;
	
	//
	return 0;
}

//
int AlgorithmAppTestSrc::GetDLLVersionTest()
{
	//
	cout << "------------------"  << endl;
	cout << "DLL VERSION TEST  "  << endl;
	cout << "------------------"  << endl;
	
	//
	//std::unique_ptr<Algorithm> uniquePtr = std::make_unique<Algorithm>();
	//
	//const char* dllVersion = uniquePtr->configMap["DLL_VERSION"].c_str();
	// 
	const char* dllVersion = this->_GetDLLVersion();
	//	
    cout << "DLL Version : " << dllVersion  <<  std::endl;
    
    //
    return 0;
}

//
int AlgorithmAppTestSrc::SortBenchMarkTest()
{
	//
	cout << "--------------------"  << endl;
	cout << "SORT BENCHMARK TEST "  << endl;
	cout << "--------------------"  << endl;
	
	//
	FormatType  format                 = FormatType::JSON; // JSON
    int         p_sortAlgorithm        = 2; // QUICK SORT
    const char* p_unsortedList         = "23|7|10|16|1|4|22|2|6|24|8|14|11|15|21|13|19|20|18|0|17|5|3|9|12";


	//
	std::unique_ptr<SortBenchMark> _uniquePtr = std::make_unique<SortBenchMark>(p_unsortedList,format);
	
	//
	std::cout << "Unsorted List in file 'ArrayUnsorted.txt'." << std::endl;

	//
	_uniquePtr->GetSort(p_sortAlgorithm);
		
	//
	switch (format) {
		case FormatType::HTML : // HTML
			  	std::cout << "Sorted   List in file 'ArraySorted.txt'.  " << std::endl;
		break;
		case FormatType::JSON : // JSON
				std::cout << "Sorted   List in file 'ArraySorted.json'. " << std::endl;
		break;
	}

  	
  	//
  	return 0;
}

//
int AlgorithmAppTestSrc::DijkstraTest()
{
	//
	cout << "--------------------"  << endl;
	cout << "DIJKSTRA TEST       "  << endl;
	cout << "--------------------"  << endl;	
	
	//
    int p_vertexSize  = 9;
    int p_sourcePoint = 0;
    
	// Create a unique_ptr for Dijkstra
	std::unique_ptr<Dijkstra> uniquePtr = std::make_unique<Dijkstra>();
	
	// Generate the response
	static std::string response; 
	
	response = uniquePtr->GetRandomPoints(p_vertexSize, p_sourcePoint);
	
	// Return the pointer to the dynamically allocated memory
	cout <<"RESPONSE : " << response.c_str() << endl;
	
	//
	return 0;
}
//
int AlgorithmAppTestSrc::RegExTest()
{
		//
		cout << "--------------------"  << endl;
		cout << "REG EX TEST         "  << endl;
		cout << "--------------------"  << endl;
		
		//
		char p_tagSearch[8];
		std::strcpy(p_tagSearch, "company");
		
		char p_textSearch[4];
		std::strcpy(p_textSearch,"BMG");
		//
		std::unique_ptr<RegExManager> uniquePtr = std::make_unique<RegExManager>();
		//
		static std::string response; 
		response  = uniquePtr->RegExEval(p_tagSearch, p_textSearch);
		
		if (response != "")
		{
			//
			std::unique_ptr<Algorithm> uniquePtr = std::make_unique<Algorithm>(false);
			//
			vector<string> vectorResponse = uniquePtr->StringSplit(response.c_str(),"|");
			//
			cout << "Se encontraron [" << vectorResponse[0] << "] coincidencias." << endl;
			//
			this->_fileManager.SaveLineToFile(response,"cdCatalog.html");
			cout << "Se creo el  archivo 'cdCatalog.html' " << endl;
		}
    
	//
	return 0;
}
//
//
int AlgorithmAppTestSrc::SudokuTest()
{
	//
	cout << "--------------------"  << endl;
	cout << "SUDOKU TEST         "  << endl;
	cout << "--------------------"  << endl;
	
	//
	const static int   N = 9;
	int                K = 20;

	//
	std::unique_ptr<SudokuGenerator> uniquePtr = std::make_unique<SudokuGenerator>(N, K);
	string           str_matrix                = uniquePtr->Run();

	//cout << endl << "Sudoku to Solve : " << str_matrix << endl;
	cout << endl << "------------------" << endl;
	//
	Algorithm*   algorithm     = new Algorithm(false);
	string       str_p_matrix  = str_matrix;
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
	const static int   _N           = 9;
	int                grid[_N][_N] =
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
		//fileManager->SaveLineToFile(row,"Sudoku.txt");
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
	std::unique_ptr<SudokuSolver> uniquePtrSolver = std::make_unique<SudokuSolver>();
	string           str_matrix_solved            = uniquePtrSolver ->Solve(grid);

	//
	//fileManager->SaveLineToFile("\nSudoku Solved \n","Sudoku.txt");
	//
	//cout << "Sudoku Solved " << str_matrix_solved.c_str() << endl;
	
	cout << endl << "(Ver Archivo 'Sudoku.txt') " << endl;
	//
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int AlgorithmAppTestSrc::Run()
{
    //
    const int opt_salida = 0;
          int option     = -1;
    const int limit      = 10;

    //
    while (option != opt_salida)
    {
    	 //
    	 //Algorithm *algorithm    = new Algorithm(__cplusplus);
    	 //const char* stdVersion  = algorithm->GetCPPSTDVersion();
    	 
    	 const char* stdVersion    = this->GetCPPSTDVersion();
    	 
         //
         system ("CLS");

         //   
         cout<<"";
         cout<<"-----------------------------------------"        << endl;
         cout<<"-- ALGORITHM SRC TESTING                 "        << endl;
         cout<<"-- C++ Standard Version: [" << stdVersion << "]"  << endl;
         cout<<"-----------------------------------------"        << endl;
         cout<<"-- MAIN MENU                             "        << endl;
         cout<<"-----------------------------------------"        << endl;
         
         cout<<"-----------------------------------------"<< endl;
         cout<<"1. Iterative.                            "<< endl;         
         cout<<"2. Recursive.                            "<< endl;
         cout<<"3. GET DLL Version.                      "<< endl;
         cout<<"4. Sort Benchmark.                       "<< endl;
         cout<<"5. Dijkstra.                             "<< endl;
         cout<<"6. Regular Expression.                   "<< endl;
         cout<<"7. Sudoku.                               "<< endl;
         cout<<"-----------------------------------------"<< endl;
         cout<<"0. Exit.                                 "<< endl;
         cout<<"-----------------------------------------"<< endl;
         cout<<"Enter Option : ";
         cin>>option;

	   	 //
		 system ("CLS");
		 
         //
         switch (option)
         {
             case 1: // ITERATIVE
				IterativeTest(limit);
             break;
             case 2: // RECURSIVE
				RecursiveTest(limit);
             break;       
			 case 3: // GET DLL VERSION
			 	GetDLLVersionTest();
			 break;    
			 case 4: // SORT BENCHMARK
			 	SortBenchMarkTest(); 
			 break;
			 case 5: //  DIJKSTRA
			 	DijkstraTest();
			 break;
			 case 6: // REGEX
			 	RegExTest();
			 break;
			 case 7: // SUDOKU
			    SudokuTest();
			 break;
			 default :
			 	if (option != 0)
			 		std::cout << std::endl << "invalid option" <<std::endl;
			 break;    
         };
         
	    //
	    if (option != 0)
	    {
		    std::cout << std::endl <<  "Press any key to continue..." << std::endl;
	        _getwch(); // Wait for a single key press	    	
		}
    };

	//
    return 0;
}

int main()
{
    AlgorithmAppTestSrc *algorithmApp = new AlgorithmAppTestSrc();
    
    algorithmApp->Run();
};

//////////////////////////////////////////////////////////////////////////
