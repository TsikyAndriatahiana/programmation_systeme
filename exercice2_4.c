#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pid_t pid_fils;

int main ()
{
    int i;
    printf("je suis le père\n");
    for(i=0;i<5;i++)
    {
         pid_fils=fork();
        if(pid_fils==0)
        {
            printf("je suis le fils %d\n",i);
            break;
        }
    }
    return(0);
}