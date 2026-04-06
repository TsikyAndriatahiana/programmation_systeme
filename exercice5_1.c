#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

typedef struct
{
    int *tab;
    int taille;

}Tableau;

void *ma_fonction_thread(void *arg)
{
    Tableau *t = (Tableau*)arg;
    int i;

    for(i=0;i<t->taille ;i++)
    {
        printf(" [%d] ",t->tab[i]);
    }
    printf("\n");

}

int main()
{
    pthread_t my_thread;

    int tab[]={1, 2, 3, 4, 5, 6};

    Tableau t;

    t.tab=tab;
    t.taille=6;

    pthread_create(&my_thread,NULL,ma_fonction_thread,&t);

    pthread_join(my_thread,NULL);

    return 0;
}