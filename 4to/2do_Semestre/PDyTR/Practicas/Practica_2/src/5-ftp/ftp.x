#define VERSION_NUMBER 1

%#define DATA_SIZE 8192

struct ftp_file {
  string name<PATH_MAX>;
	opaque data[DATA_SIZE];
  int size;
	int checksum;
};

program FTP_PROG {
   version FTP_VERSION {
     ftp_file READ(string) = 1;
     int WRITE(ftp_file) = 2;
   } = VERSION_NUMBER;
} = 555555555;

#define FTP_PROG 555555555
