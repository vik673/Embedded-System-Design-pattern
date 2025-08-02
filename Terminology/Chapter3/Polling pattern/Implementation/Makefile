# Makefile for Polling Pattern Demo
# Embedded System Design Pattern Example

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = polling_pattern_demo
SRCDIR = .
OBJDIR = obj

# Source files
SOURCES = main.c \
          BCPeriodicPoller.c \
          BCTimer.c \
          BreathingCircuitSensor.c \
          MedicalDisplay.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Header files
HEADERS = BCPeriodicPoller.h \
          BCTimer.h \
          BreathingCircuitSensor.h \
          MedicalDisplay.h

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build target executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
	@echo "Clean complete"

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# Install (copy to a common location)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  run      - Build and run the demo"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build optimized release version"
	@echo "  install  - Install the executable"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all clean run debug release install uninstall help
