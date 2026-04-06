#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    FILE *f;
    int x;

    f = fopen("/tmp/entier.txt", "r");
    if (f == NULL) 
    {
        perror("fopen");
        exit(1);
    }

    fscanf(f, "%d", &x);
    fclose(f);

    printf("Valeur reçue : %d\n", x);
}

int main()
{
    printf("PID affiche : %d\n", getpid());

    signal(SIGUSR1, handler);// installer le handler pour SIGUSR1

    while (1)
    {
        sleep(1); // attente passive
    }

    return 0;
}