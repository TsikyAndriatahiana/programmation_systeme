#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t pid_fils1,pid_fils2;

    pid_fils1=fork();

    if(pid_fils1==-1)
    {
        printf("Erreur de création du nouveau processus\n");
    }
    if(pid_fils1==0)
    {
        printf("je suis le fils 1\n");
    }
    else
    {
        pid_fils2=fork();
        if(pid_fils2==-1)
        {
            printf("Erreur de création du nouveau processus\n");
        }
        if(pid_fils2==0)
        {
            printf("je suis le fils 2\n");
        }
        else
        {
            printf("je suis le père\n");
            
        }

    }

    return (0);

}