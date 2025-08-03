# Makefile for Multiple Receptor Pattern Implementation
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
TARGET = tokenizer_demo
OBJDIR = obj

# Source files
SOURCES = TokenizerTypes.c \
          Mutex.c \
          TokenizerMultiReceptor.c \
          TokenizerClient.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Header dependencies
HEADERS = TokenizerTypes.h \
          Mutex.h \
          TokenizerMultiReceptor.h

# Default target
all: $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build the executable
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Compile source files
$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Run in interactive mode
interactive: $(TARGET)
	./$(TARGET) -i

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Clean complete"

# Install (copy to system location - optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Show help
help:
	@echo "Available targets:"
	@echo "  all         - Build the project (default)"
	@echo "  run         - Build and run the demo"
	@echo "  interactive - Build and run in interactive mode"
	@echo "  clean       - Remove build artifacts"
	@echo "  install     - Install to system location"
	@echo "  help        - Show this help message"

# Create a debug version
debug: CFLAGS += -DDEBUG -g3
debug: $(TARGET)

# Create a static analysis target (requires cppcheck)
analyze:
	@which cppcheck > /dev/null || (echo "cppcheck not found. Install with: apt-get install cppcheck"; exit 1)
	cppcheck --enable=all --std=c99 $(SOURCES)

# Format code (requires clang-format)
format:
	@which clang-format > /dev/null || (echo "clang-format not found"; exit 1)
	clang-format -i *.c *.h

.PHONY: all run interactive clean install help debug analyze format
