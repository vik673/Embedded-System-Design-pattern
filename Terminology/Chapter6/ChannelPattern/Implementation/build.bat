@echo off
REM Build script for Channel Pattern Demo
echo ================================================
echo Building Channel Pattern Implementation Demo
echo ================================================

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
cmake ..
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo ================================================

REM Try to run the demo
echo Running Channel Pattern Demo...
echo ================================================

if exist "Release\ChannelPatternDemo.exe" (
    Release\ChannelPatternDemo.exe
) else if exist "bin\Release\ChannelPatternDemo.exe" (
    bin\Release\ChannelPatternDemo.exe
) else if exist "ChannelPatternDemo.exe" (
    ChannelPatternDemo.exe
) else (
    echo Could not find the executable file!
    echo Please check the build output.
    dir /s *.exe
)

echo ================================================
echo Demo completed!
pause
