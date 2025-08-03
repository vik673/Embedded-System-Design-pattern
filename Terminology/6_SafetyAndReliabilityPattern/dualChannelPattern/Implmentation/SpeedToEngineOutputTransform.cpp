#include "SpeedToEngineOutputTransform.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

SpeedToEngineOutputTransform::SpeedToEngineOutputTransform(double target, double proportionalGain,
                                                         double minEngineOutput, double maxEngineOutput)
    : targetSpeed(target), kp(proportionalGain), minOutput(minEngineOutput), maxOutput(maxEngineOutput) {
}

double SpeedToEngineOutputTransform::processData(double input) {
    if (std::isnan(input)) {
        std::cerr << "SpeedToEngineOutputTransform: Invalid input speed" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Simple proportional controller
    double error = targetSpeed - input;
    double output = kp * error;
    
    // Add base output to maintain current speed (assume 50% for steady state)
    output += 0.5;
    
    // Clamp to valid range
    output = clampOutput(output);
    
    std::cout << "SpeedToEngineOutputTransform: Speed=" << input << " m/s, Target=" << targetSpeed 
              << " m/s, Error=" << error << " m/s, Engine Output=" << (output * 100.0) << "%" << std::endl;
    
    return output;
}

void SpeedToEngineOutputTransform::setTargetSpeed(double target) {
    if (target >= 0.0) {
        targetSpeed = target;
    }
}

void SpeedToEngineOutputTransform::setControlGain(double gain) {
    if (gain > 0.0) {
        kp = gain;
    }
}

double SpeedToEngineOutputTransform::getTargetSpeed() const {
    return targetSpeed;
}

double SpeedToEngineOutputTransform::clampOutput(double output) {
    return std::clamp(output, minOutput, maxOutput);
}
