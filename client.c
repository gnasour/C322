//George Nassour
//Client.c code
//Lab 5 

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void error(char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno, n, i=0;
  int inputNum, numToAdd;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  if (argc < 3) {

    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serv_addr.sin_addr.s_addr,
	  server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
      error("ERROR connecting");
 
    printf("How many numbers do you want to add together? ");
        bzero(buffer, 256);
	// fgets(buffer, 255, stdin);
    // numToAdd = atoi(buffer);
    scanf("%d", &numToAdd);
    write(sockfd, &numToAdd, sizeof(int));
    for(i; i< numToAdd; i++){
      printf("Enter a number: ");
      scanf("%d", &inputNum);
      write(sockfd, &inputNum, sizeof(int));
    }
    close(sockfd);
    return 0;
}
