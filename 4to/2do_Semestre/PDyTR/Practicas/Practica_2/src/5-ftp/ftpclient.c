/* RPC client for simple addition example */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <getopt.h>
#include "commands.h"

typedef int (*command_function)(CLIENT*, char*, char*);

typedef struct command {
  char name[15];
  char description[100];
  command_function callback;
} command_t;


int main( int argc, char *argv[]) {
  CLIENT *clnt;
  int i, c;

  // Declare commands with functions
  command_t commands[] = {
    {
      .name="write",
      .description="Add a file from --src to --dest",
      .callback=&ftp_write
    },
    {
      .name="add",
      .description="Add a file from --src to --dest",
      .callback=&ftp_write
    },
    {
      .name="read",
      .description="Store a file from --src to --dest",
      .callback=&ftp_read
    },
    {
      .name="get",
      .description="Store a file from --src to --dest",
      .callback=&ftp_read
    },
    {
      .name="list",
      .description="List files from --src",
      .callback=&ftp_list
    },
    {
      .name="ls",
      .description="List files from --src",
      .callback=&ftp_list
    },
  };

  // Check parameters
  if (argc < 2) {
    fprintf(stderr,"Usage: %s\n",argv[0]);
    for (i = 0; i < sizeof(commands)/sizeof(command_t); i++) {
      fprintf(stderr, "\t- %s: %s\n", commands[i].name, commands[i].description);
    }  
    exit(0);
  }

  int command = -1;
  for (i = 0; i < sizeof(commands)/sizeof(command_t); i++) {
    if (!strcmp(commands[i].name, argv[1])) {
      command = i;
      break;
    }
  }

  if (command == -1) {
    fprintf(stderr, "Invalid command");
    exit(1);
  }

  // Config getopt
  int option_index = 0;
  static struct option long_options[] = {
    {"src", required_argument, 0, 's'},
    {"dest", required_argument, 0, 'd'},
    {"host", required_argument, 0, 'h'},
    {0,      0,                 0,  0 }
  };

  // Variables for ftp command
  char src[PATH_MAX];
  strcpy(src, "");
  char dest[PATH_MAX];
  strcpy(dest, "");
  char hostname[PATH_MAX];
  strcpy(hostname, "");

  // Parse arguments
  while ((c = getopt_long(argc, argv, "s:d:h:", long_options, &option_index)) != -1) {
    switch (c) {
      case 's':
        strcpy(src, optarg);
        break;
      case 'd':
        strcpy(dest, optarg);
        break;
      case 'h':
        strcpy(hostname, optarg);
        break;
      default:
        abort();
    }
  }

  if (!strlen(src)) {
    fprintf(stderr, "Specify a --src path\n");
    exit(1);
  }

  if (!strlen(dest)) {
    fprintf(stderr, "--dest setted to tmp1\n");
    strcpy(dest, "tmp1");
  }

  // Config RPC
  /* Create a CLIENT data structure that reference the RPC
     procedure FTP_PROG, version FTP_VERSION running on the
     host specified by the 1st command line arg. */
  if(!strlen(hostname)) {
    strcpy(hostname, "localhost");
  }
  clnt = clnt_create(hostname, FTP_PROG, FTP_VERSION, "tcp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  printf("Connecting to server with host %s\n", hostname);
  // Call command
  commands[command].callback(clnt, src, dest);
  return 0;
}
