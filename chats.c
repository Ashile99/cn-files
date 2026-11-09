#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/select.h>

int main()
{
    int s,c,maxfd,n;
    int client[FD_SETSIZE],id[FD_SETSIZE];
    int count=0;

    char msg[500];

    fd_set readfds;

    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9999);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(s,(struct sockaddr*)&server,sizeof(server));

    listen(s,5);

    printf("Chat server started...\n");

    for(int i=0;i<FD_SETSIZE;i++)
        client[i]=0;

    while(1)
    {
        FD_ZERO(&readfds);

        FD_SET(s,&readfds);

        maxfd=s;

        for(int i=0;i<FD_SETSIZE;i++)
        {
            if(client[i]>0)
            {
                FD_SET(client[i],&readfds);

                if(client[i]>maxfd)
                    maxfd=client[i];
            }
        }

        select(maxfd+1,&readfds,NULL,NULL,NULL);

        if(FD_ISSET(s,&readfds))
        {
            c=accept(s,NULL,NULL);

            for(int i=0;i<FD_SETSIZE;i++)
            {
                if(client[i]==0)
                {
                    client[i]=c;
                    id[i]=++count;

                    printf("Client %d connected\n",id[i]);

                    break;
                }
            }
        }

        for(int i=0;i<FD_SETSIZE;i++)
        {
            if(client[i]>0 && FD_ISSET(client[i],&readfds))
            {
                n=recv(client[i],msg,sizeof(msg)-1,0);

                if(n<=0)
                {
                    printf("Client %d disconnected\n",id[i]);

                    close(client[i]);
                    client[i]=0;
                }

                else
                {
                    msg[n]='\0';

                    printf("Client %d: %s",id[i],msg);

                    for(int j=0;j<FD_SETSIZE;j++)
                    {
                        if(client[j]>0 && j!=i)
                        {
                            send(client[j],msg,n,0);
                        }
                    }
                }
            }
        }
    }

    close(s);

    return 0;
}