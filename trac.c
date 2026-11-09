#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
{
    int s;
    char word[500],res[500];

    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    printf("Enter sentence: ");
    fgets(word,sizeof(word),stdin);

    sendto(s,word,sizeof(word),0,
    (struct sockaddr*)&server,sizeof(server));

    recvfrom(s,res,sizeof(res),0,NULL,NULL);

    printf("Translation: %s",res);

    close(s);

    return 0;
}
/* int len;                       // declare at the top with the other variables

len = sizeof(server);          // set BEFORE calling recvfrom

recvfrom(s, res, sizeof(res), 0,
         (struct sockaddr*)&server, &len);

printf("Translation: %s", res); */