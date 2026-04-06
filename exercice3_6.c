#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char*arg[])
{
    if(argc !=4) {
        printf("Usage: %s n k fichier\n",arg[0]);
        return 1;
    }

    int n=atoi(arg[1]); //convertie char  en int 
    int k=atoi(arg[2]);
    char *fichier="exo.txt"; //affectation de l'argument 3 dans *fichier
 
    FILE *f;

    if(k == 0 || k == 1)
    {
        f=fopen(fichier,"w");
        if(f == NULL)
        {
            perror("fopen fichier");
            exit(1);
        }
        fprintf(f, "1\n");
        fclose(f);
        return 0;
    }

    char f1[100],f2[100];

    sprintf(f1,"/tmp/fic_%d_%d_1.txt",n-1 , k);
    sprintf(f2,"/tmp/fic_%d_%d_1.txt",n-1 , k-1);

    
  

    pid_t pid_fils1=fork();

    if(pid_fils1 == 0)
    {
        char sn[100],sk[100];
        sprintf(sn,"%d",n-1);
        sprintf(sk,"%d",k);
        execl(arg[0],arg[0],sn,sk,f1,NULL);
        perror("execl faild\n");
        exit(1);
    }

   
    pid_t pid_fils2=fork();

    if(pid_fils2 == 0)
    {
        char sn[100],sk[100];
        sprintf(sn,"%d",n-1);
        sprintf(sk,"%d",k-1);
        execl(arg[0],arg[0],sn,sk,f2,NULL);
        perror("execl faild\n");
        exit(1);
    }

    wait(NULL);
    wait(NULL);

    int r1,r2;

    f=fopen(f1,"r");
    if(f == NULL)
    {
        perror("fopen fichier");
        exit(1);
    }
    fscanf(f,"%d",&r1);
    fclose(f);

    f=fopen(f2,"r");
    if(f == NULL)
    {
        perror("fopen fichier");
        exit(1);
    }
    fscanf(f,"%d",&r2);
    fclose(f);

    int resultat=r1+r2;

    f=fopen(fichier, "w");
    if(f == NULL)
    {
        perror("fopen fichier");
        exit(1);
    }
    fprintf(f, "%d\n",resultat);
    fclose(f);

    char *commande
    sprintf(commande ,"cat %s",fichier);
    system(commande);
    return (0);
    
}


//utilisation de fichier (if k==O ou K==n)
//utiliation de fork et execl
//processus fils1:calcul kCn-1
//processus fils2 :calcul K-1Cn-1
//calcul somme

