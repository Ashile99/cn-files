#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>


void main()
{
    int s,c;
    int a[10][10],n;
    int u=1,l=1,d=1;
    char res[100];

    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9999);
    server.sin_addr.s_addr= INADDR_ANY;

    bind(s,(struct sockaddr*)&server,sizeof(server));

    listen(s,5);

    c=accept(s,NULL,NULL);
    
    recv(c,&n,sizeof(n),0);
    
    for(int i = 0; i < n; i++)
         recv(c, a[i], n * sizeof(int), MSG_WAITALL);   // one row at a time

   
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i>j && a[i][j]!=0)
               u=0;
            if(i<j && a[i][j]!=0)
               l=0;
            if(i!=j && a[i][j]!=0)
               d=0;
        }
    }

    if(d==1)
        sprintf(res,"diogonal");

     else if(u==1)
        sprintf(res,"Upper mtx");

    else if (l==1)
        sprintf(res,"lower mtx");

    else 
        sprintf(res,"nor");

    send(c,res,sizeof(res),0);

    printf("Classification %s \n",res);

    close(c);
    close(s); 
}