#ifndef CALCULATE_COLOR_H
#define CALCULATE_COLOR_H

#include "AbstractDataTransform.h"

/**
 * @brief Converts frequency values to RGB color values
 * 
 * This transformation maps filtered frequency data to pleasing
 * RGB color values for visual biofeedback display.
 */
class CalculateColor : public AbstractDataTransform {
private:
    int red;
    int green;
    int blue;
    double minFrequency;
    double maxFrequency;

public:
    CalculateColor(double minFreq = 10.0, double maxFreq = 500.0);
    virtual ~CalculateColor();
    
    /**
     * @brief Process frequency data and convert to RGB color
     * @param data Input frequency value
     * @return RGB color value (packed as double)
     */
    virtual double processData(double data) override;
    
    /**
     * @brief Get the current red component
     * @return Red color component (0-255)
     */
    int getRed() const;
    
    /**
     * @brief Get the current green component
     * @return Green color component (0-255)
     */
    int getGreen() const;
    
    /**
     * @brief Get the current blue component
     * @return Blue color component (0-255)
     */
    int getBlue() const;
    
    /**
     * @brief Get packed RGB value
     * @return RGB color as packed long value
     */
    long getRGBValue() const;
    
    /**
     * @brief Set the frequency range for color mapping
     * @param minFreq Minimum frequency for mapping
     * @param maxFreq Maximum frequency for mapping
     */
    void setFrequencyRange(double minFreq, double maxFreq);
    
    /**
     * @brief Get the current frequency range
     * @param minFreq Reference to store minimum frequency
     * @param maxFreq Reference to store maximum frequency
     */
    void getFrequencyRange(double& minFreq, double& maxFreq) const;

private:
    /**
     * @brief Map frequency to color using HSV color space
     * @param frequency Input frequency
     */
    void frequencyToColor(double frequency);
    
    /**
     * @brief Convert HSV to RGB color space
     * @param h Hue (0-360)
     * @param s Saturation (0-1)
     * @param v Value/Brightness (0-1)
     */
    void hsvToRgb(double h, double s, double v);
    
    /**
     * @brief Clamp value to 0-255 range
     * @param value Input value
     * @return Clamped value
     */
    int clampColorValue(double value);
};

#endif // CALCULATE_COLOR_H
