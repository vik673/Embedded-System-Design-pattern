# Makefile for Guarded Call Pattern Implementation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = guarded_call_demo
SRCDIR = .
OBJDIR = obj

# Source files
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build target
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Install (copy to a bin directory if needed)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean run install
