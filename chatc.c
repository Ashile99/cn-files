#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/select.h>

int main()
{
    int s,n;

    char msg[500];

    fd_set readfds;

    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9999);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(s,(struct sockaddr*)&server,sizeof(server));

    printf("Connected to chat server\n");

    while(1)
    {
        FD_ZERO(&readfds);

        FD_SET(0,&readfds);
        FD_SET(s,&readfds);

        select(s+1,&readfds,NULL,NULL,NULL);

        if(FD_ISSET(0,&readfds))
        {
            fgets(msg,sizeof(msg),stdin);

            send(s,msg,strlen(msg),0);
        }

        if(FD_ISSET(s,&readfds))
        {
            n=recv(s,msg,sizeof(msg)-1,0);

            if(n<=0)
            {
                printf("Server disconnected\n");
                break;
            }

            msg[n]='\0';

            printf("%s",msg);
        }
    }

    close(s);

    return 0;
}