/* Definition of the remote add and subtract procedure used by 
   simple RPC example 
   rpcgen will create a template for you that contains much of the code
   needed in this file is you give it the "-Ss" command line arg.
*/
#include <stdio.h>
#include "sleeper.h"

/* Here is the actual remote procedure */
/* The return value of this procedure must be a pointer to int! */
/* we declare the variable result as static so we can return a 
   pointer to it */

int *
sleep_time_1_svc(sleeping_time *argp, struct svc_req *rqstp)
{
	static int  result;

	sleep(argp->time);
	result = argp->time;
	
	return (&result);
}