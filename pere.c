#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int tube[2];
    if(pipe(tube)!= 0)
    {
        fprintf(stderr, "Erreur dans pipe\n");
        exit(1);
    }

    pid_t pid_fils=fork();

    if(pid_fils==-1)
    {
        fprintf(stderr, "Erreur dans fork\n");
        exit(1);
    }
    if(pid_fils==0)
    {
        close(tube[1]);
        char fd[10];
        sprintf(fd,"%d",tube[0]);//fd=file_descriptor
        
        setenv("FD", fd , 1 );//1:si le nom FD existe déjà ecraser le 

        execl("./fils","./fils",NULL);//execution ./fils
    }
    else
    {
        close(tube[0]);//pas de lecture

        char message[]="bonjour fils";

        write(tube[1],message,sizeof(message));

        close(tube[1]);

        wait(NULL);
    }
    return(0);
}