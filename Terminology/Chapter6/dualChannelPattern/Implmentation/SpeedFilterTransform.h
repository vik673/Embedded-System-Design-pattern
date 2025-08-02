#ifndef SPEED_FILTER_TRANSFORM_H
#define SPEED_FILTER_TRANSFORM_H

#include "AbstractDataTransform.h"
#include <vector>

/**
 * @brief Speed filtering transformation
 * 
 * This transform filters and validates speed data to remove noise and outliers.
 */
class SpeedFilterTransform : public AbstractDataTransform {
private:
    std::vector<double> history;
    size_t windowSize;
    double maxValidSpeed;
    double minValidSpeed;

public:
    /**
     * @brief Constructor
     * @param filterWindowSize Size of the moving average window
     * @param minSpeed Minimum valid speed
     * @param maxSpeed Maximum valid speed
     */
    SpeedFilterTransform(size_t filterWindowSize = 5, double minSpeed = 0.0, double maxSpeed = 100.0);

    /**
     * @brief Process speed data through filter
     * @param input Raw speed input
     * @return Filtered speed output
     */
    double processData(double input) override;

    /**
     * @brief Reset the filter history
     */
    void reset();

private:
    /**
     * @brief Calculate moving average from history
     * @return Moving average value
     */
    double calculateMovingAverage();

    /**
     * @brief Validate if speed is within acceptable range
     * @param speed Speed to validate
     * @return true if valid, false otherwise
     */
    bool isValidSpeed(double speed);
};

#endif // SPEED_FILTER_TRANSFORM_H
