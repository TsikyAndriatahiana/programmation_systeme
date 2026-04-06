#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

double u;
int compteur=0;

pthread_mutex_t mutex;

double f1(double x)
{
    return 0.25 * (x-1)*(x-1);
}
double f2(double x)
{
    return (1.0/6.0) * (x-2)*(x-2);
}
void *thread1(void *arg)
{
    while(1)
    {
        sleep(rand()%5+1);

        pthread_mutex_lock(&mutex);

        compteur++;
        u=f1(u);

        printf(" T1] iteration=%d , u=%f \n",compteur,u);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *thread2(void *arg)
{
    while(1)
    {
        sleep(rand()%5+1);

        pthread_mutex_lock(&mutex);

        compteur++;
        u=f2(u);

        printf(" T2] iteration=%d , u=%f \n",compteur,u);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t T1,T2;

    u=1;

    srand(time(NULL));

    
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&T1,NULL,thread1,NULL);
    pthread_create(&T2,NULL,thread2,NULL);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    pthread_mutex_destroy(&mutex);

    return(0);
}