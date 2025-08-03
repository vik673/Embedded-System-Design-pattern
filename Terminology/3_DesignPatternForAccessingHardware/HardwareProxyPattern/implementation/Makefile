# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target executable
TARGET = motor_demo

# Source files
SOURCES = main.cpp MotorProxy.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = MotorProxy.hpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Build object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the motor demo (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  rebuild - Clean and build"
	@echo "  run     - Build and run the demo"
	@echo "  debug   - Build with debug symbols"
	@echo "  help    - Show this help message"

.PHONY: all clean rebuild run debug help
