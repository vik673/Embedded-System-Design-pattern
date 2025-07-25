#ifndef SPEED_TO_ENGINE_OUTPUT_TRANSFORM_H
#define SPEED_TO_ENGINE_OUTPUT_TRANSFORM_H

#include "AbstractDataTransform.h"

/**
 * @brief Transform that converts speed to desired engine output
 * 
 * This transform takes filtered speed data and computes the desired engine output
 * to maintain or adjust the current speed.
 */
class SpeedToEngineOutputTransform : public AbstractDataTransform {
private:
    double targetSpeed;
    double kp; // Proportional gain for simple P controller
    double maxOutput;
    double minOutput;

public:
    /**
     * @brief Constructor
     * @param target Target speed to maintain
     * @param proportionalGain Proportional gain for control
     * @param minEngineOutput Minimum engine output
     * @param maxEngineOutput Maximum engine output
     */
    SpeedToEngineOutputTransform(double target = 10.0, double proportionalGain = 0.1,
                                double minEngineOutput = 0.0, double maxEngineOutput = 1.0);

    /**
     * @brief Process speed data to compute engine output
     * @param input Current speed
     * @return Desired engine output (0.0 to 1.0)
     */
    double processData(double input) override;

    /**
     * @brief Set target speed
     * @param target New target speed
     */
    void setTargetSpeed(double target);

    /**
     * @brief Set control gain
     * @param gain New proportional gain
     */
    void setControlGain(double gain);

    /**
     * @brief Get current target speed
     * @return Current target speed
     */
    double getTargetSpeed() const;

private:
    /**
     * @brief Clamp output to valid range
     * @param output Output to clamp
     * @return Clamped output
     */
    double clampOutput(double output);
};

#endif // SPEED_TO_ENGINE_OUTPUT_TRANSFORM_H
