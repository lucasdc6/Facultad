.c.o:
	gcc -c -Wall -DRPC_SVC_FG $<

all: client server

client: sleeperclient.o sleeper_clnt.o sleeper_xdr.o
	gcc -o client sleeperclient.o sleeper_clnt.o sleeper_xdr.o -lnsl


server: sleeperservice.o sleeper_svc.o sleeper_xdr.o
	gcc -o server sleeperservice.o sleeper_svc.o sleeper_xdr.o -lrpcsvc -lnsl

sleeper.h: sleeper.x
	rpcgen -C sleeper.x

clean: 
	rm *.o sleeper.h simp_svc.* sleeper_clnt.* sleeper_xdr.*

sleeperclient.c: sleeper.h
sleeperservice.c: sleeper.h
