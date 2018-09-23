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
  command commands[] = {
    { "write", &ftp_write },
    { "read", &ftp_read },
    { "list", &ftp_write }
  };

  if (argc < 2) {
    fprintf(stderr,"Usage: %s command hostname path name (optional)\n",argv[0]);
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

  // Config RPC
  /* Create a CLIENT data structure that reference the RPC
     procedure FTP_PROG, version FTP_VERSION running on the
     host specified by the 1st command line arg. */
  clnt = clnt_create("localhost", FTP_PROG, FTP_VERSION, "udp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  // Config getopt
  int option_index = 0;
  static struct option long_options[] = {
    {"name", required_argument, 0, 'n'},
    {"path", required_argument, 0, 'p'},
    {0,      0,                 0,  0 }
  };

  // Variables for ftp command
  char path[PATH_MAX];
  strcpy(path, "");
  char name[PATH_MAX];
  strcpy(name, "");

  // Parse arguments
  while ((c = getopt_long(argc, argv, "n:p:", long_options, &option_index)) != -1) {
    switch (c) {
      case 'n':
        strcpy(name, optarg);
        break;
      case 'p':
        /*
        if(strcmp(argv[1], "write")) {
          fprintf(stderr, "The flag -p/--path is only available for write command\n");
          strcpy(path, name);
          continue;
        }
        */
        strcpy(path, optarg);
        break;
      default:
        abort();
    }
  }

  // Call command
  commands[command].cmd(clnt, path, name);
  return(0);
}
