#ifndef REASONABLENESS_CHECKER_H
#define REASONABLENESS_CHECKER_H

#include "AbstractTransformChecker.h"

/**
 * @brief Concrete transform checker that validates reasonableness of transformations
 * 
 * This checker ensures that transformations produce reasonable outputs given the inputs.
 */
class ReasonablenessChecker : public AbstractTransformChecker {
private:
    double maxRateOfChange;
    double previousOutput;
    bool hasPreviousOutput;
    double maxAbsoluteValue;
    double minAbsoluteValue;

public:
    /**
     * @brief Constructor
     * @param maxRate Maximum rate of change between consecutive outputs
     * @param minValue Minimum absolute value for outputs
     * @param maxValue Maximum absolute value for outputs
     */
    ReasonablenessChecker(double maxRate = 5.0, double minValue = 0.0, double maxValue = 1.0);

    /**
     * @brief Validate a transformation
     * @param input Input value to the transformation
     * @param output Output value from the transformation
     * @return true if transformation is reasonable, false otherwise
     */
    bool validateTransformation(double input, double output) override;

    /**
     * @brief Reset the checker state
     */
    void reset();

    /**
     * @brief Set maximum rate of change
     * @param maxRate New maximum rate of change
     */
    void setMaxRateOfChange(double maxRate);

    /**
     * @brief Set value limits
     * @param minValue Minimum allowed value
     * @param maxValue Maximum allowed value
     */
    void setValueLimits(double minValue, double maxValue);

private:
    /**
     * @brief Check if output is within absolute limits
     * @param value Value to check
     * @return true if within limits, false otherwise
     */
    bool isWithinAbsoluteLimits(double value);

    /**
     * @brief Check if rate of change is acceptable
     * @param currentOutput Current output value
     * @return true if rate of change is acceptable, false otherwise
     */
    bool isRateOfChangeAcceptable(double currentOutput);
};

#endif // REASONABLENESS_CHECKER_H
