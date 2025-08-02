cmake_minimum_required(VERSION 3.12)
project(DeadlockPatternDemo VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific options
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-D_WIN32_WINNT=0x0601)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
endif()

# Find required packages
find_package(Threads REQUIRED)

# Source files
set(SOURCES
    DeadlockPattern.cpp
)

set(HEADERS
    DeadlockPattern.h
)

# Create executable
add_executable(DeadlockPatternDemo ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(DeadlockPatternDemo Threads::Threads)

# Set output directory
set_target_properties(DeadlockPatternDemo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation rules
install(TARGETS DeadlockPatternDemo
    RUNTIME DESTINATION bin
)

# Custom targets for convenience
add_custom_target(run
    COMMAND DeadlockPatternDemo
    DEPENDS DeadlockPatternDemo
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMENT "Running Deadlock Pattern Demo"
)

# Debug configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(DeadlockPatternDemo PRIVATE DEBUG)
endif()

# Release configuration
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(DeadlockPatternDemo PRIVATE NDEBUG)
    if(NOT MSVC)
        target_compile_options(DeadlockPatternDemo PRIVATE -O3)
    endif()
endif()

# Print build information
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
