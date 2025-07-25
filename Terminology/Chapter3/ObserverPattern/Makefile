# Makefile for Observer Pattern Demo

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = observer_demo
SOURCES = ObserverPattern.c demo.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = ObserverPattern.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) gas_sensor_log.txt

# Individual object file dependencies
ObserverPattern.o: ObserverPattern.c ObserverPattern.h
demo.o: demo.c ObserverPattern.h

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the observer pattern demo"
	@echo "  run     - Build and run the demo"
	@echo "  clean   - Remove all build artifacts and log files"
	@echo "  help    - Show this help message"
