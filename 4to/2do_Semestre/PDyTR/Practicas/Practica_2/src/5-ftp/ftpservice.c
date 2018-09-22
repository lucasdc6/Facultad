/* Definition of the remote add and subtract procedure used by 
   simple RPC example 
   rpcgen will create a template for you that contains much of the code
   needed in this file is you give it the "-Ss" command line arg.
*/
#include <stdio.h>
#include "hash.h"
#include "ftp.h"

/* Here is the actual remote procedure */
/* The return value of this procedure must be a pointer to int! */
/* we declare the variable result as static so we can return a 
   pointer to it */

int *
write_1_svc(ftp_file argp, struct svc_req *rqstp)
{
    #ifdef DEBUG
    printf("write_1_svc - Args:\n\targp:\n\t\t- name: %s\n\t\t- data: %s\n\t\t- size: %d \n\t\t- checksum: %d\n\n",
            argp.name, argp.data, argp.size, argp.checksum);
    #endif

    // Declare variables
	FILE *file;
    static size_t result;
    char path[PATH_MAX];

    // Set path
    snprintf(path, PATH_MAX, "%s/%s", "store", argp.name);

    #ifdef DEBUG
    printf("Path: %s\n\n", path);
    #endif

    // Open file and check errors
    file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error creating file\n");
    }
    
    // Check checksum
    int checksum = hash(argp.data);
    if (checksum != argp.checksum) {
        fprintf(stderr, "Error in checksum!!\nOriginal: %d\nOwn: %d\n", argp.checksum, checksum);
    }

    // Write file
    result = fwrite(argp.data, sizeof(char), argp.size, file);

    fclose(file);
	printf("Storing %s...\n", argp.name);

	return((int*)&result);
}

int *
read_1_svc(ftp_file argp, struct svc_req *rqstp)
{
    static int result = 1;

    return(&result);
}
