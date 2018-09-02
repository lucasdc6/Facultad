BUILD_FOLDER=bin
BUFFER_SIZE=1000

all: folders
	gcc -o ${BUILD_FOLDER}/server-${BUFFER_SIZE} server.c -D BUFFER_SIZE=${BUFFER_SIZE}
	gcc -o ${BUILD_FOLDER}/client-${BUFFER_SIZE} client.c -D BUFFER_SIZE=${BUFFER_SIZE}

folders:
	- mkdir ${BUILD_FOLDER}

clear:
	- rm -r ${BUILD_FOLDER}
