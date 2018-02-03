#ifndef MQUEUE_H
#define MQUEUE_H

#include <iostream>
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

struct Node
{
    int data;
    Node* next;
};

class MQueue
{
    public:
        MQueue();
        virtual ~MQueue();

        void push(int d); // to end
        int pop(); //from start
        int getFirst() const;

        int getCount() const;

    protected:

    private:
        Node* head;
        int node_count;
};

#endif // MQUEUE_H
