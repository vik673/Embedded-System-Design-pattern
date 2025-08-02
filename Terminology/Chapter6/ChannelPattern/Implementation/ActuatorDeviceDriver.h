#ifndef ACTUATOR_DEVICE_DRIVER_H
#define ACTUATOR_DEVICE_DRIVER_H

/**
 * @brief Base class for actuator device drivers in the Channel Pattern
 * 
 * This class handles the control of physical actuators using processed data
 * from the transformation chain.
 */
class ActuatorDeviceDriver {
protected:
    int deviceId;
    double currentValue;
    bool isEnabled;

public:
    ActuatorDeviceDriver(int id = 0);
    virtual ~ActuatorDeviceDriver();
    
    /**
     * @brief Actuate the physical device with the given value
     * @param value Processed value to use for actuation
     */
    virtual void actuate(double value) = 0;
    
    /**
     * @brief Get the current actuator value
     * @return Current actuator value
     */
    double getCurrentValue() const;
    
    /**
     * @brief Enable or disable the actuator
     * @param enabled True to enable, false to disable
     */
    void setEnabled(bool enabled);
    
    /**
     * @brief Check if actuator is enabled
     * @return True if enabled, false otherwise
     */
    bool isActuatorEnabled() const;
    
    /**
     * @brief Get the device ID
     * @return Device identifier
     */
    int getDeviceId() const;

protected:
    /**
     * @brief Control the physical actuator hardware
     * @param value Value to apply to the actuator
     */
    virtual void controlPhysicalDevice(double value) = 0;
    
    /**
     * @brief Validate that the input value is within acceptable range
     * @param value Value to validate
     * @return True if valid, false otherwise
     */
    virtual bool validateValue(double value);
};

#endif // ACTUATOR_DEVICE_DRIVER_H
