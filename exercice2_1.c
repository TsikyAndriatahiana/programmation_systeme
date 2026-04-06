#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid_fils=fork();

    if(pid_fils==-1)
    {
        printf("Erreur de création du nouveau processus\n");
    }
    if(pid_fils==0)
    {
        printf("je suis le fils\n");
    }
    else
    {
        printf("je suis le père\n");
    }
    return (0);
  
}