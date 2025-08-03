#ifndef LIGHT_DEVICE_DRIVER_H
#define LIGHT_DEVICE_DRIVER_H

#include "ActuatorDeviceDriver.h"

/**
 * @brief Light Device Driver for controlling RGB lighting
 * 
 * This driver controls RGB lighting hardware based on color values
 * computed from the EMG biofeedback processing chain.
 */
class LightDeviceDriver : public ActuatorDeviceDriver {
private:
    int currentRed;
    int currentGreen;
    int currentBlue;
    long currentColor;
    double brightness;

public:
    LightDeviceDriver(int id = 0);
    virtual ~LightDeviceDriver();
    
    /**
     * @brief Actuate the light with the given color value
     * @param value Packed RGB color value
     */
    virtual void actuate(double value) override;
    
    /**
     * @brief Set light color using individual RGB components
     * @param red Red component (0-255)
     * @param green Green component (0-255)
     * @param blue Blue component (0-255)
     */
    void setLightColor(int red, int green, int blue);
    
    /**
     * @brief Get the current color as packed RGB value
     * @return Current RGB color
     */
    long getCurrentColor() const;
    
    /**
     * @brief Get current red component
     * @return Red component (0-255)
     */
    int getCurrentRed() const;
    
    /**
     * @brief Get current green component
     * @return Green component (0-255)
     */
    int getCurrentGreen() const;
    
    /**
     * @brief Get current blue component
     * @return Blue component (0-255)
     */
    int getCurrentBlue() const;
    
    /**
     * @brief Set the brightness level
     * @param level Brightness level (0.0-1.0)
     */
    void setBrightness(double level);
    
    /**
     * @brief Get current brightness level
     * @return Current brightness (0.0-1.0)
     */
    double getBrightness() const;

protected:
    /**
     * @brief Control the physical light hardware
     * @param value RGB color value to display
     */
    virtual void controlPhysicalDevice(double value) override;
    
    /**
     * @brief Validate RGB color value
     * @param value Color value to validate
     * @return True if valid, false otherwise
     */
    virtual bool validateValue(double value) override;
    
    /**
     * @brief Unpack RGB components from packed color value
     * @param packedColor Packed RGB color
     * @param red Reference to store red component
     * @param green Reference to store green component
     * @param blue Reference to store blue component
     */
    void unpackRGB(long packedColor, int& red, int& green, int& blue);
    
    /**
     * @brief Apply brightness adjustment to color components
     * @param red Red component
     * @param green Green component
     * @param blue Blue component
     */
    void applyBrightness(int& red, int& green, int& blue);
    
    /**
     * @brief Simulate light hardware control
     * @param red Red component
     * @param green Green component
     * @param blue Blue component
     */
    void simulateLightControl(int red, int green, int blue);
};

#endif // LIGHT_DEVICE_DRIVER_H
