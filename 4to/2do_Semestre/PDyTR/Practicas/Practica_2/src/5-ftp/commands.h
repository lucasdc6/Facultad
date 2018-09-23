#ifndef COMMANDS_H
#define COMMANDS_H
#include "ftp.h"  /* Created for us by rpcgen - has everything we need ! */

int ftp_write(CLIENT *, char *, char *);
int ftp_read(CLIENT *, char *, char *);
int ftp_list(CLIENT *, char *, char *);

#endif