# Makefile for Single Receptor Pattern Implementation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = single_receptor_demo
OBJDIR = obj

# Source files
SOURCES = main.c \
          Mutex.c \
          TSREventQueue.c \
          TSRSyncSingleReceptor.c \
          TSRAsyncSingleReceptor.c \
          OSSignal.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Header files
HEADERS = Mutex.h \
          TokenizerAsyncSinglePkg.h \
          TokenizerSyncSinglePkg.h \
          TSREventQueue.h \
          TSRSyncSingleReceptor.h \
          TSRAsyncSingleReceptor.h

# Default target
all: $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build target
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the demo program"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the demo"
	@echo "  help    - Show this help message"

.PHONY: all clean run help
