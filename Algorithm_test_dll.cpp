///////////////////////////////////////////////////////////////////////////
// ALGORITHM_TEST_DLL.EXE
///////////////////////////////////////////////////////////////////////////
/*

		-- [_] TOOLCHAIN : C:\msys64\ucrt64\bin.
*/

///////////////////////////////////////////////////////////////////////////
// CONFIGURACION EXE
///////////////////////////////////////////////////////////////////////////
/*
	1) SELECCIONAR ARCHIVO *.CPP EXE
	2) TERMINAL > RUN BUILD TASK >  (1) C/C++: g++.exe compilar archivo activo 
	3) SE GENERA ARCHIVO "ALGORITHM_TEST_DLL.EXE" .EXE X64
	4) COLOCAR LOS SIGUIENTES ARCHIVOS  EN CARPETA "/_DIST" (solo para pruebads):

		a) ALGORITHM_TEST_DLL.EXE

*/
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <windows.h>

// Define a function pointer type that matches the exported function signature
typedef const char* (__cdecl *CallDLLVersionFunc)();


int main() {
    // Load the DLL
    HINSTANCE hDLL = LoadLibraryA("Algorithm.dll"); // Replace "your_tensorflow_dll.dll" with the actual name of your DLL

    if (hDLL == nullptr) {
        std::cerr << "Error loading DLL: " << GetLastError() << std::endl;
        return 1;
    }
 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    CallDLLVersionFunc callDLLVersionFunc = (CallDLLVersionFunc)GetProcAddress(hDLL, "GetDLLVersion");


    if (callDLLVersionFunc == nullptr) {
        std::cerr << "Error getting function address for DLL: " << GetLastError() << std::endl;
        FreeLibrary(hDLL);
        return 1;
    }

    // Call the exported function
    std::cout << "Calling function from DLL..." << std::endl;

    const char* dllVersion = callDLLVersionFunc();

    if (dllVersion != nullptr) {
        std::cout << "DLL Version: " << dllVersion << std::endl;
    } else {
        std::cerr << "Error: 'GetDLLVersion' returned a null pointer." << std::endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Free the DLL
    FreeLibrary(hDLL);

    return 0;
}

