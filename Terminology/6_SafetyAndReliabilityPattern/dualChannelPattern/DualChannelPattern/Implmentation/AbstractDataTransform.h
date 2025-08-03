#ifndef ABSTRACT_DATA_TRANSFORM_H
#define ABSTRACT_DATA_TRANSFORM_H

#include <memory>

// Forward declarations
class ActuatorDeviceDriver;
class AbstractTransformChecker;

/**
 * @brief Abstract base class for data transformation operations
 * 
 * This class serves as a placeholder for one of several possible ConcreteDataTransforms.
 * It can be linked to the next transformation in the chain or to the output device driver.
 */
class AbstractDataTransform {
protected:
    std::shared_ptr<AbstractDataTransform> nextTransform;
    std::shared_ptr<ActuatorDeviceDriver> outputDriver;
    std::shared_ptr<AbstractTransformChecker> checker;

public:
    AbstractDataTransform() = default;
    virtual ~AbstractDataTransform() = default;

    /**
     * @brief Pure virtual function to process input data
     * @param input Input data to be transformed
     * @return Transformed output data
     */
    virtual double processData(double input) = 0;

    /**
     * @brief Set the next transformation in the chain
     * @param next Next transformation step
     */
    void setNextTransform(std::shared_ptr<AbstractDataTransform> next);

    /**
     * @brief Set the output device driver
     * @param driver Output device driver
     */
    void setOutputDriver(std::shared_ptr<ActuatorDeviceDriver> driver);

    /**
     * @brief Set the transformation checker
     * @param transformChecker Checker for this transformation
     */
    void setChecker(std::shared_ptr<AbstractTransformChecker> transformChecker);

    /**
     * @brief Execute the complete transformation chain
     * @param input Input data
     */
    void executeChain(double input);

    /**
     * @brief Check if this transform has a checker
     * @return true if checker is set, false otherwise
     */
    bool hasChecker() const;
};

#endif // ABSTRACT_DATA_TRANSFORM_H
