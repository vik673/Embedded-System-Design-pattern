# Makefile for Queuing Pattern Example

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = queuing_pattern_demo
SRCDIR = .

# Source files
SOURCES = main.c \
          GasData.c \
          GasDataQueue.c \
          OSSemaphore.c \
          O2Sensor.c \
          N2Sensor.c \
          HeSensor.c \
          SensorThread.c \
          GasDisplay.c \
          GasController.c \
          GasProcessingThread.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Header files for dependency tracking
HEADERS = QueuingExample.h \
          GasData.h \
          GasDataQueue.h \
          OSSemaphore.h \
          O2Sensor.h \
          N2Sensor.h \
          HeSensor.h \
          SensorThread.h \
          GasDisplay.h \
          GasController.h \
          GasProcessingThread.h

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
	@echo "Clean complete"

# Clean and rebuild
rebuild: clean all

# Install (copy to a system directory - optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with debug symbols
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the executable (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and build"
	@echo "  run      - Build and run the program"
	@echo "  debug    - Build with debug symbols"
	@echo "  install  - Install to system directory"
	@echo "  help     - Show this help message"

.PHONY: all clean rebuild install run debug help
