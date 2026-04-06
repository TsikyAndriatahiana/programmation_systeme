#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

typedef struct
{
    int *tab;
    int n;
    int x;

}Tableau;

void *generer(void *arg)
{
    Tableau *t = (Tableau*)arg;

    t->tab=malloc(t->n*sizeof(int));
    int i;

    for(i=0;i<t->n;i++)
    {
        t->tab[i]=rand()%100;
    }
 return t->tab;
}

void *verification_x(void *arg)
{
    Tableau *t = (Tableau*)arg;
    int *resultat=malloc(sizeof(int));

    *resultat=0;
    int i;

    for(i=0;i< t->n;i++)
    {
        if(t->tab[i]==t->x)
        {
            *resultat=1;
        }
    }
   return resultat;
    
}

int main()
{
    srand(time(NULL));
    pthread_t my_thread1;
    pthread_t my_thread2;
    Tableau t;

    t.n=6;
    int * tabl;
    
    pthread_create(&my_thread1,NULL,generer,&t);

    pthread_join(my_thread1,(void**)&tabl);

    int i;
    for(i=0;i<t.n;i++)
    {
        printf("[%d] ",tabl[i]);
    }
    printf("\n");

    printf("saisissez un nombre: ");
    scanf("%d",&t.x);

    int *resultat;

    pthread_create(&my_thread2,NULL,verification_x,&t);

    pthread_join(my_thread1,(void**)&resultat);

    if(*resultat == 1)
    {
        printf("le nombre %d existe dans le tableau\n",t.x);
    }
    else
    {
        printf("le nombre %d n'existe pas dans le tableau\n",t.x);
    }
    return(0);
}
