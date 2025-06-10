
/////////////////////////////////////////////////////////
// ALGORITHM.dll TEST REFERECE
/////////////////////////////////////////////////////////

/*

 "C:\msys64\ucrt64\bin\g++.exe" -I"include" -L"lib" -g AlgorithmAppTestRef.cpp  -o AlgorithmAppTestRef.exe -lAlgorithm -DALGORITHM_EXPORTS  -m64

 mingw32-make --always-make --debug=v
 
 dumpbin /exports Algorithm.dll

*/

/////////////////////////////////////////////////////////

#include "include\Algorithm.h"

//
class AlgorithmAppTestRef	 :
	public Algorithm
{
	public :
		AlgorithmAppTestRef();
		~AlgorithmAppTestRef();
	public :
		int GetDLLVersionTest();
		int GetCPPSTDVersionTest();
	public :
		Run();
};

//
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

//
int AlgorithmAppTestRef::GetDLLVersionTest()
{
	//
	cout << "-----------------------------"  << endl;
	cout << "DLL VERSION TEST             "  << endl;
	cout << "(Reading through inheritance)"  << endl;
	cout << "-----------------------------"  << endl;
	
	//
	cout << "(Reading 'AlgorithmTestRefApp.ini' file)" << endl;
    
    //
	static std::string dllVersion; 
	dllVersion = this->_GetDLLVersion();

	//
	cout << dllVersion << endl;
	//
	return 0;
}

//		
int AlgorithmAppTestRef::GetCPPSTDVersionTest()
{ 
	//
	cout << "-----------------------------"  << endl;
	cout << "CPP STD VERSION TEST         "  << endl;
	cout << "(Reading through inheritance)"  << endl;
	cout << "-----------------------------"  << endl;
	
	//
	static std::string cppSTDVersion;
	cppSTDVersion = this->GetCPPSTDVersion(); 
	cout << cppSTDVersion << endl;  
	//
	return 0;
};

//
int AlgorithmAppTestRef::Run()
{
	//
    const int opt_salida = 0;
          int option     = -1;

	//
    while (option != opt_salida)
    {
    	 //
    	 Algorithm *algorithm;
    	 const char* stdVersion  = algorithm->GetCPPSTDVersion();
    	 
         //
         system ("CLS");

         //   
         cout<<"";
         cout<<"-----------------------------------------"        << endl;
         cout<<"-- ALGORITHM DLL REF TESTING             "        << endl;
         cout<<"-- C++ Standard Version: [" << stdVersion << "]"  << endl;
         cout<<"-----------------------------------------"        << endl;
         cout<<"-- MAIN MENU                             "        << endl;
         cout<<"-----------------------------------------"        << endl;
         
         cout<<"-----------------------------------------"<< endl;
         cout<<"1. DLL Version.                          "<< endl;         
         cout<<"2. Get C++ STD Version.                  "<< endl;
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
             case 1: // GetDLLVersion
				this->GetDLLVersionTest();
             break;
             case 2: // GetCPPSTDVersion
				this->GetCPPSTDVersionTest();
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

//	
int main()
{
   	//
    AlgorithmAppTestRef *algorithmAppTestRef = new 	AlgorithmAppTestRef();
    
    //
	algorithmAppTestRef->Run();
	
	//
	return 0;
}

