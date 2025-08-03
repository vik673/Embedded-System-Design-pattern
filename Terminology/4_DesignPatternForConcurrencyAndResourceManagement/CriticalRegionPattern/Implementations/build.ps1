# PowerShell build script for Critical Region Pattern Demo
# Usage: .\build.ps1 [clean|run|help]

param(
    [string]$Action = "build"
)

$ErrorActionPreference = "Stop"

function Show-Help {
    Write-Host "Critical Region Pattern Build Script"
    Write-Host "Usage: .\build.ps1 [action]"
    Write-Host ""
    Write-Host "Actions:"
    Write-Host "  build  - Compile the demo (default)"
    Write-Host "  clean  - Remove build artifacts"
    Write-Host "  run    - Build and run the demo"
    Write-Host "  help   - Show this help message"
}

function Build-Project {
    Write-Host "Building Critical Region Pattern Demo..." -ForegroundColor Green
    
    # Check if gcc is available
    try {
        gcc --version | Out-Null
    }
    catch {
        Write-Host "Error: GCC compiler not found. Please install MinGW-w64 or similar." -ForegroundColor Red
        exit 1
    }
    
    # Create object directory if it doesn't exist
    if (!(Test-Path "obj")) {
        New-Item -ItemType Directory -Name "obj" | Out-Null
    }
    
    # Source files
    $sources = @(
        "main.c",
        "CRRobotArmManager.c",
        "CRDisplay.c",
        "RobotArm.c",
        "UserInput.c",
        "OS_TaskSwitching.c"
    )
    
    # Compile each source file
    foreach ($source in $sources) {
        $object = "obj/" + $source.Replace(".c", ".o")
        Write-Host "Compiling $source..."
        gcc -Wall -Wextra -std=c99 -g -c $source -o $object
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Compilation failed for $source" -ForegroundColor Red
            exit 1
        }
    }
    
    # Link the executable
    Write-Host "Linking executable..."
    $objects = $sources | ForEach-Object { "obj/" + $_.Replace(".c", ".o") }
    gcc $objects -o "critical_region_demo.exe"
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build successful: critical_region_demo.exe" -ForegroundColor Green
    } else {
        Write-Host "Linking failed" -ForegroundColor Red
        exit 1
    }
}

function Clean-Project {
    Write-Host "Cleaning build artifacts..." -ForegroundColor Yellow
    
    if (Test-Path "obj") {
        Remove-Item -Recurse -Force "obj"
    }
    
    if (Test-Path "critical_region_demo.exe") {
        Remove-Item "critical_region_demo.exe"
    }
    
    Write-Host "Clean complete" -ForegroundColor Green
}

function Run-Demo {
    Build-Project
    
    if (Test-Path "critical_region_demo.exe") {
        Write-Host "`nRunning Critical Region Pattern Demo..." -ForegroundColor Cyan
        Write-Host "=" * 50 -ForegroundColor Cyan
        .\critical_region_demo.exe
        Write-Host "=" * 50 -ForegroundColor Cyan
    } else {
        Write-Host "Error: Executable not found" -ForegroundColor Red
        exit 1
    }
}

# Main script logic
switch ($Action.ToLower()) {
    "build" { Build-Project }
    "clean" { Clean-Project }
    "run" { Run-Demo }
    "help" { Show-Help }
    default {
        Write-Host "Unknown action: $Action" -ForegroundColor Red
        Show-Help
        exit 1
    }
}
