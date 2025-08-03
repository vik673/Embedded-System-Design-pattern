# Makefile for Interrupt Pattern Example

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = interrupt_pattern
SOURCES = main.c ButtonHandler.c LED.c Button.c RobotInterruptVectorTable.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = ButtonHandler.h LED.h Button.h RobotInterruptVectorTable.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	del /Q *.o $(TARGET).exe 2>nul || true

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG
debug: $(TARGET)

# Help target
help:
	@echo Available targets:
	@echo   all     - Build the program (default)
	@echo   clean   - Remove build artifacts
	@echo   run     - Build and run the program
	@echo   debug   - Build with debug information
	@echo   help    - Show this help message

.PHONY: all clean run debug help
