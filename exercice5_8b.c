#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

int N;
int count = 0;

sem_t mutex;
sem_t bloc;

void*my_thread(void *arg)
{
    int nb_thread=*(int*)arg;

    int i,j;
    for(i=0;i<5;i++)
    {
        int t=rand()%5+1;
        printf("thread %d iteration %d sleep %d\n",nb_thread,i,t);
        sleep(t);

        sem_wait(&mutex); //un seul thread à la fois (protège count)
        count++;

        if(count == N)
        {
            count = 0;
            for(j=0;j<N;j++)
            {
                sem_post(&bloc);
            }
        }

        sem_post(&mutex);

        sem_wait(&bloc);
    }

    return NULL;
}
int main( int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s N\n",argv[0]);
        return 1;
    }

    N=atoi(argv[1]);

    pthread_t thread[N];
    int nb_thread[N];
    srand(time(NULL));


    sem_init(&mutex,0,1);
    sem_init(&bloc,0,0);

    int i;
    for(i=0;i<N;i++)
    {
        nb_thread[i]=i;
        pthread_create(&thread[i],NULL,my_thread,&nb_thread[i]);
    }
    
    for(i=0;i<N;i++)
    {
        pthread_join(thread[i],NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&bloc);

    return 0;
}

