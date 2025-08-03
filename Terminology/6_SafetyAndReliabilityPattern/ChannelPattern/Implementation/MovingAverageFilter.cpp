#include "MovingAverageFilter.h"
#include <numeric>

MovingAverageFilter::MovingAverageFilter(size_t window) 
    : AbstractDataTransform(), windowSize(window), computedFreq(0.0), currentSum(0.0) {
}

MovingAverageFilter::~MovingAverageFilter() {
    // Cleanup if needed
}

double MovingAverageFilter::processData(double data) {
    updateAverage(data);
    
    // Forward the filtered frequency to next stage
    forwardData(computedFreq);
    
    return computedFreq;
}

double MovingAverageFilter::getFilteredFrequency() const {
    return computedFreq;
}

void MovingAverageFilter::setWindowSize(size_t window) {
    if (window == 0) window = 1; // Ensure minimum window size
    
    windowSize = window;
    
    // Adjust current buffer if it's larger than new window size
    while (frequencyHistory.size() > windowSize) {
        currentSum -= frequencyHistory.front();
        frequencyHistory.pop_front();
    }
    
    // Recalculate average with new window size
    if (!frequencyHistory.empty()) {
        computedFreq = currentSum / frequencyHistory.size();
    }
}

size_t MovingAverageFilter::getWindowSize() const {
    return windowSize;
}

void MovingAverageFilter::reset() {
    frequencyHistory.clear();
    computedFreq = 0.0;
    currentSum = 0.0;
}

bool MovingAverageFilter::isBufferFull() const {
    return frequencyHistory.size() >= windowSize;
}

void MovingAverageFilter::updateAverage(double newValue) {
    // Add new value to the history
    frequencyHistory.push_back(newValue);
    currentSum += newValue;
    
    // Remove oldest value if window is exceeded
    if (frequencyHistory.size() > windowSize) {
        currentSum -= frequencyHistory.front();
        frequencyHistory.pop_front();
    }
    
    // Calculate new average
    if (!frequencyHistory.empty()) {
        computedFreq = currentSum / frequencyHistory.size();
    } else {
        computedFreq = 0.0;
    }
}
