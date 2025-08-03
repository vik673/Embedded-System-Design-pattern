#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>
#include <vector>
#include "SensorDeviceDriver.h"
#include "AbstractDataTransform.h"
#include "ActuatorDeviceDriver.h"

/**
 * @brief Channel class that provides a "unit of redundancy"
 * 
 * This class is the container for sensor, transformations, and actuator instances.
 * It provides enable() and disable() services for fault management in dual channel systems.
 */
class Channel {
private:
    std::unique_ptr<SensorDeviceDriver> sensor;
    std::vector<std::shared_ptr<AbstractDataTransform>> transforms;
    std::shared_ptr<ActuatorDeviceDriver> actuator;
    bool enabled;
    bool initialized;
    std::string channelId;

public:
    /**
     * @brief Constructor
     * @param id Unique identifier for this channel
     */
    explicit Channel(const std::string& id);
    
    /**
     * @brief Destructor
     */
    ~Channel();

    /**
     * @brief Initialize the channel with sensor and actuator
     * @param sensorDriver Sensor device driver
     * @param actuatorDriver Actuator device driver
     * @return true if initialization successful, false otherwise
     */
    bool initialize(std::unique_ptr<SensorDeviceDriver> sensorDriver,
                   std::shared_ptr<ActuatorDeviceDriver> actuatorDriver);

    /**
     * @brief Add a data transformation to the processing chain
     * @param transform Data transformation to add
     */
    void addTransform(std::shared_ptr<AbstractDataTransform> transform);

    /**
     * @brief Enable the channel for processing
     */
    void enable();

    /**
     * @brief Disable the channel
     */
    void disable();

    /**
     * @brief Check if channel is enabled
     * @return true if enabled, false otherwise
     */
    bool isEnabled() const;

    /**
     * @brief Check if channel is initialized
     * @return true if initialized, false otherwise
     */
    bool isInitialized() const;

    /**
     * @brief Process data through the entire channel pipeline
     * @return true if processing successful, false otherwise
     */
    bool processChannel();

    /**
     * @brief Get the current sensor reading without processing
     * @return Raw sensor data, or NaN if sensor unavailable
     */
    double getCurrentSensorReading();

    /**
     * @brief Get channel identifier
     * @return Channel ID string
     */
    const std::string& getChannelId() const;

    /**
     * @brief Check if all components are operational
     * @return true if all components working, false otherwise
     */
    bool isOperational();

    /**
     * @brief Stop the channel and all its components
     */
    void stop();

private:
    /**
     * @brief Build the processing chain by linking transforms
     */
    void buildProcessingChain();
};

#endif // CHANNEL_H
