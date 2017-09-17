CC:=gcc
OPTIONS:=-O2
LIB_PATH:=-pthread
SRC_DIR:=src
DST_DIR:=bin
default:
	$(CC) $(OPTIONS) $(LIB_PATH) \
		$(SRC_DIR)/p1_a.c -o $(DST_DIR)/test_a
	$(CC) $(OPTIONS) $(LIB_PATH) \
		$(SRC_DIR)/p1_b.c -o $(DST_DIR)/test_b
clean:
	cd $(DST_DIR); rm test
