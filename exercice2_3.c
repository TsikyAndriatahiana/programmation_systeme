#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main ()
{
    int i;
    for(i=0;i<5;i++)
    {
         pid_t pid_fils=fork();
        if(pid_fils==0)
        {
            printf("je suis le fils %d\n",i);
            break;
        }
    }
    return(0);
}