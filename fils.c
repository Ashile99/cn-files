
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    int s,c,pid,len;
    char filename[100],buffer[1024];
    FILE *fp;
    int status;

    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9999);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(s,(struct sockaddr*)&server,sizeof(server));

    listen(s,5);

    printf("Server waiting for clients...\n");

    while(1)
    {
        c=accept(s,NULL,NULL);

        printf("Client connected!\n");

        pid=fork();

        if(pid==0)
        {
            close(s);

            recv(c,filename,sizeof(filename),MSG_WAITALL);

            printf("Requested file: %s\n",filename);

            fp=fopen(filename,"rb");

            if(fp==NULL)
                status=0;
            else
                status=1;

            send(c,&status,sizeof(status),0);

            if(status==1)
            {
                while((len=fread(buffer,1,sizeof(buffer),fp))>0)
                {
                    send(c,buffer,len,0);
                }

                fclose(fp);
            }

            close(c);
            exit(0);
        }
        else
        {
            close(c);

            while(waitpid(-1,NULL,WNOHANG)>0);
        }
    }

    close(s);

    return 0;
}
