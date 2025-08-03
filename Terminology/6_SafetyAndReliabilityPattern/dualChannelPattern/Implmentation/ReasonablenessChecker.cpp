#include "ReasonablenessChecker.h"
#include <cmath>
#include <iostream>

ReasonablenessChecker::ReasonablenessChecker(double maxRate, double minValue, double maxValue)
    : maxRateOfChange(maxRate), minAbsoluteValue(minValue), maxAbsoluteValue(maxValue),
      previousOutput(0.0), hasPreviousOutput(false) {
}

bool ReasonablenessChecker::validateTransformation(double input, double output) {
    if (std::isnan(input) || std::isnan(output)) {
        std::cerr << "ReasonablenessChecker: NaN values detected - validation failed" << std::endl;
        if (getCurrentChannel() && getAlternativeChannel()) {
            switchToAlternativeChannel();
        }
        return false;
    }

    // Check absolute value limits
    if (!isWithinAbsoluteLimits(output)) {
        std::cerr << "ReasonablenessChecker: Output " << output 
                  << " outside limits [" << minAbsoluteValue << ", " << maxAbsoluteValue 
                  << "] - validation failed" << std::endl;
        if (getCurrentChannel() && getAlternativeChannel()) {
            switchToAlternativeChannel();
        }
        return false;
    }

    // Check rate of change
    if (!isRateOfChangeAcceptable(output)) {
        std::cerr << "ReasonablenessChecker: Rate of change too high for output " << output 
                  << " (previous: " << previousOutput << ") - validation failed" << std::endl;
        if (getCurrentChannel() && getAlternativeChannel()) {
            switchToAlternativeChannel();
        }
        return false;
    }

    // Update previous output for next check
    previousOutput = output;
    hasPreviousOutput = true;

    std::cout << "ReasonablenessChecker: Transformation validated - Input=" << input 
              << ", Output=" << output << std::endl;
    return true;
}

void ReasonablenessChecker::reset() {
    hasPreviousOutput = false;
    previousOutput = 0.0;
}

void ReasonablenessChecker::setMaxRateOfChange(double maxRate) {
    if (maxRate > 0.0) {
        maxRateOfChange = maxRate;
    }
}

void ReasonablenessChecker::setValueLimits(double minValue, double maxValue) {
    if (minValue <= maxValue) {
        minAbsoluteValue = minValue;
        maxAbsoluteValue = maxValue;
    }
}

bool ReasonablenessChecker::isWithinAbsoluteLimits(double value) {
    return value >= minAbsoluteValue && value <= maxAbsoluteValue;
}

bool ReasonablenessChecker::isRateOfChangeAcceptable(double currentOutput) {
    if (!hasPreviousOutput) {
        return true; // First output, no rate of change to check
    }

    double rateOfChange = std::abs(currentOutput - previousOutput);
    return rateOfChange <= maxRateOfChange;
}
