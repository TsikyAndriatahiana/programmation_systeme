#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

int compt=0;
int limite;

pthread_mutex_t mutex;

void *incrementation(void*arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(compt >= limite)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        compt++;

        pthread_mutex_unlock(&mutex);

        sleep(rand()%5+1);
    }
    return NULL;
}
void *afficher(void*arg)
{

    while(1)
    {
        sleep(2);

        pthread_mutex_lock(&mutex);
        if(compt >= limite)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("le compteur vaut compt= %d\n", compt);

        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s limite\n",argv[0]);
        return 1;
    }

    limite =atoi(argv[1]);

    srand(time(NULL));

    pthread_t th1,th2;

    pthread_create(&th1,NULL,incrementation,NULL);
    pthread_create(&th2,NULL,afficher,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);


    return 0;
}
