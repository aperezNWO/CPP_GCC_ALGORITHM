///////////////////////////////////////////////////////////////////////////
// ALGORITHM.LIBRARY.DLL
///////////////////////////////////////////////////////////////////////////

#ifndef SortBenchMark_H // include guard
#define SortBenchMark_H
#endif

#include "algorithm.h"
#include "TFileManager.h"

using namespace std;

#pragma hdrstop
#pragma argsused

class SortBenchMark	 :
	public Algorithm
{
	public  :
	   SortBenchMark(char* p_randomValues);
	   ~SortBenchMark();
	   void           SaveStep(int arr[]);
	   string	      GetSort(int p_sortAlgoritm);
	   void           QuickSort();
	   int            partition(int arr[],int low,int high);
	   void           quickSort(int arr[],int low,int high);
	   void           BubbleSort();
	public  :
	   vector<int>      arreglo;
	   vector<string>   sortSteps;
	   char*            randomValues;
	   int              arraySize;
	   FileManager      _fileManager;
};
