#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define N 5

pid_t fils[N];

void fin_fils(int sig)
{
    printf("Fils %d : je meurs...\n", getpid());
    exit(0);
}

void fin_pere(int sig)
{
    printf("Père %d : fin du programme...\n", getpid());
    exit(0);
}

int main()
{
    int i;
    char choix;
    int num;

    signal(SIGTERM, fin_pere);// installer handler du père

    for (i = 0; i < N; i++)
    {
        fils[i] = fork();

        if (fils[i] == 0) 
        {
            
            signal(SIGTERM, fin_fils);// code fils

            while (1) 
            {
                printf("Fils %d actif\n", getpid());
                sleep(4);
            }
        }
    }

   

    while (1)//code père
    {
        printf("\nMenu:\n");
        printf("s : stopper un fils\n");
        printf("r : réveiller un fils\n");
        printf("k : tuer un fils\n");
        printf("Choix: ");
        scanf(" %c", &choix);

        printf("Numéro du fils (0 à 4): ");
        scanf("%d", &num);

        if (num < 0 || num >= N) 
        {
            printf("Numéro invalide\n");
            continue;
        }

        switch (choix)
        {
            case 's':
                kill(fils[num], SIGSTOP);
                printf("Fils %d stoppé\n", fils[num]);
                break;

            case 'r':
                kill(fils[num], SIGCONT);
                printf("Fils %d réveillé\n", fils[num]);
                break;

            case 'k':
                kill(fils[num], SIGTERM); //pas SIGKILL
                waitpid(fils[num],NULL,0);
                printf("Fils %d tué\n", fils[num]);
                break;

            default:
                printf("Choix invalide\n");
        }
    }

    return 0;
}