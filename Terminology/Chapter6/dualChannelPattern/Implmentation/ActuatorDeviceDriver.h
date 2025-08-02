#ifndef ACTUATOR_DEVICE_DRIVER_H
#define ACTUATOR_DEVICE_DRIVER_H

/**
 * @brief Abstract base class for actuator device drivers
 * 
 * This class uses the computed output values to drive one or more actuators,
 * such as a motor, light, or heating unit.
 */
class ActuatorDeviceDriver {
public:
    ActuatorDeviceDriver() = default;
    virtual ~ActuatorDeviceDriver() = default;

    /**
     * @brief Pure virtual function to actuate based on computed value
     * @param value The computed output value to act upon
     */
    virtual void actuate(double value) = 0;

    /**
     * @brief Initialize the actuator
     * @return true if initialization successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Check if actuator is operational
     * @return true if actuator is working properly, false otherwise
     */
    virtual bool isOperational() = 0;

    /**
     * @brief Get actuator identification
     * @return String identifying the actuator type
     */
    virtual const char* getActuatorType() const = 0;

    /**
     * @brief Stop the actuator (safety function)
     */
    virtual void stop() = 0;
};

#endif // ACTUATOR_DEVICE_DRIVER_H
