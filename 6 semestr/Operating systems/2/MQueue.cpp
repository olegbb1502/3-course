#include "MQueue.h"

MQueue::MQueue()
{
    head = NULL;
    node_count = 0;
}

MQueue::~MQueue()
{
    //dtor
}

void MQueue::push(int d)
{
    if(head == NULL)
    {
        head = new Node;
        head->data = d;
        head->next = NULL;
    }else
    {
        Node* tmp = head;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new Node;
        tmp->next->data = d;
        tmp->next->next = NULL;
    }


    node_count ++;
}

int MQueue::pop()
{
    Node* tmp = head->next;
    int data = head->data;
    delete head;
    head = tmp;
    node_count --;
    return data;
}

int MQueue::getFirst() const
{
    return head->data;
}

int MQueue::getCount() const
{
    return node_count;
}
