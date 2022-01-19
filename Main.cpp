
/*******************************************************************/
//  CONFIGURACION
/*******************************************************************/

/*******************************************************************/
//  DESCRIPCION
/*******************************************************************/
/*
  1) EJEMPLO DE LISTAS DINÁMICAS RECURSIVAS E ITERATIVAS.
  2) DEMOSTRACIÓN DE USO DE ARCHIVOS DE ENCABEZADO ".H".
  3) ESCRITO EN LENGUAJE C++.
  4) COMPILADOR MINGW / ENTORNO VISUAL STUDIO CODE.
  5) GITHUB : https://github.com/aperezNWO/cpp_test
*/
/*******************************************************************/

#include "iterativeList.h"
#include "recursiveList.h"

//
int main()
{
    //
    const int opt_salida = 3;
    int option = 0;

    //
    while (option != opt_salida)
    {
         //
         system ("CLS");

         //   
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
                IterativeList::Set();
             break;
             case 2:
                RecursiveList::Set();
             break;                

         };

         //
         system ("CLS");
    };

    //
    return 0;
}
