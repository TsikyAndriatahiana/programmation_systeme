#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    char nom_fichier[50];
    char commande[100];

    printf("Entrer le nom du fichier: ");
    scanf("%s",nom_fichier); //saisi du nom de fichier
    execl("/usr/bin/emacs","emacs",nom_fichier,NULL);//execution des commande avec les options et argument(remplace sprintf et system)

    return (0);
}