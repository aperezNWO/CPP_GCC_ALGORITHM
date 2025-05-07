///////////////////////////////////////////////////////////////////////////
// ALGORITHM.DLL
///////////////////////////////////////////////////////////////////////////
/*

		-- [_] TOOLCHAIN : C:\msys64\mingw64\bin.

*/

///////////////////////////////////////////////////////////////////////////
// CONFIGURACION EXE
///////////////////////////////////////////////////////////////////////////
/*

	1) SELECCIONAR ARCHIVO *.CPP 
	2) TERMINAL > RUN BUILD TASK > (2) (EXE) C/C++: g++.exe build active file
	3) SE GENERA ARCHIVO "ALGORITMO.EXE" X6
	4) EJECUTA  DESDE VISUAL STUDIO CODE : .\AlgorithmApp

*/
///////////////////////////////////////////////////////////////////////////

#include "Algorithm.cpp"

//////////////////////////////////////////////////////////////////////////
// DLL TEST
//////////////////////////////////////////////////////////////////////////
int main()
{
    cout << "DLL Version : " << GetDLLVersion()  <<  std::endl;

    int p_sortAlgoritm         = 2;
    const char* p_unsortedList = "23|7|10|16|1|4|22|2|6|24|8|14|11|15|21|13|19|20|18|0|17|5|3|9|12";

    std::cout << "Unsorted List: " << p_unsortedList << std::endl;

	std::unique_ptr<SortBenchMark> uniquePtr = std::make_unique<SortBenchMark>(
		p_unsortedList
	);

  	std::cout << "Sorted List:   " << uniquePtr->GetSort(p_sortAlgoritm).c_str() << std::endl;

	std::cout << "Press any key to continue";
	std::getchar();
  	
    return 0;
}

//////////////////////////////////////////////////////////////////////////
