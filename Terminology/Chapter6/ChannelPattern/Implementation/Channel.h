#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include <memory>
#include "SensorDeviceDriver.h"
#include "AbstractDataTransform.h"
#include "ActuatorDeviceDriver.h"

/**
 * @brief Main Channel class that orchestrates the entire data processing pipeline
 * 
 * The Channel Pattern provides an architectural structure for end-to-end processing
 * from data acquisition through transformations to physical actuation.
 */
class Channel {
private:
    std::unique_ptr<SensorDeviceDriver> sensor;
    std::vector<std::unique_ptr<AbstractDataTransform>> transforms;
    std::unique_ptr<ActuatorDeviceDriver> actuator;
    bool isInitialized;

public:
    Channel();
    ~Channel();
    
    /**
     * @brief Initialize the channel with sensor, transforms, and actuator
     * @param sensorDriver Sensor device driver
     * @param actuatorDriver Actuator device driver
     */
    void initialize(std::unique_ptr<SensorDeviceDriver> sensorDriver,
                   std::unique_ptr<ActuatorDeviceDriver> actuatorDriver);
    
    /**
     * @brief Add a data transformation to the processing chain
     * @param transform Data transformation to add
     */
    void addTransform(std::unique_ptr<AbstractDataTransform> transform);
    
    /**
     * @brief Process data through the entire channel pipeline
     */
    void processChannel();
    
    /**
     * @brief Get the current sensor reading without processing
     * @return Raw sensor data
     */
    double getCurrentSensorReading();
    
    /**
     * @brief Get the current actuator value
     * @return Current actuator value
     */
    double getCurrentActuatorValue();
    
    /**
     * @brief Check if the channel is properly initialized
     * @return True if initialized, false otherwise
     */
    bool getInitializationStatus() const;
    
    /**
     * @brief Get the number of transformations in the chain
     * @return Number of transforms
     */
    size_t getTransformCount() const;
    
    /**
     * @brief Enable or disable the entire channel
     * @param enabled True to enable, false to disable
     */
    void setChannelEnabled(bool enabled);
    
    /**
     * @brief Cleanup the channel and reset all components
     */
    void cleanup();

private:
    /**
     * @brief Set up the relationships between channel components
     */
    void initializeRelations();
    
    /**
     * @brief Validate the channel configuration
     * @return True if valid, false otherwise
     */
    bool validateConfiguration();
};

#endif // CHANNEL_H
