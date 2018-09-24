#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utils.h"
#include "ftp.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */
int ftp_write(CLIENT *clnt, char *path, char *name) {
  double time = dwalltime();
  #ifdef DEBUG
  printf("write - Args: \n\t- path: %s\n\t- name: %s\n\n", path, name);
  #endif
  FILE* file;

  file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
    exit(1);
  }

  ftp_file ftp_file_data;
  int *result;

  /* Gather everything into a single data structure to send to the server */
  ftp_file_data.data.data_val = malloc(DATA_SIZE);
  ftp_file_data.data.data_len = fread(ftp_file_data.data.data_val, sizeof(char), DATA_SIZE, file);
  ftp_file_data.name = malloc(PATH_MAX);
  ftp_file_data.name = strcpy(ftp_file_data.name, name);
  ftp_file_data.checksum = hash(ftp_file_data.data.data_val);

  fclose(file);

  #ifdef DEBUG
  printf("name: %s\ndata: %s\nsize: %d\nchecksum: %" PRIu64 "\n",
        ftp_file_data.name,
        ftp_file_data.data.data_val,
        ftp_file_data.data.data_len,
        ftp_file_data.checksum);
  #endif

  /* Call the client stub created by rpcgen */
  result = write_1(ftp_file_data,clnt);
  if (result == NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  } else if (*result == -1) {
    fprintf(stderr, "Error creating file\n");
  }
  fprintf(stderr, "Took %g ms\n\n", dwalltime()-time);
  return(*result);
}

/* Wrapper function takes care of calling the RPC procedure */
int ftp_read(CLIENT *clnt, char *path, char *name) {
  double time = dwalltime();
  #ifdef DEBUG
  //printf("write - Args: \n\t- data: %s\n\t- name: %s\n\n", data, name);
  #endif
  FILE* file;
  ftp_file *ftp_file_data;

  ftp_file_data = read_1(path,clnt);
  if (ftp_file_data == NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }

  printf("Storing file %s...\n", name);
  file = fopen(name, "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
    exit(1);
  }
  fwrite(ftp_file_data->data.data_val, sizeof(char), ftp_file_data->data.data_len, file);
  fclose(file);

  fprintf(stderr, "Took %g ms\n\n", dwalltime()-time);
  return 1;
}

/* Wrapper function takes care of calling the RPC procedure */
int ftp_list(CLIENT *clnt, char *path, char *name) {
  double time = dwalltime();
  #ifdef DEBUG
  //printf("write - Args: \n\t- data: %s\n\t- name: %s\n\n", data, name);
  #endif
  char **paths;
  paths = list_1(path, clnt);
  printf("%s\n", paths[0]);
  fprintf(stderr, "Took %g ms\n\n", dwalltime()-time);
  return 0;
}