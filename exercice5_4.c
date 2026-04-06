#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

typedef struct
{
    int *tab;
    int taille;

}Tableau;

void *generate(void *arg)
{
    Tableau *t = (Tableau*)arg;
    int i;

    for(i=0;i<t->taille ;i++)
    {
        t->tab[i]=rand()%100;
    }
    pthread_exit(NULL);
    
}

void *inclusion(void *arg)
{
    Tableau **tab=(Tableau**)arg;

    Tableau *T1=tab[0];
    Tableau *T2=tab[1];

    int resultat=1;

    int i,k,found;

    for(i=0;i<T1->taille;i++)
    {
        found=0;
        for(k=0; k < T2->taille ;k++)
        {
            if(T1->tab[i]== T2->tab[k])
            {
                found=1;
                break;
            }
        }

        if(found==0)
        {
            resultat=0;
            break;
        }
    }

    if(resultat==1)
    {
        printf("T1 est inclus dans T2\n");
    }
    else
    {
        printf("T1 n'est pas inclus dans T2\n");
    }

    pthread_exit(NULL);
}
void *surveillance(void*arg)
{
    char c;

    while(1)
    {
        c=getchar();

        if(c=='A')
        {
            printf("\n programme annulé par l'utillisateur\n");
            exit(0);
        }
    }
}

int main()
{

    srand(time(NULL));
    pthread_t th1,th2,th3,th4;

    Tableau T1,T2;

    T1.taille=5;
    T2.taille=10;

    T1.tab=malloc(T1.taille*sizeof(int));
    T2.tab=malloc(T2.taille*sizeof(int));

    pthread_create(&th1,NULL,generate,&T1);
    pthread_create(&th2,NULL,generate,&T2);

    pthread_join(th1,NULL);

    int i;
    for(i=0;i<T1.taille;i++)
    {
        printf("[%d] ",T1.tab[i]);
    }
    printf("\n");
    pthread_join(th2,NULL);

    for(i=0;i<T2.taille;i++)
    {
        printf("[%d] ",T2.tab[i]);
    }
    
    printf("\n");
    Tableau *tab[2];
    tab[0]=&T1;
    tab[1]=&T2;

    pthread_create(&th3,NULL,inclusion,tab);
    pthread_join(th3,NULL);

    pthread_create(&th4,NULL,surveillance,NULL);
    pthread_join(th4,NULL);
    free(T1.tab);
    free(T2.tab);

    return 0;
}