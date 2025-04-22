#ifndef iterativeList_H // include guard
    #define iterativeList_H
#endif

#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>  
#include <sstream>
#include "node.h"

using namespace std;

class IterativeList
{
  private:
    string  __trace;
  
  public:
    //
    node   *head,*tail;
    //
    IterativeList()
    {
        head = NULL;
        tail = NULL;
    }
	//
    void add_node(int n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
	//
	void setTrace(string aTrace)
    {
        __trace = aTrace;    
    }
    //
	const char* getTrace()
	{
		return __trace.c_str();
	}
	//
	void Set(int limit)
    {
        //
        IterativeList a;
		string        _trace;

        for (int i = 0; i <= limit; i++)
                a.add_node(i);
        //
        node *tmp = new node;
        tmp       = a.head;

        //
        while (tmp->next != NULL)
        {
            //
            string  _strdata  = "";
            tmp               = tmp->next;

            //
            stringstream ss;  
            ss << tmp->data;  
            ss >> _strdata;
            
            //
            _trace += ("->" + _strdata);
        }

        //
        setTrace("Iterative : " + _trace);
    };
    

};
