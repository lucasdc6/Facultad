/* RPC client for simple addition example */

#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "ftp.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */
int write( CLIENT *clnt, char *data, char *name, int size) {
  #ifdef DEBUG
  printf("write - Args: \n\t- data: %s\n\t- name: %s\n\n", data, name);
  #endif
  ftp_file ftp_file_data;
  int *result;

  /* Gather everything into a single data structure to send to the server */
  strcpy(ftp_file_data.data, data);
  ftp_file_data.name = malloc(PATH_MAX);
  ftp_file_data.name = strcpy(ftp_file_data.name, name);
  ftp_file_data.size = size;
  ftp_file_data.checksum = hash(data);

  /* Call the client stub created by rpcgen */
  result = write_1(ftp_file_data,clnt);
  if (result == NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }
  return(*result);
}

int main( int argc, char *argv[]) {
  CLIENT *clnt;
  char* data;
  char name[PATH_MAX];
  int size;
  if (argc < 3) {
    fprintf(stderr,"Usage: %s hostname path name (optional)\n",argv[0]);
    exit(0);
  }

  /* Create a CLIENT data structure that reference the RPC
     procedure FTP_PROG, version FTP_VERSION running on the
     host specified by the 1st command line arg. */

  clnt = clnt_create(argv[1], FTP_PROG, FTP_VERSION, "udp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  FILE* file;
  file = fopen(argv[2], "r");
  data = malloc(DATA_SIZE);
  size = fread(data, sizeof(char), DATA_SIZE, file);

  fclose(file);

  if (argc < 4) {
    strcpy(name, argv[2]);
  } else {
    strcpy(name, argv[3]);
  }

  write(clnt,data,name,size);
  return(0);
}



