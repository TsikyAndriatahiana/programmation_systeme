#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

char buffer;

sem_t vide;
sem_t plein;

void *emmetteur(void*arg)
{
    while(1)
    {
        sleep(rand()%3+1);

        char octet='A'+(rand()%26);

        sem_wait (&vide);//attendre de buffer soit vide

        buffer=octet;

        printf("emmeteur] envoie: %c\n",buffer);

        sem_post(&plein);//signaler que buffer est plein
    }
    return NULL;
}
void *recepteur(void*arg)
{
    while(1)
    {
        sleep(rand()%3+1);

        sem_wait (&plein);//attendre de buffer soit vide

        char recup_buffer;

        printf("recepteur] reçoie: %c\n",buffer);

        recup_buffer=buffer;

        sem_post(&vide);//signaler que buffer est plein
    }
    return NULL;
}

int main()
{
    pthread_t th1,th2;

    srand(time(NULL));

    sem_init(&vide,0,1);
    sem_init(&plein,0,0);

    pthread_create(&th1,NULL,emmetteur,NULL);
    pthread_create(&th2,NULL,recepteur,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    sem_destroy(&vide);
    sem_destroy(&plein);
}