
///////////////////////////////////////////////////////////
// COMMAND LINE
///////////////////////////////////////////////////////////

/*
 
 "C:\msys64\ucrt64\bin\g++.exe"  -g AlgorithmAppTestDLL.cpp  -o AlgorithmAppTestDLL.exe  -m64

  RunTestDLL.BAT
  
*/

#include <stdio.h>
#include <windows.h>

typedef const char* (*GetDLLVersionFunc)();  // Define function pointer type

int main()
{
	
	// Load the DLL
    HMODULE hDLL = LoadLibrary("Algorithm.dll");
    if (hDLL == NULL) {
        printf("Failed to load DLL.\n");
        return 1;
    }
    
	//////////////////////////////////////////////////////
    //GetTensorFlowAPPVersion
    //////////////////////////////////////////////////////
    
    
    GetDLLVersionFunc GetDLLVersion = (GetDLLVersionFunc)GetProcAddress(hDLL, "GetDLLVersion");
    if (!GetDLLVersion) {
        printf("Could not locate the function 'GetDLLVersion'.\n");
        FreeLibrary(hDLL);
        return 1;
    }

    // Call the function
    const char* appVersion = GetDLLVersion();
    printf("'GetDLLVersion' : %s\n", appVersion);
    
    //////////////////////////////////////////////////////////
    // Clean up
    //////////////////////////////////////////////////////////
    FreeLibrary(hDLL);
    return 0;
}
