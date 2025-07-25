cmake_minimum_required(VERSION 3.10)
project(ChannelPatternDemo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SOURCES
    main.cpp
    AbstractDataTransform.cpp
    SensorDeviceDriver.cpp
    ActuatorDeviceDriver.cpp
    Channel.cpp
    EMGSensorDeviceDriver.cpp
    ConvertToFrequency.cpp
    MovingAverageFilter.cpp
    CalculateColor.cpp
    LightDeviceDriver.cpp
    EMGChannel.cpp
)

# Header files (for IDE support)
set(HEADERS
    AbstractDataTransform.h
    SensorDeviceDriver.h
    ActuatorDeviceDriver.h
    Channel.h
    EMGSensorDeviceDriver.h
    ConvertToFrequency.h
    MovingAverageFilter.h
    CalculateColor.h
    LightDeviceDriver.h
    EMGChannel.h
)

# Create executable
add_executable(ChannelPatternDemo ${SOURCES} ${HEADERS})

# Set output directory
set_target_properties(ChannelPatternDemo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add custom target for running the demo
add_custom_target(run
    COMMAND ChannelPatternDemo
    DEPENDS ChannelPatternDemo
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMENT "Running Channel Pattern Demo"
)

# Print build information
message(STATUS "Channel Pattern Demo Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")

# Optional: Add testing support
option(BUILD_TESTS "Build unit tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    # Add test subdirectory if it exists
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
        add_subdirectory(tests)
    endif()
endif()

# Installation rules
install(TARGETS ChannelPatternDemo
    RUNTIME DESTINATION bin
)

install(FILES ${HEADERS}
    DESTINATION include/ChannelPattern
)
