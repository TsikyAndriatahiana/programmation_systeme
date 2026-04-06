#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,  char *argv[])
{
    if(argc>2)
    {
        printf("Erreur argument\n");
        return 1;
    }

        int fd=atoi(argv[1]);
        char buffer[100];
        read(fd,buffer,sizeof(buffer));
        printf("message : %s\n",buffer);

        close(fd);

        return(0);

}