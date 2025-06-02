
///////////////////////////////////////////////////////////
// COMMAND LINE
///////////////////////////////////////////////////////////

/*
 
 "C:\msys64\ucrt64\bin\g++.exe"  -g Algorithm_Test_Dll.cpp  -o Algorithm_Test_Dll.exe  -m64

*/

#include <stdio.h>
#include <windows.h>

typedef const char* (*GetTensorFlowAPPVersionFunc)();  // Define function pointer type

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
    
    
    GetTensorFlowAPPVersionFunc GetTensorFlowAPPVersion = (GetTensorFlowAPPVersionFunc)GetProcAddress(hDLL, "GetDLLVersion");
    if (!GetTensorFlowAPPVersion) {
        printf("Could not locate the function 'GetDLLVersion'.\n");
        FreeLibrary(hDLL);
        return 1;
    }

    // Call the function
    const char* appVersion = GetTensorFlowAPPVersion();
    printf("'GetDLLVersion' : %s\n", appVersion);
    
    //////////////////////////////////////////////////////////
    // Clean up
    //////////////////////////////////////////////////////////
    FreeLibrary(hDLL);
    return 0;
}
