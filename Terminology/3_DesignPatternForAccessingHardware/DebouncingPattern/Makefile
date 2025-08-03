# Makefile for Debouncing Pattern Demo
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = debouncing_demo
SOURCES = main.c Button.c ButtonDriver.c MicrowaveEmitter.c Timer.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = Button.h ButtonDriver.h MicrowaveEmitter.h Timer.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Rebuild everything
rebuild: clean all

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the debouncing demo (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and build"
	@echo "  run      - Build and run the demo"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build optimized release version"
	@echo "  help     - Show this help message"

.PHONY: all clean rebuild run debug release help
