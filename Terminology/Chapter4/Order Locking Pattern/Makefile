# Makefile for Ordered Locking Pattern Implementation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = ordered_locking_demo
OBJS = main.o Mutex.o ResourceList.o Position.o PositionSensor.o \
       Velocity.o VelocitySensor.o Attitude.o AttitudeSensor.o \
       KinematicModelClient.o

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Individual object file rules
main.o: main.c OrderedLockingExample.h Mutex.h ResourceList.h PositionSensor.h VelocitySensor.h AttitudeSensor.h KinematicModelClient.h
	$(CC) $(CFLAGS) -c main.c

Mutex.o: Mutex.c Mutex.h
	$(CC) $(CFLAGS) -c Mutex.c

ResourceList.o: ResourceList.c ResourceList.h OrderedLockingExample.h Mutex.h
	$(CC) $(CFLAGS) -c ResourceList.c

Position.o: Position.c Position.h
	$(CC) $(CFLAGS) -c Position.c

PositionSensor.o: PositionSensor.c PositionSensor.h OrderedLockingExample.h Position.h Mutex.h ResourceList.h
	$(CC) $(CFLAGS) -c PositionSensor.c

Velocity.o: Velocity.c Velocity.h
	$(CC) $(CFLAGS) -c Velocity.c

VelocitySensor.o: VelocitySensor.c VelocitySensor.h OrderedLockingExample.h Velocity.h Mutex.h ResourceList.h
	$(CC) $(CFLAGS) -c VelocitySensor.c

Attitude.o: Attitude.c Attitude.h
	$(CC) $(CFLAGS) -c Attitude.c

AttitudeSensor.o: AttitudeSensor.c AttitudeSensor.h OrderedLockingExample.h Attitude.h Mutex.h ResourceList.h
	$(CC) $(CFLAGS) -c AttitudeSensor.c

KinematicModelClient.o: KinematicModelClient.c KinematicModelClient.h PositionSensor.h VelocitySensor.h AttitudeSensor.h
	$(CC) $(CFLAGS) -c KinematicModelClient.c

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the demo program"
	@echo "  clean   - Remove object files and executable"
	@echo "  run     - Build and run the demo"
	@echo "  help    - Show this help message"

.PHONY: all clean run help
