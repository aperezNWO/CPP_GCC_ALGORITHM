#ifndef recursiveList_H // include guard
#define recursiveList_H
#endif

#pragma once

#include <iostream>
#include <stdlib.h>
#include "node.h"

using namespace std;

class RecursiveList
{
  public : 
    // Allocates a new node with given data
    static node *newNode(int data)
    {
        node *new_node = new node;
        new_node->data = data;
        new_node->next = NULL;
        return new_node;
    }
    
    // Function to insert a new node at the
    // end of linked list using recursion.
    static node* insertEnd(node* head, int data)
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
    static void traverse(node* head)
    {
        if (head == NULL)
            return;
        
        // If head is not NULL, print current node
        // and recur for remaining list   
        cout << head->data << " "<< endl;
    
        traverse(head->next);
    }
    //
    static void Set()
    {
        //
        system ("CLS");

        //   
        cout<<"-----------------------------------------"<< endl;
        cout<<"-- RECURSIVE                             "<< endl;
        cout<<"-----------------------------------------"<< endl;

        //
        node* head = NULL;
        for (int i = 0; i < 10; i++)
            head = insertEnd(head, i);

        //
        traverse(head);
        
        //
        system("pause");
    };
};
