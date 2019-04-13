CC := gcc
CFLAGS := -pthread
SRC_DIR := src
BIN_DIR := bin
SOURCES := punto1 punto1-sec punto2 punto2-sec punto3 punto3-sec punto4 punto4-sec

all: folders
	@echo "Compiling '$(SOURCES)'\n"
	@for src in $(SOURCES); do \
		echo "$(CC) -Wall $(CFLAGS) -o $(BIN_DIR)/$$src $(SRC_DIR)/$$src.c" ;\
		$(CC) -Wall $(CFLAGS) -o $(BIN_DIR)/$$src $(SRC_DIR)/$$src.c ;\
	done

folders:
	@-mkdir bin

clean:
	-rm -r bin
