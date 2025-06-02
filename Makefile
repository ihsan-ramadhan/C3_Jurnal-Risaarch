CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ASSETS_DIR = assets

# Source files
SOURCES = $(SRC_DIR)/dll.c $(SRC_DIR)/jurnal.c $(SRC_DIR)/main.c $(SRC_DIR)/fitur1.c
OBJECTS = $(OBJ_DIR)/dll.o $(OBJ_DIR)/jurnal.o $(OBJ_DIR)/main.o $(OBJ_DIR)/fitur1.o

# Executable name
TARGET = $(BIN_DIR)/journal_app

# Default target
all: $(TARGET)

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean