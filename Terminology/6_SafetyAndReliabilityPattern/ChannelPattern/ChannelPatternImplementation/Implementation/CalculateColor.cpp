#include "CalculateColor.h"
#include <algorithm>
#include <cmath>

CalculateColor::CalculateColor(double minFreq, double maxFreq) 
    : AbstractDataTransform(), red(0), green(0), blue(0), 
      minFrequency(minFreq), maxFrequency(maxFreq) {
}

CalculateColor::~CalculateColor() {
    // Cleanup if needed
}

double CalculateColor::processData(double data) {
    frequencyToColor(data);
    
    // Pack RGB into a double for forwarding (simplified approach)
    double colorValue = static_cast<double>(getRGBValue());
    
    // Forward the color value to the actuator
    forwardData(colorValue);
    
    return colorValue;
}

int CalculateColor::getRed() const {
    return red;
}

int CalculateColor::getGreen() const {
    return green;
}

int CalculateColor::getBlue() const {
    return blue;
}

long CalculateColor::getRGBValue() const {
    return (static_cast<long>(red) << 16) + 
           (static_cast<long>(green) << 8) + 
           static_cast<long>(blue);
}

void CalculateColor::setFrequencyRange(double minFreq, double maxFreq) {
    minFrequency = minFreq;
    maxFrequency = maxFreq;
}

void CalculateColor::getFrequencyRange(double& minFreq, double& maxFreq) const {
    minFreq = minFrequency;
    maxFreq = maxFrequency;
}

void CalculateColor::frequencyToColor(double frequency) {
    // Normalize frequency to 0-1 range
    double normalizedFreq = (frequency - minFrequency) / (maxFrequency - minFrequency);
    normalizedFreq = std::max(0.0, std::min(1.0, normalizedFreq));
    
    // Map to hue (0-300 degrees, avoiding purple/magenta range)
    double hue = normalizedFreq * 300.0;
    
    // Use high saturation and value for vibrant colors
    double saturation = 0.8;
    double value = 0.9;
    
    // Convert HSV to RGB
    hsvToRgb(hue, saturation, value);
}

void CalculateColor::hsvToRgb(double h, double s, double v) {
    double c = v * s;
    double x = c * (1.0 - std::abs(std::fmod(h / 60.0, 2.0) - 1.0));
    double m = v - c;
    
    double r, g, b;
    
    if (h < 60.0) {
        r = c; g = x; b = 0;
    } else if (h < 120.0) {
        r = x; g = c; b = 0;
    } else if (h < 180.0) {
        r = 0; g = c; b = x;
    } else if (h < 240.0) {
        r = 0; g = x; b = c;
    } else if (h < 300.0) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }
    
    red = clampColorValue((r + m) * 255.0);
    green = clampColorValue((g + m) * 255.0);
    blue = clampColorValue((b + m) * 255.0);
}

int CalculateColor::clampColorValue(double value) {
    return static_cast<int>(std::max(0.0, std::min(255.0, std::round(value))));
}
