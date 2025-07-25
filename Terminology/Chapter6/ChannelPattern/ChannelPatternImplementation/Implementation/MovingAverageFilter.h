#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include "AbstractDataTransform.h"
#include <vector>
#include <deque>

/**
 * @brief Moving average filter for smoothing frequency data
 * 
 * This filter smooths out rapid frequency changes by averaging
 * values over a sliding window of recent samples.
 */
class MovingAverageFilter : public AbstractDataTransform {
private:
    std::deque<double> frequencyHistory;
    double computedFreq;
    size_t windowSize;
    double currentSum;

public:
    MovingAverageFilter(size_t window = 10);
    virtual ~MovingAverageFilter();
    
    /**
     * @brief Process frequency data through moving average filter
     * @param data Input frequency value
     * @return Filtered frequency value
     */
    virtual double processData(double data) override;
    
    /**
     * @brief Get the current filtered frequency
     * @return Most recent filtered frequency
     */
    double getFilteredFrequency() const;
    
    /**
     * @brief Set the window size for the moving average
     * @param window Number of samples in the moving window
     */
    void setWindowSize(size_t window);
    
    /**
     * @brief Get current window size
     * @return Current window size
     */
    size_t getWindowSize() const;
    
    /**
     * @brief Reset the filter state
     */
    void reset();
    
    /**
     * @brief Check if the filter buffer is full
     * @return True if buffer is full, false otherwise
     */
    bool isBufferFull() const;

private:
    /**
     * @brief Update the moving average calculation
     * @param newValue New value to add to the average
     */
    void updateAverage(double newValue);
};

#endif // MOVING_AVERAGE_FILTER_H
