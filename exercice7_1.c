#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    char choix;

    pid = fork();

    if (pid < 0) 
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
     {
        printf("Fils démarré (PID = %d)\n", getpid());

        while (1) 
        {
            printf("Fils en cours de calcul...\n");
            sleep(1);
        }
    }
    else 
    {
        while (1) 
        {
            printf("\nMenu:\n");
            printf("s : stopper le fils\n");
            printf("r : reprendre le fils\n");
            printf("q : quitter\n");
            printf("Votre choix: ");

            scanf(" %c", &choix);

            switch (choix) 
            {

                case 's':
                    kill(pid, SIGSTOP);
                    printf("Fils stoppé\n");
                    break;

                case 'r':
                    kill(pid, SIGCONT);
                    printf("Fils repris\n");
                    break;

                case 'q':
                    kill(pid, SIGKILL);
                    wait(NULL); // éviter zombie
                    printf("Fils tué, fin du programme\n");
                    exit(0);

                default:
                    printf("Choix invalide\n");
            }
        }
    }

    return 0;
}