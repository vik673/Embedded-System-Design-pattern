# Makefile for State Table Design Pattern Implementation
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
TARGET = state_table_demo
OBJDIR = obj

# Source files
SOURCES = StateTableTypes.c \
          Mutex.c \
          StateTableTokenizer.c \
          StateTableClient.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Header dependencies
HEADERS = StateTableTypes.h \
          Mutex.h \
          StateTableTokenizer.h

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
	@echo "  debug       - Build with extra debugging info"
	@echo "  analyze     - Run static analysis (requires cppcheck)"
	@echo "  format      - Format code (requires clang-format)"

# Create a debug version
debug: CFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)

# Create a static analysis target (requires cppcheck)
analyze:
	@which cppcheck > /dev/null || (echo "cppcheck not found. Install with: apt-get install cppcheck"; exit 1)
	cppcheck --enable=all --std=c99 --suppress=missingIncludeSystem $(SOURCES)

# Format code (requires clang-format)
format:
	@which clang-format > /dev/null || (echo "clang-format not found"; exit 1)
	clang-format -i *.c *.h

# Generate documentation (requires doxygen)
docs:
	@which doxygen > /dev/null || (echo "doxygen not found. Install with: apt-get install doxygen"; exit 1)
	doxygen Doxyfile

.PHONY: all run interactive clean install help debug analyze format docs
