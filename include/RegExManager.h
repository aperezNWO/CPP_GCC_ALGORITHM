///////////////////////////////////////////////////////////////////////////
// REGEX MANAGER
///////////////////////////////////////////////////////////////////////////

#ifndef RegExManager_H // include guard
#define RegExManager_H
#endif

#include "algorithm.h"

using namespace std;

#pragma hdrstop
#pragma argsused

class RegExManager :
	public Algorithm
{
	public :
		 RegExManager();
		 ~RegExManager();
		 int    GetXml();
		 string RegExEval(char* p_tagSearch, char* p_textSearch);
	public :
		 vector<string>      xmlItems;
};
