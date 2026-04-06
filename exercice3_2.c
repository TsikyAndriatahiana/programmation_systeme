#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *arg[])
{

    if(argc != 2)
    {
        printf("Usage : %s repertoire_R\n",arg[0]);

        return (0);
    }
    char *repertoire_courant;
    char commande[50];

    printf("%s\n",arg[1]);
    repertoire_courant = getenv("PWD");//recuperation du repertoire courant
    sprintf(commande,"cp -r %s %s",repertoire_courant,arg[1]); //affectation du commande(cp -r ...) dans un variable nommé commande
    system(commande); //execution de la commande

    return (0);

}