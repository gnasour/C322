/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
   gcc server2.c -lsocket
*/

//George Nassour
//Server.c code
//Lab5

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>

void dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
  
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;
     char buffer[256];
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);

     }
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     portno = atoi(argv[1]);
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
    
     while (1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
	 wait();
     } /* end of while */
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
  int numToAdd,i=0,numbersAdded=0;
  read(sock, &numToAdd, sizeof(int));
  //bzero(buffer, 256);
  int inputNum[numToAdd];
  for(i; i<numToAdd;i++){
    read(sock, &inputNum[i], sizeof(int));
    printf("Recieved number %d: %d\n", i+1,inputNum[i]);

  }
  i=0;
  for(i;i<numToAdd;i++){
    numbersAdded += inputNum[i];
  }
  printf("Here are the numbers added together: %d\n", numbersAdded);
  close(sock);
   
}
