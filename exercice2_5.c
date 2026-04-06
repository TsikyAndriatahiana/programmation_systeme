#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t pid_fils1,pid_fils2;
    int debut,fin,t1,t2;

    debut=time(NULL);

    pid_fils1=fork();
    if(pid_fils1==0)
    {
        srand(time(NULL) ^ getpid()); //pour que le rand genère differente nombre aléatoire pour chaque processus fils1
        t1=rand() % 10 + 1; //nombre aléatoire entre 10 et 1
        printf("je suis le fils1 dort pendant %d sec\n",t1);
        sleep(t1); 
        exit(0);
    }

    pid_fils2=fork();
    if(pid_fils2==0)
    {
        srand(time(NULL) ^ getpid());
        t2=rand() % 10 + 1;
        printf("je suis le fils2 dort pendant %d sec\n",t2);
        sleep(t2);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    fin=time(NULL);
    printf("total= %d sec\n",fin-debut);

    return (0);

}