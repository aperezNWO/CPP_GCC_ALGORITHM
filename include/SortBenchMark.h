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
	   SortBenchMark(const char* p_randomValues, int p_format);
	   ~SortBenchMark();
	   void           SaveStep(int arr[]);
	   string	      GetSort(int p_sortAlgoritm);
	   void           QuickSort();
	   int            partition(int arr[],int low,int high);
	   void           quickSort(int arr[],int low,int high);
	   void           BubbleSort();
	public  :
	   const char*      randomValues;
	   int              format;
	   int              arraySize;
	   vector<int>      arreglo;
	   vector<string>   sortSteps;
	   FileManager      _fileManager;
};
