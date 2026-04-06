#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define N 100

double tableau[N];

pthread_mutex_t mutex;

void* mise_a_jours(void*arg)
{
    double temp[N];
    int i;

    while(1)
    {
        pthread_mutex_lock(&mutex);//ouverture

        for(i=1;i<98;i++)
        {
            temp[i]=(tableau[i-1]+tableau[i]+tableau[i+1])/3.0; //calcul ,temporaire pour la manipultaion du tableau
        }
        
        for(i=1;i<98;i++)
        {
            tableau[i]=temp[i]; //copier dan le tableau
        }

        pthread_mutex_unlock(&mutex); //fermeture

        sleep(rand()%3+1); // attend 1 à 3;
    }
    return NULL;
}

void *afficher(void *arg)
{
    int i;
    while(1)
    {
        pthread_mutex_lock(&mutex);//ouverture

        for(i=0;i<N;i++)
        {
            printf("[%2.f] ",tableau[i]);
        }
        printf("\n\n");

        pthread_mutex_unlock(&mutex); //fermeture

        sleep(4); // attend 1 à 3;
    }
    return NULL;
    
}

int main()
{
    pthread_t th1,th2;

    srand(time(NULL));
    pthread_mutex_init(&mutex,NULL);
    
    tableau[0]=0;
    tableau[N-1]=0;
    int i;

    for(i=1;i<(N-1);i++)
    {
        tableau[i]=(double)(rand()%100);
    }

    pthread_create(&th1,NULL,mise_a_jours,NULL);
    pthread_create(&th2,NULL,afficher,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    pthread_mutex_destroy(&mutex);

    return(0);
}