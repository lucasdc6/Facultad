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

unsigned long hash(unsigned char *str)
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
  int sockfd, portno, silent, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[BUFFER_SIZE];
  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }

  portno = atoi(argv[2]);

  if (argc == 4) {
    silent = atoi(argv[3]);
  } else {
    silent = 0;
  }
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

  long int bufferi[1];
  bufferi[0]=BUFFER_SIZE-1;
  char response[2];
  response[0]='M';
  i=0;

  unsigned long buffer_hash = hash(buffer);

  n = write(sockfd,bufferi,4);

  while(response[0] == 'M'){

    n = write(sockfd,&buffer[i],BUFFER_SIZE-1);

    n = read(sockfd,response,2 );

    if (response[0] == 'M'){
      n = read(sockfd,bufferi,BUFFER_SIZE-1);
      i=bufferi[0];
      if (n < 0) 
        error("ERROR reading from socket");
    }
  }
  if (!silent) {
    printf("%s\n",response);

    printf("Check: %lu\n", buffer_hash);
  }

  n = write(sockfd, &buffer_hash,sizeof(buffer_hash));

  printf("%g\n", dwalltime()-time);
  return 0;
}
