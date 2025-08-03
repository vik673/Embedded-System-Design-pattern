#include "SpeedFilterTransform.h"
#include <numeric>
#include <cmath>
#include <iostream>
#include <limits>

SpeedFilterTransform::SpeedFilterTransform(size_t filterWindowSize, double minSpeed, double maxSpeed)
    : windowSize(filterWindowSize), minValidSpeed(minSpeed), maxValidSpeed(maxSpeed) {
    history.reserve(windowSize);
}

double SpeedFilterTransform::processData(double input) {
    if (std::isnan(input) || !isValidSpeed(input)) {
        std::cerr << "SpeedFilterTransform: Invalid input speed: " << input << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Add to history
    history.push_back(input);
    
    // Maintain window size
    if (history.size() > windowSize) {
        history.erase(history.begin());
    }

    // Calculate filtered output
    double filteredSpeed = calculateMovingAverage();
    
    std::cout << "SpeedFilterTransform: Input=" << input << " m/s, Filtered=" << filteredSpeed << " m/s" << std::endl;
    
    return filteredSpeed;
}

void SpeedFilterTransform::reset() {
    history.clear();
}

double SpeedFilterTransform::calculateMovingAverage() {
    if (history.empty()) {
        return 0.0;
    }

    double sum = std::accumulate(history.begin(), history.end(), 0.0);
    return sum / history.size();
}

bool SpeedFilterTransform::isValidSpeed(double speed) {
    return speed >= minValidSpeed && speed <= maxValidSpeed;
}
