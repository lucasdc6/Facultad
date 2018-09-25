/* RPC client for simple addition example */

#include <stdio.h>
#include "sleeper.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */

int sleep_time( CLIENT *clnt, int time) {
  sleeping_time stime;
  int *result;

  /* Gather everything into a single data structure to send to the server */
  stime.time = time;

  /* Call the client stub created by rpcgen */
  result = sleep_time_1(&stime,clnt);
  if (result==NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }
  return(*result);
}

int main( int argc, char *argv[]) {
  CLIENT *clnt;
  if (argc!=2) {
    fprintf(stderr,"Usage: %s hostname\n",argv[0]);
    exit(0);
  }

  /* Create a CLIENT data structure that reference the RPC
     procedure SIMP_PROG, version SIMP_VERSION running on the
     host specified by the 1st command line arg. */

  clnt = clnt_create(argv[1], SLEEPER_PROG, SLEEPER_VERSION, "tcp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  sleep_time(clnt,30);
 
  return(0);
}



