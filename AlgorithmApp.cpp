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

 "C:\msys64\ucrt64\bin\g++.exe"  -g AlgorithmApp.cpp include\Dijkstra.cpp include\RegExManager.cpp include\SortBenchMark.cpp include\Sudoku.cpp include\TFileManager.cpp -o AlgorithmApp.exe -Iinclude  -m64
	
  AlgoritmApp.bat
 	            
*/

///////////////////////////////////////////////////////////////////////////

#include "Algorithm.cpp"
#include "include/iterativeList.h"
#include "include/recursiveList.h"

///////////////////////////////////////////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////////////////////////////////////////

//
int IterativeTest(int limit)
{
	//
	IterativeList* iterativeList = new IterativeList();  
	iterativeList->Set(limit);
	cout<<iterativeList->getTrace()<<endl;
	
	//
	return 0;
}

//  
int RecursiveTest(int limit)
{
	//
	RecursiveList* recursiveList = new RecursiveList();
	recursiveList->Set(limit);
	cout<<recursiveList->getTrace()<<endl;
	
	//
	return 0;
}

//
int GetDLLVersionTest()
{
	//
	std::unique_ptr<Algorithm> uniquePtr = std::make_unique<Algorithm>();
	//
	const char* dllVersion = uniquePtr->configMap["DLL_VERSION"].c_str();
	//	
    cout << "DLL Version : " << dllVersion  <<  std::endl;
    
    //
    return 0;
}

//
int SortBenchMarkTest()
{
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
int DijkstraTest()
{	
	//
    int p_vertexSize  = 9;
    int p_sourcePoint = 0;
    
	// Create a unique_ptr for Dijkstra
	std::unique_ptr<Dijkstra> uniquePtr = std::make_unique<Dijkstra>();
	
	// Generate the response
	static std::string response; 
	
	response = uniquePtr->GetRandomPoints(p_vertexSize, p_sourcePoint);
	
	// Return the pointer to the dynamically allocated memory
	cout <<"DIJKSTRA RESPONSE : " << response.c_str() << endl;
	
	//
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main()
{
    //
    const int opt_salida = 0;
          int option     = -1;
    const int limit      = 10;

    //
    while (option != opt_salida)
    {
         //
         system ("CLS");

         //   
         cout<<"";
         cout<<"-----------------------------------------"<< endl;
         cout<<"-- ALGORITHM UNIT TESTING                "<< endl;
         cout<<"-----------------------------------------"<< endl;
         cout<<"-- MAIN MENU                             "<< endl;
         cout<<"-----------------------------------------"<< endl;
         
         cout<<"-----------------------------------------"<< endl;
         cout<<"1. Iterative.                            "<< endl;         
         cout<<"2. Recursive.                            "<< endl;
         cout<<"3. GET DLL Version.                      "<< endl;
         cout<<"4. Sort Benchmark.                       "<< endl;
         cout<<"5. Dijkstra.                             "<< endl;
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
			 case 5: //  DIJKSATRA
			 	DijkstraTest();
			 break;
			 default :
			 	if (option != 0)
			 		cout<<"invalid option"<<endl;
			 break;    
         };
         
	    //
	    if (option != 0)
	    {
		    std::cout << "Press any key to continue..." << std::endl;
	        _getwch(); // Wait for a single key press	    	
		}
    };

	//
    return 0;
}

//////////////////////////////////////////////////////////////////////////
