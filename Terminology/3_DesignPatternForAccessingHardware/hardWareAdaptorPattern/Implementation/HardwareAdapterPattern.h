#ifndef HARDWARE_ADAPTER_PATTERN_H
#define HARDWARE_ADAPTER_PATTERN_H

#include <iostream>
#include <string>
#include <memory>

/**
 * Hardware Adapter Pattern Implementation
 * 
 * This pattern provides a way of adapting an existing hardware interface 
 * into the expectations of the application. It creates an element that 
 * converts between two incompatible interfaces.
 * 
 * Key Components:
 * - HardwareInterfaceToClient: Interface expected by the client
 * - HardwareAdapter: Converts between client interface and hardware proxy
 * - HardwareProxy: Software representation of hardware
 * - HardwareDevice: Actual hardware with specific interface
 * - AdapterClient: Uses hardware through expected interface
 */

// Forward declarations
class HardwareDevice;
class HardwareProxy;

/**
 * Hardware Interface to Client
 * This represents the interface that the client expects the hardware to provide
 */
class HardwareInterfaceToClient {
public:
    virtual ~HardwareInterfaceToClient() = default;
    virtual void startOperation() = 0;
    virtual void stopOperation() = 0;
    virtual int getStatus() = 0;
    virtual void configure(const std::string& config) = 0;
};

/**
 * Hardware Device
 * Represents the actual hardware device with its specific interface
 */
class HardwareDevice {
private:
    bool isActive;
    int deviceStatus;
    std::string deviceConfig;

public:
    HardwareDevice();
    
    // Hardware-specific interface (different from what client expects)
    void powerOn();
    void powerOff();
    int readDeviceState();
    void setDeviceParameters(const std::string& params);
    bool isDeviceActive() const;
    std::string getDeviceConfig() const;
};

/**
 * Hardware Proxy
 * Provides a software representation of the hardware device
 */
class HardwareProxy {
private:
    std::unique_ptr<HardwareDevice> device;

public:
    HardwareProxy();
    void activateDevice();
    void deactivateDevice();
    int queryDeviceStatus();
    void configureDevice(const std::string& parameters);
    bool isOperational();
};

/**
 * Hardware Adapter
 * Performs "impedance matching" between the client interface and hardware proxy
 */
class HardwareAdapter : public HardwareInterfaceToClient {
private:
    std::unique_ptr<HardwareProxy> hardwareProxy;

public:
    HardwareAdapter();
    
    // Implement the client-expected interface
    void startOperation() override;
    void stopOperation() override;
    int getStatus() override;
    void configure(const std::string& config) override;
};

/**
 * Adapter Client
 * Uses the hardware through the expected interface
 */
class AdapterClient {
private:
    std::shared_ptr<HardwareInterfaceToClient> hardwareInterface;

public:
    AdapterClient(std::shared_ptr<HardwareInterfaceToClient> interface);
    void performOperation();
};

/**
 * Alternative Hardware Implementation
 * Shows how different hardware can be used with same client
 */
class AlternativeHardwareAdapter : public HardwareInterfaceToClient {
private:
    bool isRunning;
    int currentStatus;

public:
    AlternativeHardwareAdapter();
    void startOperation() override;
    void stopOperation() override;
    int getStatus() override;
    void configure(const std::string& config) override;
};

// Demonstration function
void demonstrateHardwareAdapterPattern();

#endif // HARDWARE_ADAPTER_PATTERN_H
