# Makefile for Smart Data Pattern Implementation
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = smart_data_demo
OBJDIR = obj

# Source files
SOURCES = AlarmManager.c SmartInt.c SmartColor.c PatientDataClass.c demo.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Default target
all: $(OBJDIR) $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Install (copy to a system directory - modify as needed)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean run install
