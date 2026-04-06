#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int *tab;
int n;
int i_global;

void handler_segv(int sig)//verification de i_global si c'est correcte ou pas si non redemander
{
    printf("\nErreur : index invalide ! Recommencez.\n");

    printf("Donner i : ");
    scanf("%d", &i_global);

    if (i_global >= 0 && i_global < n)
    {
        printf("tab[%d] = %d\n", i_global, tab[i_global]);
    }
    else
    {
        kill(getpid(), SIGSEGV); //relancer le signal sur le processus lui-même//arret
    }
}

int main()
{
    
    signal(SIGSEGV, handler_segv);// initialisation handler

    printf("Donner n : ");
    scanf("%d", &n);

    tab = (int *)malloc(n * sizeof(int));//allocation

    if (tab == NULL)
    {
        printf("Erreur malloc\n");
        return 1;
    }

    for (int i = 0; i < n; i++)// saisie du tableau
    {
        printf("tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }

    printf("Donner i : ");// saisie de i
    scanf("%d", &i_global);

    
    printf("tab[%d] = %d\n", i_global, tab[i_global]);// accès potentiellement dangereux

    free(tab);

    return 0;
}