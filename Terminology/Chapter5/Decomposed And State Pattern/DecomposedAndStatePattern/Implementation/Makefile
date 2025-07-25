# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Source files
SOURCES = main.c \
          LightControllerClient.c \
          LightController.c \
          ErrorStateClass.c \
          ModeStateClass.c \
          AndStateList.c \
          StateActionSet.c \
          Light.c \
          Klaxon.c \
          Mutex.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Target executable
TARGET = decomposed_and_state_demo

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Print help
help:
	@echo "Available targets:"
	@echo "  all      - Build the demo executable"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and rebuild"
	@echo "  run      - Build and run the demo"
	@echo "  help     - Show this help message"

.PHONY: all clean rebuild run help
