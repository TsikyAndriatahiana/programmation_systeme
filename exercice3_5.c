#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include <sys/wait.h>

int main()
{
    char nom_fichier[50],commande[100];
    char verif;
    bool quitter=true;

    do
{
    printf("Entrer le nom du fichier: ");
    scanf("%s",nom_fichier); //saisi du nom de fichier

        switch(fork()) 
        {
            case -1 :
                printf("Problème dans fork()\n");
                break;

            case 0 :
                execl("/usr/bin/emacs","emacs",nom_fichier,NULL);
                break;
        }

        printf("tapez Q si vous voulez quitter:");
                scanf(" %c",&verif);
                if(verif == 'Q' || verif == 'q')
                {
                    quitter=false;
                }
        wait(NULL);
} while(quitter == true);

    return (0);
}