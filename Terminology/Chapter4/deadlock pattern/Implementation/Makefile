# Deadlock Pattern Makefile
# For Windows with MSVC or MinGW

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread
TARGET = deadlock_demo
SOURCES = DeadlockPattern.cpp
HEADERS = DeadlockPattern.h
OBJECTS = $(SOURCES:.cpp=.o)

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
	del /Q *.o $(TARGET).exe 2>nul || true

# Alternative clean for Unix-like systems
clean-unix:
	rm -f *.o $(TARGET)

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build (default)
release: CXXFLAGS += -DNDEBUG
release: $(TARGET)

# Install dependencies (if needed)
install-deps:
	@echo "No external dependencies required for this demo"

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the deadlock demo (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  run      - Build and run the demo"
	@echo "  debug    - Build with debug information"
	@echo "  release  - Build optimized release version"
	@echo "  help     - Show this help message"

# CMake alternative (commented out)
# cmake-build:
# 	mkdir -p build
# 	cd build && cmake .. && make

# Visual Studio build (commented out)
# vs-build:
# 	cl /EHsc /std:c++17 $(SOURCES) /Fe$(TARGET).exe

.PHONY: all clean clean-unix run debug release install-deps help
