#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *arg[])
{
    if(argc != 3)
    {
        printf("Usage : %s argument1 argument2\n",arg[0]);
        return(0);
    }
    int entier1=atoi(arg[1]); //converti un chaine de caractere en entier
    int entier2=atoi(arg[2]);
    int resultat;
    resultat=entier1+entier2;
    printf("le resultat des sommes:\n%d + %d = %d\n",entier1,entier2,resultat);

    return(0);
}