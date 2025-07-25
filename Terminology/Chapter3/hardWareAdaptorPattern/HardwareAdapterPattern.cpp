#include "HardwareAdapterPattern.h"

// HardwareDevice Implementation
HardwareDevice::HardwareDevice() : isActive(false), deviceStatus(0), deviceConfig("") {}

void HardwareDevice::powerOn() {
    isActive = true;
    deviceStatus = 1;
    std::cout << "Hardware Device: Power ON\n";
}

void HardwareDevice::powerOff() {
    isActive = false;
    deviceStatus = 0;
    std::cout << "Hardware Device: Power OFF\n";
}

int HardwareDevice::readDeviceState() {
    return deviceStatus;
}

void HardwareDevice::setDeviceParameters(const std::string& params) {
    deviceConfig = params;
    std::cout << "Hardware Device: Parameters set to " << params << "\n";
}

bool HardwareDevice::isDeviceActive() const {
    return isActive;
}

std::string HardwareDevice::getDeviceConfig() const {
    return deviceConfig;
}

// HardwareProxy Implementation
HardwareProxy::HardwareProxy() : device(std::make_unique<HardwareDevice>()) {}

void HardwareProxy::activateDevice() {
    device->powerOn();
}

void HardwareProxy::deactivateDevice() {
    device->powerOff();
}

int HardwareProxy::queryDeviceStatus() {
    return device->readDeviceState();
}

void HardwareProxy::configureDevice(const std::string& parameters) {
    device->setDeviceParameters(parameters);
}

bool HardwareProxy::isOperational() {
    return device->isDeviceActive();
}

// HardwareAdapter Implementation
HardwareAdapter::HardwareAdapter() : hardwareProxy(std::make_unique<HardwareProxy>()) {}

void HardwareAdapter::startOperation() {
    std::cout << "Hardware Adapter: Converting startOperation() to hardware proxy calls\n";
    hardwareProxy->activateDevice();
}

void HardwareAdapter::stopOperation() {
    std::cout << "Hardware Adapter: Converting stopOperation() to hardware proxy calls\n";
    hardwareProxy->deactivateDevice();
}

int HardwareAdapter::getStatus() {
    std::cout << "Hardware Adapter: Converting getStatus() to hardware proxy calls\n";
    return hardwareProxy->queryDeviceStatus();
}

void HardwareAdapter::configure(const std::string& config) {
    std::cout << "Hardware Adapter: Converting configure() to hardware proxy calls\n";
    // Adapter may need to transform the configuration format
    std::string adaptedConfig = "ADAPTED_" + config;
    hardwareProxy->configureDevice(adaptedConfig);
}

// AdapterClient Implementation
AdapterClient::AdapterClient(std::shared_ptr<HardwareInterfaceToClient> interface) 
    : hardwareInterface(interface) {}

void AdapterClient::performOperation() {
    std::cout << "\n=== Adapter Client: Starting operation sequence ===\n";
    
    // Configure the hardware
    hardwareInterface->configure("PERFORMANCE_MODE");
    
    // Start the operation
    hardwareInterface->startOperation();
    
    // Check status
    int status = hardwareInterface->getStatus();
    std::cout << "Adapter Client: Current status = " << status << "\n";
    
    // Stop the operation
    hardwareInterface->stopOperation();
    
    // Check final status
    status = hardwareInterface->getStatus();
    std::cout << "Adapter Client: Final status = " << status << "\n";
    
    std::cout << "=== Adapter Client: Operation sequence completed ===\n\n";
}

// AlternativeHardwareAdapter Implementation
AlternativeHardwareAdapter::AlternativeHardwareAdapter() : isRunning(false), currentStatus(0) {}

void AlternativeHardwareAdapter::startOperation() {
    std::cout << "Alternative Hardware Adapter: Starting with different implementation\n";
    isRunning = true;
    currentStatus = 100;  // Different status values
}

void AlternativeHardwareAdapter::stopOperation() {
    std::cout << "Alternative Hardware Adapter: Stopping with different implementation\n";
    isRunning = false;
    currentStatus = 0;
}

int AlternativeHardwareAdapter::getStatus() {
    std::cout << "Alternative Hardware Adapter: Returning alternative status format\n";
    return currentStatus;
}

void AlternativeHardwareAdapter::configure(const std::string& config) {
    std::cout << "Alternative Hardware Adapter: Processing config differently: " << config << "\n";
    // Different configuration processing
}

// Demonstration function
void demonstrateHardwareAdapterPattern() {
    std::cout << "=== Hardware Adapter Pattern Demonstration ===\n\n";

    // Create adapter with original hardware
    std::cout << "1. Using Original Hardware Implementation:\n";
    auto originalAdapter = std::make_shared<HardwareAdapter>();
    AdapterClient client1(originalAdapter);
    client1.performOperation();

    // Create adapter with alternative hardware
    std::cout << "2. Using Alternative Hardware Implementation:\n";
    auto alternativeAdapter = std::make_shared<AlternativeHardwareAdapter>();
    AdapterClient client2(alternativeAdapter);
    client2.performOperation();

    std::cout << "=== Pattern Benefits Demonstrated ===\n";
    std::cout << "- Same client code works with different hardware implementations\n";
    std::cout << "- Hardware-specific interfaces are hidden from the client\n";
    std::cout << "- Easy to replace hardware without changing client code\n";
    std::cout << "- Adapter handles interface conversion and data transformation\n";
}

int main() {
    demonstrateHardwareAdapterPattern();
    return 0;
}
