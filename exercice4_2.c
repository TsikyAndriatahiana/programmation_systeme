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
    char caractereW[100];

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
        //----------------pipe1_------------------

        printf("saisissez un mot\n");
        scanf("%s",caractereW);

        close(tube1[0]);
        close(tube2[1]);
        
        dup2(tube1[1] ,STDOUT_FILENO);
        dup2(tube2[0],STDIN_FILENO);

        close(tube1[1]);
        close(tube2[0]);
        
        //---------------pipe_2-------------------

        printf("%s\n",caractereW);//envoyer père
        fflush(stdout);


        int resultat;

        scanf("%d",&resultat);

        if(resultat == 1 )
        {
            fprintf(stderr,"le mot existe dans le fichier\n");
        }
        else
        {
            fprintf(stderr,"le mot n'existe pas dans le fichier\n");
        }
        
    }
    else
    {
        //-------------------pipe_1----------------
        close(tube1[1]);//pas ecriture
        close(tube2[0]);//pas lecture

        dup2(tube1[0], STDIN_FILENO);
        dup2(tube2[1],STDOUT_FILENO);

        close(tube1[0]);
        close(tube2[1]);

        
        char caractereR[50];
        scanf("%s",caractereR);//lire mot venant du fils

        char ligne[50];
        int compt=0;

        FILE *mot=fopen("fichier.txt","r");//ouverture du fichier contenant le mot
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
       printf("%d\n",compt);//envoyer au processus fils
       fflush(stdout);

       exit(0);
    }

    return(0);

}