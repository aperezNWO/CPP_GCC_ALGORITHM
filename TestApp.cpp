/*******************************************************************/
//  DESCRIPCION
/*******************************************************************/
/*
  1) EJEMPLO DE LISTAS DINÁMICAS RECURSIVAS E ITERATIVAS.
  2) DEMOSTRACIÓN DE USO DE ARCHIVOS DE ENCABEZADO ".H".
  3) ESCRITO EN LENGUAJE C++.
  4) COMPILADOR MINGW / ENTORNO VISUAL STUDIO CODE.
  5) GITHUB : https://github.com/aperezNWO/cpp_gcc_algorithm
*/
/*******************************************************************/
//  CONFIGURACION - visual studio code
/*******************************************************************/
/*
  -- [_] toolchain linked via "tasks.json" -> "C:\\msys64\\ucrt64\\bin\\g++.exe".

   1) SELECT *.CPP FILE (i.e main_exe.cpp)
   2) TERMINAL > RUN TASK,
   3) SELECT "(1) C/C++: g++.exe compilar archivo activo""
   4) RUN FILE :  I.E: .\main_exe.exe
*/

/*******************************************************************/
// COMMAND LINE
/*******************************************************************/
/*

	 "C:\msys64\ucrt64\bin\g++.exe"  -g TestApp.cpp  -o TestApp.exe 

*/

#include "include/iterativeList.h"
#include "include/recursiveList.h"

//
int main()
{
    //
    const int opt_salida = 3;
          int option     = 0;
    const int limit      = 10;

    //
    while (option != opt_salida)
    {
         //
         system ("CLS");

         //   
         cout<<"";
         cout<<"-----------------------------------------"<< endl;
         cout<<"-- LINKED LISTS                          "<< endl;
         cout<<"-----------------------------------------"<< endl;
         cout<<"-- MAIN MENU"<< endl;
         cout<<"-----------------------------------------"<< endl;
         
         cout<<""<< endl;
         cout<<"1. Iterative."<< endl;         
         cout<<"2. Recursive."<< endl;
         cout<<"3. Exit."<< endl;
         cout<<""<< endl;
         cout<<"Enter Option :";
         cin>>option;

         //
         switch (option)
         {
             case 1:
               {
               	  //
         		  system ("CLS");
		 		  //
                  IterativeList* iterativeList = new IterativeList();  
                  iterativeList->Set(limit);
                  cout<<iterativeList->getTrace()<<endl;
			      //
				  std::cout << "Press any key to continue..." << std::endl;
			      _getwch(); // Wait for a single key press
               }
             break;
             case 2:
               {
               	  //
         		  system ("CLS");
         		  //
                  RecursiveList* recursiveList = new RecursiveList();
                  recursiveList->Set(limit);
                  cout<<recursiveList->getTrace()<<endl;
			      //
				  std::cout << "Press any key to continue..." << std::endl;
			      _getwch(); // Wait for a single key press
               }
             break;                

         };


    };

    //
    return 0;
}

