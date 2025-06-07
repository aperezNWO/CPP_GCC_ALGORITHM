
/////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////

/*

 "C:\msys64\ucrt64\bin\g++.exe" -I"include" -L"lib" -g AlgorithmAppTestRef.cpp  -o AlgorithmAppTestRef.exe -lAlgorithm -DALGORITHM_EXPORTS  -m64
 
 dumpbin /exports Algorithm.dll

*/

/////////////////////////////////////////////////////////

#include "include\Algorithm.h"

class AlgorithmAppTestRef	 :
	public Algorithm
{
	public :
		AlgorithmAppTestRef();
		~AlgorithmAppTestRef();
};

AlgorithmAppTestRef::AlgorithmAppTestRef()
{
	//
	this->ReadConfigFile("AlgorithmTestRefApp.ini");
};

//
AlgorithmAppTestRef::~AlgorithmAppTestRef()
{
	//
};
	
int main()
{
    // Create a unique_ptr for Dijkstra
    std::unique_ptr<AlgorithmAppTestRef> uniquePtr = std::make_unique<AlgorithmAppTestRef>();

    // Generate the response
    static std::string response; 
	
	//
	response = uniquePtr->_GetDLLVersion();

	//
	cout << response;
	
	//
	return 0;
}

