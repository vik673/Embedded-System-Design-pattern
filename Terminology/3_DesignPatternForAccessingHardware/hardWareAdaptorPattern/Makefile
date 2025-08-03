# Makefile for Hardware Adapter Pattern

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
TARGET = hardware_adapter_demo
SOURCES = main.cpp HardwareAdapterPattern.cpp
HEADERS = HardwareAdapterPattern.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Windows-specific run target
run-windows: $(TARGET)
	$(TARGET).exe

.PHONY: all clean run run-windows
