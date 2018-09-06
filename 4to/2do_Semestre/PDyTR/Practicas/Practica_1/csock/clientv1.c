#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

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
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[BUFFER_SIZE];
  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  double time = dwalltime();
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
  if (connect(sockfd,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR connecting");
  bzero(buffer,BUFFER_SIZE);
  int i = 0;
  buffer[i++] = 'r';
  for (i; i < BUFFER_SIZE-4; i++) {
    buffer[i] = 'a';
  }
  buffer[i++] = 'w';
  buffer[i++] = 'r';
  buffer[i] = '!';
  n = write(sockfd,buffer,BUFFER_SIZE);
  if (n < 0) 
    error("ERROR writing to socket");
  bzero(buffer,BUFFER_SIZE);
  n = read(sockfd,buffer,BUFFER_SIZE-1);
  if (n < 0) 
    error("ERROR reading from socket");
  //printf("%s\n",buffer);
  printf("%g\n", dwalltime()-time);
  return 0;
}
