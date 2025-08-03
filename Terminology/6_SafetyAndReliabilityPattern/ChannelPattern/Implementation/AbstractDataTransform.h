#ifndef ABSTRACT_DATA_TRANSFORM_H
#define ABSTRACT_DATA_TRANSFORM_H

/**
 * @brief Abstract base class for data transformations in the Channel Pattern
 * 
 * This class defines the interface for data transformation steps that can be
 * chained together to process data from sensors to actuators.
 */
class AbstractDataTransform {
protected:
    AbstractDataTransform* nextTransform;
    class ActuatorDeviceDriver* actuatorDriver;

public:
    AbstractDataTransform();
    virtual ~AbstractDataTransform();
    
    /**
     * @brief Process the input data and either pass to next transform or actuator
     * @param data Input data to be processed
     * @return Processed data
     */
    virtual double processData(double data) = 0;
    
    /**
     * @brief Set the next transformation in the processing chain
     * @param next Pointer to the next data transformation
     */
    void setNextTransform(AbstractDataTransform* next);
    
    /**
     * @brief Set the actuator device driver for final output
     * @param driver Pointer to the actuator device driver
     */
    void setActuatorDriver(class ActuatorDeviceDriver* driver);
    
    /**
     * @brief Get the next transform in the chain
     * @return Pointer to next transform or nullptr
     */
    AbstractDataTransform* getNextTransform() const;
    
    /**
     * @brief Get the actuator driver
     * @return Pointer to actuator driver or nullptr
     */
    class ActuatorDeviceDriver* getActuatorDriver() const;

protected:
    /**
     * @brief Forward processed data to the next step in the chain
     * @param processedData Data to forward
     */
    void forwardData(double processedData);
};

#endif // ABSTRACT_DATA_TRANSFORM_H
