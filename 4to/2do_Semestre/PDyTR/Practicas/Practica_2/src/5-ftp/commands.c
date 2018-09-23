#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ftp.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */
int ftp_write(CLIENT *clnt, char *path, char *name) {
  #ifdef DEBUG
  printf("write - Args: \n\t- data: %s\n\t- name: %s\n\n", data, name);
  #endif
  FILE* file;
  char* data;
  int size;

  file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
  }
  data = malloc(DATA_SIZE);
  size = fread(data, sizeof(char), DATA_SIZE, file);
  fclose(file);

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

/* Wrapper function takes care of calling the RPC procedure */
int ftp_read(CLIENT *clnt, char *path, char *name) {
  #ifdef DEBUG
  printf("write - Args: \n\t- data: %s\n\t- name: %s\n\n", data, name);
  #endif
  FILE* file;
  ftp_file *ftp_file_data;

  ftp_file_data = read_1(path,clnt);
  if (ftp_file_data == NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }

  file = fopen(name, "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
  }
  fwrite(ftp_file_data->data, sizeof(char), ftp_file_data->size, file);
  fclose(file);

  printf("posta?\n%s\n", ftp_file_data->data);

  return 1;
}