#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

#define PORT 5555

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    
    char sendBuff[10000];
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    listen(listenfd, 5);
    printf("\nServer listening for connections!\n");
    
    time_t t_seconds;
    
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        printf("\nAccepted a connection\n");
	memset(sendBuff, '\0', sizeof(sendBuff));
	char buffer[1000];
	memset(buffer,'\0',sizeof(buffer));
	int bytes = recv(connfd, buffer, 1000, 0);
	buffer[bytes] = '\0';
	    printf("%s\nanswer: ", buffer);
	    
	    scanf("%s",buffer);
	    char c;
	    c = getchar();
	    char temp[100];
	    memset(temp,'\0',sizeof(temp));
	    while(c != '\n'){
	      scanf("%s",temp);
	      strcat(buffer," ");
	      strcat(buffer, temp);
	      c = getchar();
	    }
	    //scanf("%s",sendBuff);
	    printf("message sent\n");
	    //printf("buffer scanned length  %d",(int)strlen(sendBuff));
	    
      int i=0;
      snprintf(sendBuff, sizeof(buffer), "%s\n", buffer);
      write(connfd, sendBuff, strlen(sendBuff));
        close(connfd);
	
     }
}
