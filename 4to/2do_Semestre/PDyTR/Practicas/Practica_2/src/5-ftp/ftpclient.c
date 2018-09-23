/* RPC client for simple addition example */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <getopt.h>
#include "commands.h"

typedef void (*command_function)(CLIENT*, char*, char*);

typedef struct {
  char name[15];
  command_function cmd;
} command;


int main( int argc, char *argv[]) {
  CLIENT *clnt;
  int i, c;

  // Declare commands with functions
  command commands[] = {
    { "write", &ftp_write },
    { "read", &ftp_read },
    { "list", &ftp_write }
  };

  // Check parameters
  if (argc < 2) {
    fprintf(stderr,"Usage: %s command --name <name> --path <path> --host <host>\n",argv[0]);
    exit(0);
  }

  int command = -1;
  for (i = 0; i < 3; i++) {
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
    {"name", required_argument, 0, 'n'},
    {"path", required_argument, 0, 'p'},
    {"host", required_argument, 0, 'h'},
    {0,      0,                 0,  0 }
  };

  // Variables for ftp command
  char path[PATH_MAX];
  strcpy(path, "");
  char name[PATH_MAX];
  strcpy(name, "");
  char hostname[PATH_MAX];
  strcpy(hostname, "");

  // Parse arguments
  while ((c = getopt_long(argc, argv, "n:p:h:", long_options, &option_index)) != -1) {
    switch (c) {
      case 'n':
        strcpy(name, optarg);
        break;
      case 'p':
        strcpy(path, optarg);
        break;
      case 'h':
        strcpy(hostname, optarg);
        break;
      default:
        abort();
    }
  }

  // Config RPC
  /* Create a CLIENT data structure that reference the RPC
     procedure FTP_PROG, version FTP_VERSION running on the
     host specified by the 1st command line arg. */
  if(!strlen(hostname)) {
    strcpy(hostname, "localhost");
  }
  clnt = clnt_create(hostname, FTP_PROG, FTP_VERSION, "udp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  printf("Connecting to server with host %s\n", hostname);
  // Call command
  commands[command].cmd(clnt, path, name);
  return(0);
}
