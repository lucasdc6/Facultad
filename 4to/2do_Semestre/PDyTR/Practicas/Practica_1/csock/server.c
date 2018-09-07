/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

unsigned long hash(char *str)
{
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

double dwalltime()
{
  double sec;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  sec = tv.tv_sec + tv.tv_usec/1000000.0;
  return sec;
}

void error(char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno, clilen;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr, cli_addr;
  int n;
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
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0) 
    error("ERROR on binding");
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, 
      (struct sockaddr *) &cli_addr, 
      &clilen);
  if (newsockfd < 0)
    error("ERROR on accept");
  double time = dwalltime();
  bzero(buffer,BUFFER_SIZE);
  long int bufferi[1];
  int i=0;

  n = read(newsockfd,bufferi,4);
 printf("%d\n",bufferi[0] );
  while(bufferi[0] != i){
    i+= read(newsockfd,&buffer[i],BUFFER_SIZE-1);
    if (i != bufferi[0]){
      write(newsockfd,"M",2);
      write(newsockfd,&i,2);
    }
  }
   n = write(newsockfd,"I",2);
  if (n < 0) error("ERROR writing to socket");

  //printf("Here is the message! %s\nRead return value: %d\n %d\n",buffer,i,bufferi[0]);

  unsigned long buffer_checksum;
  n = read(newsockfd, &buffer_checksum,sizeof(buffer_checksum));
  printf("Checksum de client: %lu\nMi checsum %lu\n", buffer_checksum, hash(buffer));


  return 0; 
}
