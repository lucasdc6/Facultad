all: clean
	mkdir punto1/classes punto2/classes punto3/classes
	javac -classpath lib/jade.jar -d punto1/classes punto1/AgentePunto1.java
	javac -classpath lib/jade.jar -d punto2/classes punto2/AgentePunto2.java
	javac -classpath lib/jade.jar -d punto3/classes punto3/AgentePunto3.java

start-gui:
	java -cp lib/jade.jar:classes jade.Boot -gui

run-punto1:
	cd punto1 && java -cp ../lib/jade.jar:classes jade.Boot -gui -container -host localhost -agents mol:AgentePunto1

run-punto2:
	cd punto2 && java -cp ../lib/jade.jar:classes jade.Boot -gui -container -host localhost -agents mol:AgentePunto2

run-punto3:
	cd punto3 && java -cp ../lib/jade.jar:classes jade.Boot -gui -container -host localhost -agents mol:AgentePunto3

clean:
	- rm -r APDescription.txt MTPs-Main-Container.txt punto1/classes punto2/classes punto3/classes
