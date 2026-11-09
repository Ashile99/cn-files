#include<stdio.h>
#include<string.h>
#include<time.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void main()
{
    int s;
    char word[20],res[100];
    time_t t;

    struct sockaddr_in server,client;
    int len=sizeof(client);

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(s,(struct sockaddr*)&server,sizeof(server));

    while(1)
    {
        len=sizeof(client);

        recvfrom(s,word,sizeof(word),0,(struct sockaddr*)&client,&len);

        if(fork()==0)
        {
            if(strcmp(word,"time")==0 || strcmp(word,"Time")==0)
            {
                time(&t);
                strcpy(res,ctime(&t));
            }
            else
            {
                strcpy(res,"Invalid request");
            }

            sendto(s,res,sizeof(res),0,(struct sockaddr*)&client,len);

            printf("Requested %s is %s",word,res);

            close(s);
            exit(0);
        }

        waitpid(-1,NULL,WNOHANG); //optnl
    }
}