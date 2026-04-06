#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
   char *fd_read_pere=getenv ("FD");

    if(fd_read_pere == NULL)
    {
        printf("Erreur getenv\n");
        return 1;
    }


        int fd=atoi(fd_read_pere);
        char buffer[100];
        read(fd,buffer,sizeof(buffer));
        printf("message : %s\n",buffer);

        close(fd);

        return(0);

}