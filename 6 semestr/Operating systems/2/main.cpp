//#include "MQueue.h"

#define USERS 0
#define TIME_MIN 4000
#define TIME_MAX 9000

using namespace std;

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

MQueue* q_users;

CRITICAL_SECTION sec_count, sec_brad;
CRITICAL_SECTION sec_users[USERS];

void *closeSec(void* params)
{
    LPCRITICAL_SECTION section = (LPCRITICAL_SECTION) params;
    EnterCriticalSection(section);

}

void blockSection(LPCRITICAL_SECTION section)
{
    pthread_t block_thread;
    pthread_create(&block_thread, NULL, closeSec, section);
    pthread_join(block_thread, NULL);
}

void *users(void* params)
{
    int number = *(int *) params;
    while(TRUE)
    {
        int time = TIME_MIN + rand() % (TIME_MAX - TIME_MIN);
        Sleep(time);

        EnterCriticalSection(&sec_count);

        if(q_users->getCount() == 0)
        {
            LeaveCriticalSection(&sec_brad);
            printf("Брадобрея будит клиент %d\n", number + 1);
        }
        q_users->push(number);
        printf("Клиент %d стал в очередь\n", number + 1);

        LeaveCriticalSection(&sec_count);


        EnterCriticalSection(&sec_users[number]);
        printf("Клиент %d ушел\n", number + 1);
        LeaveCriticalSection(&sec_users[number]);

        blockSection(&sec_users[number]);
    }

}

void* bradThread(void* params)
{
    int user_num = -1;
    while(TRUE)
    {
        printf("\nБрадобрей спит\n");
        EnterCriticalSection(&sec_brad);
        LeaveCriticalSection(&sec_brad);

        EnterCriticalSection(&sec_count);

        while(q_users->getCount() > 0)
        {
            user_num = q_users->getFirst();
            LeaveCriticalSection(&sec_count);

            //WORK
            printf("Брадобрей стрижет клиента %d\n", user_num + 1);
            int time = TIME_MIN + rand() % (TIME_MAX - TIME_MIN);
            Sleep(time);

            EnterCriticalSection(&sec_count);
            q_users->pop();
            LeaveCriticalSection(&sec_users[user_num]); //leave user
        }

        blockSection(&sec_brad);
        LeaveCriticalSection(&sec_count);
    }
}


int main()
{
    setlocale(0, "Rus");
    q_users = new MQueue();

    InitializeCriticalSection(&sec_count);
    InitializeCriticalSection(&sec_brad);

    EnterCriticalSection(&sec_brad); //brad sleep
    for(int i=0; i<USERS; i++) //users check
     {
         InitializeCriticalSection(&sec_users[i]);
         EnterCriticalSection(&sec_users[i]);
     }


    pthread_t users_threads[USERS];
    pthread_t brad_thread;

    int us_num[USERS];

    //THREAD CREATE
    for(int i=0; i<USERS; i++)
     {
         us_num[i] = i;
         pthread_create(&users_threads[i], NULL, users, &us_num[i]);
     }
     pthread_create(&brad_thread, NULL, bradThread, NULL);

     //THREAD JOIN
     for(int i=0; i<USERS; i++)
     {
         pthread_join(users_threads[i], NULL);
     }
     pthread_join(brad_thread, NULL);

    return 0;
}
