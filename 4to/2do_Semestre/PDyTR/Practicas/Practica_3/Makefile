all: compile start

start:
	rmiregistry &
	java StartRemoteObject

stop:
	@echo "Stop server\n"
	- killall rmiregistry

compile:
	javac *.java

clean:
	- rm *.class
