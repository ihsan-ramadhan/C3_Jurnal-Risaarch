CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ASSETS_DIR = assets

# Source files
SOURCES = $(SRC_DIR)/dll.c $(SRC_DIR)/jurnal.c $(SRC_DIR)/main.c $(SRC_DIR)/fitur1.c $(SRC_DIR)/fitur2.c $(SRC_DIR)/fitur3.c $(SRC_DIR)/fitur4.c $(SRC_DIR)/fitur5.c
OBJECTS = $(OBJ_DIR)/dll.o $(OBJ_DIR)/jurnal.o $(OBJ_DIR)/main.o $(OBJ_DIR)/fitur1.o $(OBJ_DIR)/fitur2.o $(OBJ_DIR)/fitur3.o $(OBJ_DIR)/fitur4.o $(OBJ_DIR)/fitur5.o

# Executable name
TARGET = $(BIN_DIR)/journal_app

# Default target - will build and then run
all: run # Mengubah default target menjadi 'run'

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target untuk menjalankan program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET) # Menjalankan program setelah berhasil dibuat

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean run # Tambahkan 'run' ke phony targets