CC := gcc
CFLAGS := -pthread
SRC_DIR := src
TEMPLATE_DIR := templates
BIN_DIR := bin
SOURCES := `ls $(SRC_DIR) | cut -d. -f1 | xargs`
TEMPLATES := `ls $(TEMPLATE_DIR) | cut -d. -f1 | xargs`

all: folders
	@echo "Compiling '$(SOURCES)'\n"
	@for src in $(SOURCES); do \
		echo "$(CC) -Wall $(CFLAGS) -o $(BIN_DIR)/$$src $(SRC_DIR)/$$src.c" ;\
		$(CC) -Wall $(CFLAGS) -o $(BIN_DIR)/$$src $(SRC_DIR)/$$src.c ;\
	done

templates: folders
	@echo "Compiling templates files '$(TEMPLATES)'"
	@for src in $(TEMPLATES); do \
		echo "$(CC) -Wall $(CFLAGS) -o $(BIN_DIR)/$$src $(TEMPLATE_DIR)/$$src.c" ;\
		$(CC) -Wall $(CFLAGS) -o $(BIN_DIR)/$$src $(TEMPLATE_DIR)/$$src.c ;\
	done

folders:
	@-mkdir bin

clean:
	-rm -r bin
