# Rutas
SRC_DIR = .
BIN_DIR = ../bin
OBJ_DIR = ../../obj
INCLUDE_DIR = ../../src

# Compilador y flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Archivos fuente
TEST_SRC = cpuinfo_test.c meminfo_test.c tui_test.c
TEST_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Ejecutables
TEST_BIN = $(BIN_DIR)/cpuinfo_test $(BIN_DIR)/meminfo_test $(BIN_DIR)/tui_test

all: $(TEST_BIN)

$(BIN_DIR)/cpuinfo_test: $(OBJ_DIR)/cpuinfo_test.o $(OBJ_DIR)/cpuinfo_manip.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/meminfo_test: $(OBJ_DIR)/meminfo_test.o $(OBJ_DIR)/meminfo_manip.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/tui_test: $(OBJ_DIR)/tui_test.o $(OBJ_DIR)/tui.o $(OBJ_DIR)/cpuinfo_manip.o $(OBJ_DIR)/meminfo_manip.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean
