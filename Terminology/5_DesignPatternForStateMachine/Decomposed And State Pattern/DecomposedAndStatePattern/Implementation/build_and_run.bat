@echo off
echo Decomposed AND-State Pattern Demo Builder
echo ========================================

REM Check if GCC is available
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: GCC compiler not found. Please install MinGW or similar.
    echo You can download it from: https://www.mingw-w64.org/
    pause
    exit /b 1
)

echo.
echo Building the demo...
echo.

REM Clean previous build
if exist decomposed_and_state_demo.exe del decomposed_and_state_demo.exe
if exist *.o del *.o

REM Compile all source files
gcc -Wall -Wextra -std=c99 -g -c main.c
gcc -Wall -Wextra -std=c99 -g -c LightControllerClient.c
gcc -Wall -Wextra -std=c99 -g -c LightController.c
gcc -Wall -Wextra -std=c99 -g -c ErrorStateClass.c
gcc -Wall -Wextra -std=c99 -g -c ModeStateClass.c
gcc -Wall -Wextra -std=c99 -g -c AndStateList.c
gcc -Wall -Wextra -std=c99 -g -c StateActionSet.c
gcc -Wall -Wextra -std=c99 -g -c Light.c
gcc -Wall -Wextra -std=c99 -g -c Klaxon.c
gcc -Wall -Wextra -std=c99 -g -c Mutex.c

REM Link all object files
gcc -Wall -Wextra -std=c99 -g -o decomposed_and_state_demo.exe main.o LightControllerClient.o LightController.o ErrorStateClass.o ModeStateClass.o AndStateList.o StateActionSet.o Light.o Klaxon.o Mutex.o

if %errorlevel% neq 0 (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful!
echo.

REM Clean object files
del *.o

echo Running the demo...
echo.
decomposed_and_state_demo.exe

echo.
echo Demo completed.
pause
