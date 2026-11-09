#include<stdio.h>
#include<string.h>
#include<time.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

void main()
{
    int s;
    char word[20],res[200];
    time_t t;

    struct sockaddr_in server;

    int len=sizeof(server);

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    printf("enter time:");
    scanf("%s",word);

    sendto(s,word,sizeof(word),0,(struct sockaddr*)&server,len);

    recvfrom(s,res,sizeof(res),0,(struct sockaddr*)&server,&len);

    printf("Requested %s is %s",word,res);

    close(s);
   
}