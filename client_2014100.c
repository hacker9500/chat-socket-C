#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555

int main(int argc, char *argv[])
{
  char name[100];
  printf("enter your name: ");
  scanf("%s",name);
  printf("\ntype exit to exit\n\n");
  
  while(1){
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    if(argc != 2)
    {
        printf("\n Usage: %s <Server IP address>\n",argv[0]);
        return -1;
    }

    char s[1000];
    memset(s,'\0',sizeof(s));
    printf("ques: ");
    //fgets(s,1000,stdin);
    char temp[100];
    char c;
    memset(temp,'\0',sizeof(temp));
    scanf("%s",s);
    c = getchar();
    while(c != '\n'){
      scanf("%s",temp);
      strcat(s," ");
      strcat(s,temp);
      c = getchar();
    }
    char sendBuff[1000];
    memset(sendBuff,'\0',sizeof(sendBuff));
    
    if(!strcmp(s,"exit")){
      sprintf(sendBuff,"%s has left",name);
      send(sock, sendBuff, strlen(sendBuff), 0);
      break;
    } else {
      sprintf(sendBuff,"%s: %s",name,s);
    }
    
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) //convert IPv4 and IPv6 addresses from text to binary form
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\nConnection Failed \n");
       return -1;
    }
    
    int readbytes = 0;
    char recvBuff[500];
    memset(recvBuff, '\0',sizeof(recvBuff));
    send(sock, sendBuff, strlen(sendBuff), 0);
    //printf("Server Time: ");
    while ( (readbytes=read(sock, recvBuff, sizeof(recvBuff))) > 0)
    {
        recvBuff[readbytes] = 0;
	printf("ans: %s\n",recvBuff);
    }
    
    if(readbytes < 0)
    {
        printf("\n Read error \n");
    }
}
    return 0;
}
