# Makefile for One's Complement Pattern Implementation
# Demonstrates memory corruption detection using bit-wise inversion

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0
TARGET = OnesComplementDemo
OBJS = OnesComplementDemo.o OwnShipAttitude.o AttitudeDataType.o AlarmManager.o

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete. Run with: ./$(TARGET)"

# Object file rules
OnesComplementDemo.o: OnesComplementDemo.c OwnShipAttitude.h AttitudeDataType.h AlarmManager.h
	$(CC) $(CFLAGS) -c OnesComplementDemo.c

OwnShipAttitude.o: OwnShipAttitude.c OwnShipAttitude.h AttitudeDataType.h AlarmManager.h
	$(CC) $(CFLAGS) -c OwnShipAttitude.c

AttitudeDataType.o: AttitudeDataType.c AttitudeDataType.h
	$(CC) $(CFLAGS) -c AttitudeDataType.c

AlarmManager.o: AlarmManager.c AlarmManager.h
	$(CC) $(CFLAGS) -c AlarmManager.c

# Run the demonstration
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Clean complete"

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the executable (default)"
	@echo "  run     - Build and run the demonstration"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"

# Generate diagrams (requires PlantUML)
diagrams:
	@echo "Generating UML diagrams..."
	@if command -v plantuml >/dev/null 2>&1; then \
		plantuml -tpng OnesComplementPattern_ClassDiagram.puml; \
		plantuml -tpng OnesComplementPattern_SequenceDiagram.puml; \
		echo "Diagrams generated: ClassDiagram.png and SequenceDiagram.png"; \
	else \
		echo "PlantUML not found. Install PlantUML to generate diagrams."; \
		echo "Visit: https://plantuml.com/download"; \
	fi

.PHONY: all run clean help diagrams
