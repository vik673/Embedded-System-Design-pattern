#ifndef SENSOR_DEVICE_DRIVER_H
#define SENSOR_DEVICE_DRIVER_H

#include "AbstractDataTransform.h"

/**
 * @brief Base class for sensor device drivers in the Channel Pattern
 * 
 * This class handles the acquisition of data from physical sensors
 * and initiates the data processing chain.
 */
class SensorDeviceDriver {
protected:
    int sensorId;
    int sensitivity;
    AbstractDataTransform* firstTransform;

public:
    SensorDeviceDriver(int id = 0);
    virtual ~SensorDeviceDriver();
    
    /**
     * @brief Acquire data from the physical sensor
     * @return Raw sensor data
     */
    virtual double acquireData() = 0;
    
    /**
     * @brief Set sensor sensitivity
     * @param sens Sensitivity value
     */
    virtual void setSensitivity(int sens);
    
    /**
     * @brief Get current sensitivity setting
     * @return Current sensitivity value
     */
    int getSensitivity() const;
    
    /**
     * @brief Set the first transformation in the processing chain
     * @param transform Pointer to the first data transformation
     */
    void setFirstTransform(AbstractDataTransform* transform);
    
    /**
     * @brief Get the first transform in the chain
     * @return Pointer to first transform
     */
    AbstractDataTransform* getFirstTransform() const;
    
    /**
     * @brief Start the data processing chain
     */
    void startProcessing();

protected:
    /**
     * @brief Read data from the physical sensor hardware
     * @return Raw sensor reading
     */
    virtual double readPhysicalSensor() = 0;
};

#endif // SENSOR_DEVICE_DRIVER_H
