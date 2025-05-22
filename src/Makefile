# Ruta a la carpeta obj
OBJ_DIR = ../obj

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -I.

# Archivos fuente en src
SRC_FILES = cpuinfo_manip.c meminfo_manip.c tui.c resource_mon.c
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Regla por defecto: compilar los .c a .o
all: $(OBJ_FILES)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o

.PHONY: all clean
