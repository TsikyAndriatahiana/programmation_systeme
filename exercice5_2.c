#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

void *allocation_aleatoire(void *arg)
{
    int taille = *(int*)arg;

    int *tab=malloc(taille*sizeof(int));
    int i;

    for(i=0;i < taille;i++)
    {
        tab[i]=rand()%100;
    }
    return tab;
}
int main()
{
    srand (time(NULL));
    pthread_t my_thread;

    int taille=6;

    int *tableau;

    pthread_create(&my_thread,NULL,allocation_aleatoire,(void*)&taille);

    pthread_join(my_thread,(void**)&tableau);

    int i;
    for(i=0;i<taille;i++)
    {
        printf("[%d] ",tableau[i]);
    }

    free(tableau);
    return(0);
}