#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

#define NBR_ITER 10

sem_t S1,S2;

void*T1(void *arg)
{
    int i;
    for(i=0;i<NBR_ITER;i++)
    {
        printf("T1] itération %d\n",i);

        sleep(2);

        sem_post(&S1); //signaler que T1 arrivée

        sem_wait(&S2); //attend T2
    }

    return NULL;
}
void*T2(void *arg)
{
    int i;
    for(i=0;i<NBR_ITER;i++)
    {
        printf("T2] itération %d\n",i);

        sleep(2);

        sem_post(&S2); //signaler que T2 arrivée

        sem_wait(&S1); //attend T1
    }

    return NULL;
}

int main()
{
    pthread_t th1,th2;

    srand(time(NULL));

    sem_init(&S1,0,1);
    sem_init(&S1,0,0);

    pthread_create(&th1,NULL,T1,NULL);
    pthread_create(&th2,NULL,T2,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    sem_destroy(&S1);
    sem_destroy(&S2);

    return 0;
}

