#include "SortBenchMark.h"

	//
	SortBenchMark::SortBenchMark(const char* p_randomValues)
	{
		//
		this->randomValues   = p_randomValues;
		this->arraySize      = std::stoi(this->configMap["ARRAY_SIZE"]);

		//-----------------------------------------------------
		// INICIAR ARREGLO
		//-----------------------------------------------------
		vector<string>   arreglo_str = StringSplit(p_randomValues,"|");
		//
		for (int i = 0; i < this->arraySize; i++) {
			//
			this->arreglo.push_back( std::stoi(arreglo_str[i] ) );
		}

		//
		this->_fileManager.DeleteFile("Array.txt");
		this->_fileManager.SaveVectorToFile(this->arreglo,"Array.txt");

	};
	//
	SortBenchMark::~SortBenchMark()
	{
		 //
	};
    //
	void SortBenchMark::SaveStep(int arr[])
	{
		//----------------------------------------------------
		// IMPRIMIR PASO INTERMEDIO
		//-----------------------------------------------------
		//
		string tempValues = "";
		for (int index = 0; index < this->arraySize; index++)
		{
		  //
		  stringstream  ss;
		  //
		  string separator = (index == 0) ? "" : "<br/>";
		  ss << separator << arr[index];
		  //
		  string _tempValues  = ss.str();
		  //
		  tempValues          += _tempValues;
		}
		//
		this->sortSteps.push_back(tempValues);
	}
	//
	string SortBenchMark::GetSort(int p_sortAlgorithm)
	{
		//
		switch (p_sortAlgorithm)
		{
			case 1: // BUBBLE SORT
				this->BubbleSort();
				break;
			case 2: // QUICK SORT
				this->QuickSort();
				break;
		};

		//
		string sortedList = "";
		// Using iterators
		for (auto sortStep = this->sortSteps.begin(); sortStep != this->sortSteps.end(); ++sortStep) {
				  //
				  stringstream  ss;
				  //
				  string separator = "~";
				  ss << separator << "<br/>" << *sortStep << "<br/>";
				  //
				  string _tempValues  = ss.str();
				  //
				  sortedList          += _tempValues;

		}

		//
		this->_fileManager.DeleteFile("SortedArray.txt");
		this->_fileManager.SaveVectorToFile(this->sortSteps,"SortedArray.txt");

		//
		return sortedList;
	};
	//
	void SortBenchMark::QuickSort()
	{
		//----------------------------------------------------
		// CONFIGURAR VALORES INICIALES
		//-----------------------------------------------------
		//
		int* _arreglo     = new int[this->arraySize];
		//
		for (int i = 0; i < this->arraySize; i++) {
			  _arreglo[i] = arreglo[i];
		}
		//----------------------------------------------------
		// INGRESAR A RECURSION
		//-----------------------------------------------------
		quickSort(_arreglo,0 , this->arraySize - 1);

		//----------------------------------------------------
		// IMPRIMIR VALOES FINALES
		//-----------------------------------------------------
		SaveStep(_arreglo);

		//----------------------------------------------------
		// REMOVER VALORES REPETIDOS
		//-----------------------------------------------------

		// Use std::unique to move duplicates to the end
		auto last = std::unique(this->sortSteps.begin(), this->sortSteps.end());

		// Erase the duplicates from the vector
		this->sortSteps.erase(last, this->sortSteps.end());
	}
	//
	int SortBenchMark::partition(int arr[],int low,int high)
	{
	  //choose the pivot
	  int pivot=arr[high];
	  //Index of smaller element and Indicate
	  //the right position of pivot found so far
	  int i=(low-1);
	  //
	  for(int j=low;j<=high;j++)
	  {
		  //If current element is smaller than the pivot
		  if(arr[j]<pivot)
		  {
			//Increment index of smaller element
			i++;
			std::swap(arr[i],arr[j]);
			SaveStep(arr);
		  }
	  }
	  //
	  std::swap(arr[i+1],arr[high]);
	  SaveStep(arr);
	  //
	  return (i+1);
	}
	//
	void SortBenchMark::quickSort(int arr[],int low,int high)
	{
	  // when low is less than high
	  if(low<high)
	  {
		// pi is the partition return index of pivot

		int pi=partition(arr,low,high);

		//Recursion Call
		//smaller element than pivot goes left and
		//higher element goes right
		quickSort(arr,low,pi-1);
		quickSort(arr,pi+1,high);
	  }
	}
	//
	void SortBenchMark::BubbleSort()
	{
	   //
	   int temp = 0;
	   //
	   for (int write = 0; write < this->arraySize; write++)
	   {
		   //
		   for (int sort = 0; sort < this->arraySize - 1; sort++)
		   {
			   //
			   if (arreglo[sort] > arreglo[sort + 1])
			   {
				   //
				   temp              = arreglo[sort + 1];
				   arreglo[sort + 1] = arreglo[sort];
				   arreglo[sort]     = temp;

				  //-----------------------------------------------------
				  // GUARDAR PASO DEL ARREGLO EN MATRIZ DE PASOS
				  //-----------------------------------------------------
				  //
				  string tempValues = "";
				  //
				  for (int j = 0; j < this->arraySize; j++)
				  {
					  //
					  stringstream  ss;
					  //
					  string separator = (j == 0)? "" : "<br/>";
					  ss << separator << arreglo[j];
					  //
					  string _tempValues  = ss.str();
					  //
					  tempValues          += _tempValues;
				  }
				  //
				  this->sortSteps.push_back(tempValues);
			   }
		   }
	   }
	}

