#define VERSION_NUMBER 1

%#define DATA_SIZE 4294967295

struct ftp_file {
  string name<PATH_MAX>;
	opaque data<>;
	uint64_t checksum;
};

program FTP_PROG {
   version FTP_VERSION {
     ftp_file READ(string) = 1;
     int WRITE(ftp_file) = 2;
     string LIST(string) = 3;
   } = VERSION_NUMBER;
} = 555555555;

#define FTP_PROG 555555555
