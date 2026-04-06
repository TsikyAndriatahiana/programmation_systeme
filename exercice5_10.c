#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

#define SIZE 10

char buffer[SIZE];
int compt;

int N ,M;

sem_t mutex;
sem_t vide;
sem_t plein;

void *producteur(void *arg)
{
    int id=*(int*)arg;

    while(1)
    {
        sleep(rand()%3+1);

        char item ='A' +(rand()%26);

        sem_wait(&vide);//attendre une place libre
        
        sem_wait(&mutex);

        buffer[compt++]=item;

        printf("P%d] produit %c (compt=%d)\n",id,item,compt);

        sem_post(&mutex);

        sem_post(&plein); //signaler un nouveau element
    }
    return NULL;
}

void *consommateur(void *arg)
{
    int id=*(int*)arg;

    while(1)
    {
        sleep(rand()%3+1);

        sem_wait(&plein);//attendre un element

        sem_wait(&mutex);//eviter que le compteur ecrase un autre

        char item=buffer[compt--];

        printf("    C%d] consomme %c (compt=%d)\n",id,item,compt);

        sem_post(&mutex);

        sem_post(&vide);//signaler une place vide

    }
    return NULL;
}

int main()
{

    printf("nombre de productions\n");
    scanf("%d",&N);
    printf("nombre de consommeteur\n");
    scanf("%d",&M);
     
    pthread_t prod[N],cons[M];
    int idP[N],idC[M];

    srand(time(NULL));

    sem_init(&mutex,0,1);
    sem_init(&vide,0,SIZE);
    sem_init(&plein,0,0);

    int i;

    for(i=0;i<N;i++)
    {
        idP[i]=i;
        pthread_create(&prod[i],NULL,producteur,&idP[i]);
    }
   

    for(i=0;i<M;i++)
    {
        idC[i]=i;
        pthread_create(&cons[i],NULL,consommateur,&idC[i]);
    }
   
    for(i=0;i<N;i++)
    {
        pthread_join(prod[i],NULL);
    }
    for(i=0;i<M;i++)
    {
        pthread_join(cons[i],NULL);
    }

    sem_destroy(&vide);
    sem_destroy(&plein);

    return 0;
}