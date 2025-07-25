#ifndef EMG_CHANNEL_H
#define EMG_CHANNEL_H

#include "Channel.h"
#include "EMGSensorDeviceDriver.h"
#include "ConvertToFrequency.h"
#include "MovingAverageFilter.h"
#include "CalculateColor.h"
#include "LightDeviceDriver.h"

/**
 * @brief EMG Biofeedback Channel Implementation
 * 
 * This class demonstrates the Channel Pattern with a specific EMG biofeedback
 * implementation that processes muscle signals into visual color feedback.
 */
class EMGChannel {
private:
    std::unique_ptr<Channel> channel;
    EMGSensorDeviceDriver* emgSensor;
    ConvertToFrequency* frequencyConverter;
    MovingAverageFilter* filter;
    CalculateColor* colorCalculator;
    LightDeviceDriver* lightDriver;

public:
    EMGChannel();
    ~EMGChannel();
    
    /**
     * @brief Initialize the EMG channel with all components
     */
    void initialize();
    
    /**
     * @brief Start data acquisition and processing
     */
    void acquireData();
    
    /**
     * @brief Get the current frequency reading
     * @return Current filtered frequency
     */
    double getFrequency();
    
    /**
     * @brief Get the current light color
     * @return Current RGB color value
     */
    long getLightColor();
    
    /**
     * @brief Get the current voltage reading
     * @return Current EMG voltage
     */
    int getVoltage();
    
    /**
     * @brief Set the sensor sensitivity
     * @param sensitivity Sensitivity value
     */
    void setSensitivity(int sensitivity);
    
    /**
     * @brief Set the brightness of the light output
     * @param brightness Brightness level (0.0-1.0)
     */
    void setBrightness(double brightness);
    
    /**
     * @brief Get individual color components
     * @param red Reference to store red component
     * @param green Reference to store green component
     * @param blue Reference to store blue component
     */
    void getCurrentRGB(int& red, int& green, int& blue);
    
    /**
     * @brief Run continuous biofeedback processing
     * @param iterations Number of processing cycles to run
     */
    void runBiofeedback(int iterations = 100);
    
    /**
     * @brief Check if the channel is properly initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const;

private:
    /**
     * @brief Create and configure all channel components
     */
    void createComponents();
    
    /**
     * @brief Set up the processing chain relationships
     */
    void setupProcessingChain();
};

#endif // EMG_CHANNEL_H
