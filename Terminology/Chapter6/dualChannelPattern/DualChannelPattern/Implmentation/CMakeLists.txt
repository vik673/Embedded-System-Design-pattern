cmake_minimum_required(VERSION 3.10)
project(DualChannelPattern)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for better debugging and warnings
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Create executable
add_executable(DualChannelPatternDemo
    main.cpp
    AbstractDataTransform.cpp
    AbstractTransformChecker.cpp
    SensorDeviceDriver.cpp
    ActuatorDeviceDriver.cpp
    Channel.cpp
    DualChannelPattern.cpp
    OpticalWheelSpeedSensor.cpp
    GPSSpeedSensor.cpp
    EngineActuator.cpp
    SpeedFilterTransform.cpp
    SpeedToEngineOutputTransform.cpp
    ReasonablenessChecker.cpp
)

# Set output directory
set_target_properties(DualChannelPatternDemo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    target_compile_definitions(DualChannelPatternDemo PRIVATE _USE_MATH_DEFINES)
    set_target_properties(DualChannelPatternDemo PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    )
endif()

# Add math library on Unix-like systems
if(UNIX)
    target_link_libraries(DualChannelPatternDemo m)
endif()

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ flags: ${CMAKE_CXX_FLAGS}")
