#include "LightDeviceDriver.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

LightDeviceDriver::LightDeviceDriver(int id) 
    : ActuatorDeviceDriver(id), currentRed(0), currentGreen(0), 
      currentBlue(0), currentColor(0), brightness(1.0) {
}

LightDeviceDriver::~LightDeviceDriver() {
    // Turn off light when destroying
    setLightColor(0, 0, 0);
}

void LightDeviceDriver::actuate(double value) {
    if (!isActuatorEnabled() || !validateValue(value)) {
        return;
    }
    
    currentValue = value;
    controlPhysicalDevice(value);
}

void LightDeviceDriver::setLightColor(int red, int green, int blue) {
    // Clamp values to valid range
    currentRed = std::max(0, std::min(255, red));
    currentGreen = std::max(0, std::min(255, green));
    currentBlue = std::max(0, std::min(255, blue));
    
    // Pack into single color value
    currentColor = (static_cast<long>(currentRed) << 16) + 
                   (static_cast<long>(currentGreen) << 8) + 
                   static_cast<long>(currentBlue);
    
    currentValue = static_cast<double>(currentColor);
    
    // Apply brightness and control hardware
    int adjustedRed = currentRed, adjustedGreen = currentGreen, adjustedBlue = currentBlue;
    applyBrightness(adjustedRed, adjustedGreen, adjustedBlue);
    simulateLightControl(adjustedRed, adjustedGreen, adjustedBlue);
}

long LightDeviceDriver::getCurrentColor() const {
    return currentColor;
}

int LightDeviceDriver::getCurrentRed() const {
    return currentRed;
}

int LightDeviceDriver::getCurrentGreen() const {
    return currentGreen;
}

int LightDeviceDriver::getCurrentBlue() const {
    return currentBlue;
}

void LightDeviceDriver::setBrightness(double level) {
    brightness = std::max(0.0, std::min(1.0, level));
}

double LightDeviceDriver::getBrightness() const {
    return brightness;
}

void LightDeviceDriver::controlPhysicalDevice(double value) {
    // Unpack RGB from the color value
    long colorValue = static_cast<long>(value);
    int red, green, blue;
    unpackRGB(colorValue, red, green, blue);
    
    // Update current color
    setLightColor(red, green, blue);
}

bool LightDeviceDriver::validateValue(double value) {
    if (!ActuatorDeviceDriver::validateValue(value)) {
        return false;
    }
    
    // Check if value represents a valid RGB color
    long colorValue = static_cast<long>(value);
    return (colorValue >= 0 && colorValue <= 0xFFFFFF);
}

void LightDeviceDriver::unpackRGB(long packedColor, int& red, int& green, int& blue) {
    red = (packedColor >> 16) & 0xFF;
    green = (packedColor >> 8) & 0xFF;
    blue = packedColor & 0xFF;
}

void LightDeviceDriver::applyBrightness(int& red, int& green, int& blue) {
    red = static_cast<int>(red * brightness);
    green = static_cast<int>(green * brightness);
    blue = static_cast<int>(blue * brightness);
}

void LightDeviceDriver::simulateLightControl(int red, int green, int blue) {
    // Simulate controlling actual light hardware
    std::cout << "Light Control - RGB(" 
              << std::setw(3) << red << ", "
              << std::setw(3) << green << ", "
              << std::setw(3) << blue << ") "
              << "Hex: #" << std::hex << std::setfill('0')
              << std::setw(2) << red
              << std::setw(2) << green  
              << std::setw(2) << blue
              << std::dec << std::setfill(' ') << std::endl;
}
