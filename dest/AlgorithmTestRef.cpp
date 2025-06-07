
/////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////

/*

 "C:\msys64\ucrt64\bin\g++.exe" -I"include" -L"lib" -g AlgorithmTestRef.cpp  -o AlgorithmTestRef.exe -lAlgorithm -DALGORITHM_EXPORTS  -m64

 
 dumpbin /exports Algorithm.dll

*/

/////////////////////////////////////////////////////////

#include "include\Algorithm.h"

class AlgorithmTestRefApp	 :
	public Algorithm
{
	public :
		AlgorithmTestRefApp();
		~AlgorithmTestRefApp();
};

AlgorithmTestRefApp::AlgorithmTestRefApp()
{
	//
	this->ReadConfigFile("AlgorithmTestRefApp.ini");
};

//
AlgorithmTestRefApp::~AlgorithmTestRefApp()
{
	//
};
	
int main()
{
    // Create a unique_ptr for Dijkstra
    std::unique_ptr<AlgorithmTestRefApp> uniquePtr = std::make_unique<AlgorithmTestRefApp>();

    // Generate the response
    static std::string response; 
	
	//
	response = uniquePtr->_GetDLLVersion();

	//
	cout << response;
	
	//
	return 0;
}

