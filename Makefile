# Rutas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -I$(SRC_DIR)

src:
	$(MAKE) -C src


# Archivos fuente principales
SRC_FILES = cpuinfo_manip.c meminfo_manip.c tui.c resource_mon.c
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Archivos fuente de test
TEST_SRC = cpuinfo_test.c meminfo_test.c tui_test.c
TEST_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Ejecutables
RESOURCE_MON = $(BIN_DIR)/resource_mon
TESTS = $(BIN_DIR)/cpuinfo_test $(BIN_DIR)/meminfo_test $(BIN_DIR)/tui_test

# Default
all: resource_mon tests

# Ejecutable principal
resource_mon: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(RESOURCE_MON) $^

# Tests
tests: $(TESTS)

$(BIN_DIR)/cpuinfo_test: $(OBJ_DIR)/cpuinfo_test.o $(OBJ_DIR)/cpuinfo_manip.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/meminfo_test: $(OBJ_DIR)/meminfo_test.o $(OBJ_DIR)/meminfo_manip.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/tui_test: $(OBJ_DIR)/tui_test.o $(OBJ_DIR)/tui.o $(OBJ_DIR)/cpuinfo_manip.o $(OBJ_DIR)/meminfo_manip.o
	$(CC) $(CFLAGS) -o $@ $^

# Regla general para objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean tests resource_mon
