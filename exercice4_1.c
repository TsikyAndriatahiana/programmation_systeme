#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define SIZECAR 100
int main()
{
    pid_t pid_fils;
    int tube1[2];
    int tube2[2];
    char caractereR[100],caractereW[100];

    //creation du pipe
    if(pipe(tube1)!=0 || pipe(tube2)!=0)
    {
        fprintf(stderr, "Erreur dans pipe\n");
        exit(1);
    }

    pid_fils = fork();

    if (pid_fils == -1)
    {
        fprintf(stderr, "Erreur dans fork\n");
        exit(1);
    }
    if(pid_fils == 0)
    {
        //----------------pipe1_-------------------
        printf("saisissez un mot\n");
        scanf("%s",caractereW);
        close(tube1[0]);
        write(tube1[1] , caractereW , SIZECAR);

        //---------------pipe_2--------------------

        int resultat;
        read(tube2[0],&resultat,sizeof(int));

        if(resultat == 1 )
        {
            printf("le mot existe dans le fichier\n");
        }
        else
        {
            printf("le mot n'existe pas dans le fichier\n");
        }

        close(tube2[1]);
    }
    else
    {
        //-------------------pipe_1----------------
        close(tube1[1]);
        read(tube1[0], caractereR , SIZECAR);
        FILE *mot;
        char ligne[100];
        int compt=0;

        mot=fopen("fichier.txt","r");//ouverture du fichier contenant le mot
        if(mot==NULL)
        {
            perror("fopen");
            exit(1);
        }

        while(fscanf(mot,"%s",ligne)!=EOF) //verification mot par mot
        {
            if(strcmp(ligne,caractereR)==0)//comparaison des chaines de caratcère
            {
                compt=1;
                break;
            }
        }

       fclose(mot);

       //---------------pipe_2--------------------
       write(tube2[1],&compt,sizeof(int));
        
        close(tube2[0]);

    }

    return(0);

}