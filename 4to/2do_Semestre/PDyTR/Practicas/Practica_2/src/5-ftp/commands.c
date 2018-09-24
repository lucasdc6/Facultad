#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utils.h"
#include "ftp.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */
int ftp_write(CLIENT *clnt, char *src, char *dest) {
  double time = dwalltime();
  #ifdef DEBUG
  printf("write - Args: \n\t- src: %s\n\t- dest: %s\n\n", src, dest);
  #endif
  FILE* file;

  file = fopen(src, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", src);
    exit(1);
  }

  ftp_file ftp_file_data;
  int *result;

  /* Gather everything into a single data structure to send to the server */
  ftp_file_data.data.data_val = malloc(DATA_SIZE);
  ftp_file_data.data.data_len = fread(ftp_file_data.data.data_val, sizeof(char), DATA_SIZE, file);
  ftp_file_data.name = malloc(PATH_MAX);
  ftp_file_data.name = strcpy(ftp_file_data.name, dest);
  ftp_file_data.checksum = hash(ftp_file_data.data.data_val);

  fclose(file);

  #ifdef DEBUG
  printf("dest: %s\ndata: %s\nsize: %d\nchecksum: %" PRIu64 "\n",
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
int ftp_read(CLIENT *clnt, char *src, char *dest) {
  double time = dwalltime();
  #ifdef DEBUG
  //printf("write - Args: \n\t- data: %s\n\t- dest: %s\n\n", data, dest);
  #endif
  FILE* file;
  ftp_file *ftp_file_data;

  ftp_file_data = read_1(src,clnt);
  if (ftp_file_data == NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }

  printf("Storing file %s...\n", dest);
  file = fopen(dest, "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", src);
    exit(1);
  }
  fwrite(ftp_file_data->data.data_val, sizeof(char), ftp_file_data->data.data_len, file);
  fclose(file);

  fprintf(stderr, "Took %g ms\n\n", dwalltime()-time);
  return 1;
}

/* Wrapper function takes care of calling the RPC procedure */
int ftp_list(CLIENT *clnt, char *src, char *dest) {
  double time = dwalltime();
  #ifdef DEBUG
  //printf("write - Args: \n\t- data: %s\n\t- dest: %s\n\n", data, dest);
  #endif
  char **paths;
  paths = list_1(src, clnt);
  printf("%s\n", paths[0]);
  fprintf(stderr, "Took %g ms\n\n", dwalltime()-time);
  return 0;
}