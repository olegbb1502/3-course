#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <semaphore.h>
#include <time.h>

#define N 5
#define TIME_MIN 2000000
#define TIME_MAX 5000000

using namespace std;

sem_t spoons[N];

void *eat(void *params)
{
    int num = *(int*) params;
    useconds_t time = 0;
    while(true)
    {
        if(sem_trywait(&spoons[num]) == 0) //try get left spoon
        {
            if(sem_trywait(&spoons[ (num + 1) % N ]) == 0) //try get right spoon
            {
                cout << "Philosoph " << num + 1 << " start eat\n";

                time = TIME_MIN + rand() % (TIME_MAX - TIME_MIN);
                usleep(time);

                cout << "Philosoph " << num + 1 << " end eat\n";
                sem_post(&spoons[ (num + 1) % N ]);
            }
            sem_post(&spoons[num]);
        }

       time = TIME_MIN + rand() % (TIME_MAX - TIME_MIN);
        usleep(time);
    }
}

int main()
{
    srand(time(0));

    //init semaphore
     for(int i=0; i < N; i++)
    {
        sem_init(&spoons[i], 0, 1);
    }


    pthread_t philos[N];
    int num_philos[N];
    int err;

    for(int i=0;i<N;i++)
    {
        num_philos[i] = i;
        err = pthread_create(&philos[i],NULL,eat,&num_philos[i]);

        if (err != 0)
        {
            return 0;
        }
    }

    for(int i=0;i<N;i++)
    {
        pthread_join(philos[i], NULL);
    }

    return 0;
}
