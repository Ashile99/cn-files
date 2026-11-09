#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
{
    int s,len;

    char word[500],res[500];

    char key[5][10]={"tbh","omw","tbf","omg","btw"};

    char value[5][30]={"to be honest","on my way",
                       "to be fair","oh my god","by the way"};

    struct sockaddr_in server,client;

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(s,(struct sockaddr*)&server,sizeof(server));

    len=sizeof(client);

    recvfrom(s,word,sizeof(word),0,
    (struct sockaddr*)&client,&len);

    strcpy(res,"");

    char *p=strtok(word," \n");

    while(p!=NULL)
    {
        int found=0;

        for(int i=0;i<5;i++)
        {
            if(strcmp(p,key[i])==0)
            {
                strcat(res,value[i]);
                found=1;
                break;
            }
        }

        if(found==0)
            strcat(res,p);

        strcat(res," ");

        p=strtok(NULL," \n");
    }

    sendto(s,res,sizeof(res),0,
    (struct sockaddr*)&client,len);

    printf("Translated: %s",res);

    close(s);

    return 0;
}