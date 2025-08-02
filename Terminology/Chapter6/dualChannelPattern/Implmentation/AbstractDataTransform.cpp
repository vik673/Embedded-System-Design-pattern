#include "AbstractDataTransform.h"
#include "ActuatorDeviceDriver.h"
#include "AbstractTransformChecker.h"

void AbstractDataTransform::setNextTransform(std::shared_ptr<AbstractDataTransform> next) {
    nextTransform = next;
    outputDriver.reset(); // Clear output driver if next transform is set
}

void AbstractDataTransform::setOutputDriver(std::shared_ptr<ActuatorDeviceDriver> driver) {
    outputDriver = driver;
    nextTransform.reset(); // Clear next transform if output driver is set
}

void AbstractDataTransform::setChecker(std::shared_ptr<AbstractTransformChecker> transformChecker) {
    checker = transformChecker;
}

void AbstractDataTransform::executeChain(double input) {
    double output = processData(input);
    
    // If there's a checker, validate the transformation
    if (checker) {
        if (!checker->validateTransformation(input, output)) {
            // Validation failed, don't continue the chain
            return;
        }
    }
    
    // Continue the chain
    if (nextTransform) {
        nextTransform->executeChain(output);
    } else if (outputDriver) {
        outputDriver->actuate(output);
    }
}

bool AbstractDataTransform::hasChecker() const {
    return checker != nullptr;
}
