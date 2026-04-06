#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>

int main()
{
    bool quitter=true;
    char repertoire[50],commande[100];
    char verif;
    char *repertoire_courant;

    while( quitter!= false)
    {
        printf("Entrer le nom du repertoire: ");
        scanf("%s",repertoire);
        repertoire_courant=getenv("PWD");
        sprintf(commande,"cp -r %s %s",repertoire_courant,repertoire);
        system(commande);

        printf("tapez Q si vous voulez quitter:");
        scanf(" %c",&verif);

        if(verif == 'Q' || verif == 'q')
        {
            quitter=true;
        }

    }

    return(0);
}