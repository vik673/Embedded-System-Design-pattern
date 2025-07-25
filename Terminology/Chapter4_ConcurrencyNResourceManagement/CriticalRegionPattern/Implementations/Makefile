# Makefile for Critical Region Pattern Implementation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = critical_region_demo
SRCDIR = .
OBJDIR = obj

# Source files
SOURCES = main.c \
          CRRobotArmManager.c \
          CRDisplay.c \
          RobotArm.c \
          UserInput.c \
          OS_TaskSwitching.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Create target executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Create object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
	@echo "Clean complete"

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install-deps:
	@echo "No external dependencies required for this demo"

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build the critical region pattern demo"
	@echo "  clean      - Remove build artifacts"
	@echo "  run        - Build and run the demo"
	@echo "  help       - Show this help message"

.PHONY: all clean run install-deps help
