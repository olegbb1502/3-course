#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <iostream>
#define BUFFER_SIZE 25

using namespace std;

sem_t mutex_cons;
sem_t mutex_prod;
sem_t fill_count;
sem_t empty_count;
sem_t accesst;

queue<int> my_queue;


int generate_item() {
	srand(time(NULL));
	return rand() %100;
}

void *producer(void *number) {
	int num = *(int *)number;
	srand(time(NULL));
    while (true) {
        sem_wait(&empty_count);
        sem_wait(&mutex_prod);
        if (my_queue.size() > 1) {
            printf("Producer %d started producing item.\n", num);
            int item = generate_item();
            Sleep((rand() %6+2)*500);
            my_queue.push(item);
            printf("Producer %d produced item. Element: %d, Queue size: %d.\n", num, my_queue.back(), my_queue.size());
        }
        else {
            sem_wait(&accesst);
            printf("Producer %d started producing item.\n", num);
            int item = generate_item();
            Sleep((rand() %6+2)*500);
            my_queue.push(item);
            printf("Producer %d produced item. Element: %d, Queue size: %d.\n", num, my_queue.back(), my_queue.size());
            sem_post(&accesst);
        }
        sem_post(&mutex_prod);
        sem_post(&fill_count);
       // if(my_queue.size() > 1)
        //	sem_post(&accesst);
        /*sem_wait(&accesst);
    	if(my_queue.size()==1) {
    		sem_wait(&mutex_cons);
    		checked = false;
    	}
    	if(!checked) {
    	if(my_queue.size() > 1) {
    		sem_post(&mutex_cons);
    		checked = true;
    	}
    	}
    	sem_post(&accesst);*/

        Sleep((rand() %6+3)*500);
    }
}

void *consumer(void *number) {
	int num = *(int *)number;
	srand(time(NULL));
    while (true) {
        sem_wait(&fill_count);
        sem_wait(&mutex_cons);
        if (my_queue.size() > 0) {
            printf("Consumer %d started consuming item. \n", num);
            Sleep((rand() %6+1)*500);
            int item = my_queue.front();
            my_queue.pop();
            printf("Consumer %d consumed item. Element: %d, Queue size: %d.\n", num, item, my_queue.size());
        }
        else{
            sem_wait(&accesst);
            printf("Consumer %d started consuming item. \n", num);
            Sleep((rand() %6+1)*500);
            int item = my_queue.front();
            my_queue.pop();
            printf("Consumer %d consumed item. Element: %d, Queue size: %d.\n", num, item, my_queue.size());
            sem_post(&accesst);
        }
        sem_post(&mutex_cons);
        sem_post(&empty_count);
        Sleep((rand() %6+3)*500);

    }
}

int main()
{
	int x;
	printf("Enter number of producers\n");
    scanf("%d",&x);
    int numProducers = x;
    printf("Enter number of consumers\n");
    scanf("%d",&x);
    int numConsumers = x;
    pthread_t prodid[numProducers];
	pthread_t consid[numConsumers];
	int i = 0;
    printf("Starting...\n");
	int numProd[numProducers];
	int numCons[numConsumers];
    for (i = 0; i < numProducers; i++) {
        numProd[i] = i;
    }
    for (i = 0; i < numConsumers; i++) {
        numCons[i] = i;
    }

    sem_init(&mutex_cons, 0, 1);
    sem_init(&mutex_prod, 0, 1);
    sem_init(&fill_count, 0, 0);
    sem_init(&accesst, 0, 1);
	sem_init(&empty_count, 0, BUFFER_SIZE);

    for (i = 0; i < numProducers; i++) {
        pthread_create(&prodid[i], NULL, producer, (void *)&numProd[i]);
    }
    for (i = 0; i < numConsumers; i++) {
    	pthread_create(&consid[i], NULL, consumer, (void *)&numCons[i]);
	}
    for (i = 0; i < numProducers; i++) {
        pthread_join(prodid[i],NULL);
    }
    for (i = 0; i < numConsumers; i++) {
        pthread_join(consid[i],NULL);
    }

    return 0;
}
