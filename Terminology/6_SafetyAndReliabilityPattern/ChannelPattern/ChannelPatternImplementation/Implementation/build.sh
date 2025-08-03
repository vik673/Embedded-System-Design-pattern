#!/bin/bash

# Build script for Channel Pattern Demo (Linux/Mac)
echo "================================================"
echo "Building Channel Pattern Implementation Demo"
echo "================================================"

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build the project
echo "Building project..."
cmake --build . --config Release
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build completed successfully!"
echo "================================================"

# Try to run the demo
echo "Running Channel Pattern Demo..."
echo "================================================"

if [ -x "./ChannelPatternDemo" ]; then
    ./ChannelPatternDemo
elif [ -x "./bin/ChannelPatternDemo" ]; then
    ./bin/ChannelPatternDemo
else
    echo "Could not find the executable file!"
    echo "Please check the build output."
    find . -name "ChannelPatternDemo" -type f
fi

echo "================================================"
echo "Demo completed!"
