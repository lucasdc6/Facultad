/* Definition of the remote add and subtract procedure used by 
   simple RPC example 
   rpcgen will create a template for you that contains much of the code
   needed in this file is you give it the "-Ss" command line arg.
*/
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
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
        exit(1);
    }
    
    // Check checksum
    uint64_t checksum = hash(argp.data.data_val);
    if (checksum != argp.checksum) {
        fprintf(stderr, "Error in checksum!!\nOriginal: %"PRIu64"\nOwn: %"PRIu64"\n", argp.checksum, checksum);
    }

    // Write file
    result = fwrite(argp.data.data_val, sizeof(char), argp.data.data_len, file);

    fclose(file);
	printf("Storing %s...\n", argp.name);

	return((int*)&result);
}

ftp_file *
read_1_svc(char *path, struct svc_req *rqstp)
{
	printf("Reading %s...\n", path);
    FILE *file;
    ftp_file *file_struct;
    file_struct = malloc(sizeof(char*) + sizeof(u_int) + sizeof(char*) + sizeof(int));
    file_struct->data.data_val = malloc(DATA_SIZE);

    file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opeing file %s\n", path);
        file_struct->data.data_len = -1;
        return file_struct;
    }
    file_struct->data.data_len = fread(file_struct->data.data_val, sizeof(char), DATA_SIZE, file);
    file_struct->name = malloc(PATH_MAX);
    file_struct->name = strcpy(file_struct->name, path);

    return file_struct;
}

char **
list_1_svc(char *path, struct svc_req *rqstp)
{
	printf("Listing files '%s'\n", path);
    DIR *dir;
    char **paths;
    paths = (char**)malloc(sizeof(char*));
    paths[0] = (char*)malloc(PATH_MAX);
    struct dirent *dir_str;

    dir = opendir(path);
    if(dir) {
        while((dir_str = readdir(dir)) != NULL) {
            if (strcmp(dir_str->d_name, ".") && strcmp(dir_str->d_name, "..")) {
                strcat(paths[0], dir_str->d_name);
                strcat(*paths, "\t");

                #ifdef DEBUG
                printf("%d - %s\n", i-1, paths[i-1]);
                #endif
            }
        }
        closedir(dir);
    }
    return paths;
}
