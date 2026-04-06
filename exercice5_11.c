#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define SIZE 15

char base[SIZE];   // base de données

int readcount = 0;

sem_t mutex;  // protège readcount
sem_t wrt;    // accès à la base

int N, M;

void* lecteur(void* arg) 
{
    int id = *(int*)arg;

    while (1) {
        sleep(rand() % 3 + 1);

        sem_wait(&mutex);// entrée section lecteur
        readcount++;

        if (readcount == 1)
        {
            sem_wait(&wrt); // premier lecteur bloque les écrivains
        }

        sem_post(&mutex);

        int index = rand() % SIZE;// lecture
        printf("[Lecteur %d] lit base[%d] = %d\n", id, index, base[index]);

        sem_wait(&mutex);// sortie section lecteur
        readcount--;

        if (readcount == 0)
        {
            sem_post(&wrt); // dernier lecteur libère les écrivains
        }

            sem_post(&mutex);
    }

    return NULL;
}

void* redacteur(void* arg) 
{
    int id = *(int*)arg;

    while (1) {
        sleep(rand() % 10 + 1);

        sem_wait(&wrt);  // accès exclusif

        int index = rand() % SIZE;
        base[index] = rand() % 100;

        printf("    [Redacteur %d] écrit base[%d] = %d\n", id, index, base[index]);

        sem_post(&wrt);
    }

    return NULL;
}

int main() {
    printf("Nombre de lecteurs : ");
    scanf("%d", &N);

    printf("Nombre de redacteurs : ");
    scanf("%d", &M);

    pthread_t lecteurs[N], redacteurs[M];
    int idL[N], idR[M];

    srand(time(NULL));
    
    for (int i = 0; i < SIZE; i++)// initialisation base
    {
        base[i] = 0;
    }

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < N; i++) 
    {
        idL[i] = i;
        pthread_create(&lecteurs[i], NULL, lecteur, &idL[i]);
    }

    for (int i = 0; i < M; i++) 
    {
        idR[i] = i;
        pthread_create(&redacteurs[i], NULL, redacteur, &idR[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(lecteurs[i], NULL);

    for (int i = 0; i < M; i++)
        pthread_join(redacteurs[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}