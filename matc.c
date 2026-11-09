#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

void main()
{
    int s;
    int a[10][10], n;
    char res[100];

    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9999);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("connect");
        return;
    }

    printf("enter n:");
    scanf("%d", &n);

    printf("enter elements:");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    send(s, &n, sizeof(n), 0);

    for(int i = 0; i < n; i++)
        send(s, a[i], n * sizeof(int), 0);   // one row at a time

    recv(s, res, sizeof(res), 0);

    printf("result %s \n", res);

    close(s);
}