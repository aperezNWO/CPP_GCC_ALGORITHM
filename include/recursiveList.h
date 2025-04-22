#ifndef recursiveList_H // include guard
#define recursiveList_H
#endif

#pragma once

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "node.h"

using namespace std;

class RecursiveList
{
  private:
	string  __trace;
  
  public : 
    // Allocates a new node with given data
    node *newNode(int data)
    {
        node *new_node = new node;
        new_node->data = data;
        new_node->next = NULL;
        return new_node;
    }
    // Function to insert a new node at the
    // end of linked list using recursion.
    node* insertEnd(node* head, int data)
    {
        // If linked list is empty, create a 
        // new node (Assuming newNode() allocates
        // a new node with given data)
        if (head == NULL) 
            return newNode(data);
    
        // If we have not reached end, keep traversing
        // recursively.
        else
            head->next = insertEnd(head->next, data);
        return head;
    }
    //
    void traverse(node* head)
    {
        if (head == NULL)
            return;
        
        // If head is not NULL, print current node
        // and recur for remaining list   
        //cout << head->data << " "<< endl;
        
        //
        stringstream ss; 
        string       _strdata;
         
        ss << head->data;  
        ss >> _strdata;
        
        setTrace(("->" + _strdata));
        
        //
        traverse(head->next);
    }
    //
    void setTrace(string aTrace)
    {
        __trace += aTrace;    
    }
    //
	const char* getTrace()
	{
        return __trace.c_str();
    }
    //
    void Set(int arraySize)
    {
        //
        setTrace("Recursive : ");
        
        //
        node* head = NULL;
        for (int i = 1; i <= arraySize; i++)
            head = insertEnd(head, i);
        
        //
        traverse(head);
    };
};
