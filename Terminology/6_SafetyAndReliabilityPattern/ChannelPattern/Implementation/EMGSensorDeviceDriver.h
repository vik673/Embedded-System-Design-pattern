#ifndef EMG_SENSOR_DEVICE_DRIVER_H
#define EMG_SENSOR_DEVICE_DRIVER_H

#include "SensorDeviceDriver.h"

/**
 * @brief EMG Sensor Device Driver for measuring muscle voltage
 * 
 * This driver reads electromyography (EMG) signals from electrodes
 * placed on muscle tissue to measure muscle activity.
 */
class EMGSensorDeviceDriver : public SensorDeviceDriver {
private:
    int voltage;
    int amplificationFactor;
    double noiseThreshold;

public:
    EMGSensorDeviceDriver(int id = 0);
    virtual ~EMGSensorDeviceDriver();
    
    /**
     * @brief Acquire voltage data from EMG electrodes
     * @return EMG voltage reading
     */
    virtual double acquireData() override;
    
    /**
     * @brief Get the current voltage reading
     * @return Current voltage value
     */
    int getVoltage() const;
    
    /**
     * @brief Set the amplification factor for the EMG signal
     * @param factor Amplification factor
     */
    void setAmplificationFactor(int factor);
    
    /**
     * @brief Set noise threshold for filtering
     * @param threshold Noise threshold value
     */
    void setNoiseThreshold(double threshold);

protected:
    /**
     * @brief Read raw voltage from EMG electrodes
     * @return Raw EMG voltage reading
     */
    virtual double readPhysicalSensor() override;
    
    /**
     * @brief Apply noise filtering to the raw signal
     * @param rawVoltage Raw voltage reading
     * @return Filtered voltage
     */
    double filterNoise(double rawVoltage);
    
    /**
     * @brief Simulate EMG sensor hardware reading
     * @return Simulated EMG voltage
     */
    int simulateEMGReading();
};

#endif // EMG_SENSOR_DEVICE_DRIVER_H
