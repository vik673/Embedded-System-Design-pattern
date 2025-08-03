#ifndef ENGINE_ACTUATOR_H
#define ENGINE_ACTUATOR_H

#include "ActuatorDeviceDriver.h"

/**
 * @brief Engine actuator for train speed control
 * 
 * This actuator controls the train engine based on the computed desired output.
 */
class EngineActuator : public ActuatorDeviceDriver {
private:
    bool operational;
    double currentOutput;
    double maxOutput;
    double minOutput;

public:
    /**
     * @brief Constructor
     * @param minPower Minimum engine power (0.0 to 1.0)
     * @param maxPower Maximum engine power (0.0 to 1.0)
     */
    EngineActuator(double minPower = 0.0, double maxPower = 1.0);

    /**
     * @brief Actuate the engine based on computed value
     * @param value Desired engine output (0.0 to 1.0)
     */
    void actuate(double value) override;

    /**
     * @brief Initialize the engine actuator
     * @return true if initialization successful
     */
    bool initialize() override;

    /**
     * @brief Check if actuator is operational
     * @return true if operational
     */
    bool isOperational() override;

    /**
     * @brief Get actuator type identification
     * @return Actuator type string
     */
    const char* getActuatorType() const override;

    /**
     * @brief Stop the engine (emergency stop)
     */
    void stop() override;

    /**
     * @brief Get current engine output
     * @return Current output value
     */
    double getCurrentOutput() const;

    /**
     * @brief Set output limits
     * @param minPower Minimum power
     * @param maxPower Maximum power
     */
    void setOutputLimits(double minPower, double maxPower);

    /**
     * @brief Simulate actuator failure for testing
     */
    void simulateFailure();

    /**
     * @brief Restore actuator operation
     */
    void restoreOperation();

private:
    /**
     * @brief Clamp value to output limits
     * @param value Value to clamp
     * @return Clamped value
     */
    double clampOutput(double value);
};

#endif // ENGINE_ACTUATOR_H
