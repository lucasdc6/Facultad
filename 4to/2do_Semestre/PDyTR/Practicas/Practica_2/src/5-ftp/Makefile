.c.o:
	gcc -c -Wall -DRPC_SVC_FG $<

all: client server


client: ftpclient.o ftp_clnt.o ftp_xdr.o utils.o commands.o
	gcc -o client ftpclient.o ftp_clnt.o ftp_xdr.o utils.o commands.o -lnsl -Wall


server: ftpservice.o ftp_svc.o ftp_xdr.o utils.o
	gcc -o server ftpservice.o ftp_svc.o ftp_xdr.o utils.o -lrpcsvc -lnsl -Wall

ftp.h: ftp.x
	rpcgen -N ftp.x

clean: 
	rm *.o ftp.h ftp_svc.* ftp_clnt.* ftp_xdr.* client server

ftpclient.c: ftp.h
ftpservice.c: ftp.h
utils.c: utils.h
commands.c: commands.h
