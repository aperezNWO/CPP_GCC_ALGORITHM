#ifndef iterativeList_H // include guard
    #define iterativeList_H
#endif

#pragma once

#include <iostream>
#include <stdlib.h>
#include "node.h"

using namespace std;

class IterativeList
{
public:
    //
    node *head,*tail;
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
    static void Set()
    {
        //
        system ("CLS");

        //   
        cout<<"-----------------------------------------"<< endl;
        cout<<"-- ITERATIVE                             "<< endl;
        cout<<"-----------------------------------------"<< endl;


        //
        IterativeList a;
        for (int i = 0; i <= 10; i++)
                a.add_node(i);
        //
        node *tmp = new node;
        tmp       = a.head;

        //
        while (tmp->next != NULL)
        {
            cout<<tmp->data<<endl;
            tmp  = tmp->next;
        }

        //
        system("pause");
    };
};
