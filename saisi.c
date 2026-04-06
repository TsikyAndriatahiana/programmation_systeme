#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        printf("Usage: %s PID_affiche\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    int x;

    printf("Entrez un entier : ");
    scanf("%d", &x);

    FILE *f = fopen("/tmp/entier.txt", "w");
    if (f == NULL) 
    {
        perror("fopen");
        exit(1);
    }

    fprintf(f, "%d", x);
    fclose(f);

    kill(pid, SIGUSR1);// envoyer le signal

    return 0;
}