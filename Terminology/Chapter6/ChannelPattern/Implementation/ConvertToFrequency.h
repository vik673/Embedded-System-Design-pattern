#ifndef CONVERT_TO_FREQUENCY_H
#define CONVERT_TO_FREQUENCY_H

#include "AbstractDataTransform.h"
#include <vector>
#include <complex>

/**
 * @brief Converts EMG voltage signals to frequency domain
 * 
 * This transformation takes voltage samples and computes the fundamental
 * frequency using FFT analysis of the EMG signal.
 */
class ConvertToFrequency : public AbstractDataTransform {
private:
    std::vector<double> samples;
    double computedFreq;
    size_t sampleSize;
    double samplingRate;
    size_t currentSampleIndex;

public:
    ConvertToFrequency(size_t bufferSize = 64, double rate = 1000.0);
    virtual ~ConvertToFrequency();
    
    /**
     * @brief Process voltage data and convert to frequency
     * @param data Voltage data from EMG sensor
     * @return Computed fundamental frequency
     */
    virtual double processData(double data) override;
    
    /**
     * @brief Get the last computed frequency
     * @return Most recent frequency calculation
     */
    double getComputedFrequency() const;
    
    /**
     * @brief Set the sampling rate for frequency calculation
     * @param rate Sampling rate in Hz
     */
    void setSamplingRate(double rate);
    
    /**
     * @brief Get current sampling rate
     * @return Current sampling rate
     */
    double getSamplingRate() const;
    
    /**
     * @brief Reset the sample buffer
     */
    void resetSamples();

private:
    /**
     * @brief Compute fundamental frequency from sample buffer
     * @return Fundamental frequency in Hz
     */
    double computeFundamentalFrequency();
    
    /**
     * @brief Simple FFT implementation for frequency analysis
     * @param samples Input samples
     * @return FFT result
     */
    std::vector<std::complex<double>> simpleFFT(const std::vector<double>& samples);
    
    /**
     * @brief Find peak frequency from FFT result
     * @param fftResult FFT magnitude spectrum
     * @return Peak frequency
     */
    double findPeakFrequency(const std::vector<std::complex<double>>& fftResult);
};

#endif // CONVERT_TO_FREQUENCY_H
