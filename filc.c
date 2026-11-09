
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
{
    int s,len,status;
    char filename[100],buffer[1024];
    FILE *fp;

    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9999);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(s,(struct sockaddr*)&server,sizeof(server));

    printf("Enter filename: ");
    scanf("%99s",filename);

    send(s,filename,sizeof(filename),0);

    recv(s,&status,sizeof(status),MSG_WAITALL);

    if(status==1)
    {
        fp=fopen("received.txt","wb");

        printf("\nFile contents:\n");

        while((len=recv(s,buffer,sizeof(buffer),0))>0)
        {
            fwrite(buffer,1,len,fp);

            printf("%.*s",len,buffer);
        }

        fclose(fp);

        printf("\n\nFile received successfully!\n");
    }
    else
    {
        printf("File not found!\n");
    }

    close(s);

    return 0;
}
