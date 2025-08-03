#include "ConvertToFrequency.h"
#include <algorithm>
#include <cmath>
#include <numeric>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

ConvertToFrequency::ConvertToFrequency(size_t bufferSize, double rate) 
    : AbstractDataTransform(), sampleSize(bufferSize), samplingRate(rate), 
      currentSampleIndex(0), computedFreq(0.0) {
    samples.resize(sampleSize, 0.0);
}

ConvertToFrequency::~ConvertToFrequency() {
    // Cleanup if needed
}

double ConvertToFrequency::processData(double data) {
    // Add new sample to circular buffer
    samples[currentSampleIndex] = data;
    currentSampleIndex = (currentSampleIndex + 1) % sampleSize;
    
    // Compute frequency when buffer is full
    static size_t processCount = 0;
    processCount++;
    
    if (processCount >= sampleSize) {
        computedFreq = computeFundamentalFrequency();
        
        // Forward the frequency to next stage
        forwardData(computedFreq);
        
        processCount = 0; // Reset for next batch
    }
    
    return computedFreq;
}

double ConvertToFrequency::getComputedFrequency() const {
    return computedFreq;
}

void ConvertToFrequency::setSamplingRate(double rate) {
    samplingRate = rate;
}

double ConvertToFrequency::getSamplingRate() const {
    return samplingRate;
}

void ConvertToFrequency::resetSamples() {
    std::fill(samples.begin(), samples.end(), 0.0);
    currentSampleIndex = 0;
    computedFreq = 0.0;
}

double ConvertToFrequency::computeFundamentalFrequency() {
    // Create a properly ordered sample array for FFT
    std::vector<double> orderedSamples(sampleSize);
    for (size_t i = 0; i < sampleSize; ++i) {
        orderedSamples[i] = samples[(currentSampleIndex + i) % sampleSize];
    }
    
    // Apply window function (Hamming window)
    for (size_t i = 0; i < sampleSize; ++i) {
        double window = 0.54 - 0.46 * std::cos(2.0 * M_PI * i / (sampleSize - 1));
        orderedSamples[i] *= window;
    }
    
    // Perform FFT
    auto fftResult = simpleFFT(orderedSamples);
    
    // Find peak frequency
    return findPeakFrequency(fftResult);
}

std::vector<std::complex<double>> ConvertToFrequency::simpleFFT(const std::vector<double>& samples) {
    size_t N = samples.size();
    std::vector<std::complex<double>> result(N);
    
    // Simple DFT implementation (not optimized FFT)
    for (size_t k = 0; k < N; ++k) {
        std::complex<double> sum(0, 0);
        for (size_t n = 0; n < N; ++n) {
            double angle = -2.0 * M_PI * k * n / N;
            sum += samples[n] * std::complex<double>(std::cos(angle), std::sin(angle));
        }
        result[k] = sum;
    }
    
    return result;
}

double ConvertToFrequency::findPeakFrequency(const std::vector<std::complex<double>>& fftResult) {
    // Only analyze the first half of the spectrum (due to symmetry)
    size_t halfSize = fftResult.size() / 2;
    
    // Find the bin with maximum magnitude (excluding DC component)
    size_t maxBin = 1;
    double maxMagnitude = std::abs(fftResult[1]);
    
    for (size_t i = 2; i < halfSize; ++i) {
        double magnitude = std::abs(fftResult[i]);
        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
            maxBin = i;
        }
    }
    
    // Convert bin number to frequency
    double frequency = (maxBin * samplingRate) / fftResult.size();
    
    // Ensure reasonable frequency range for EMG (typically 10-500 Hz)
    if (frequency < 10.0) frequency = 10.0;
    if (frequency > 500.0) frequency = 500.0;
    
    return frequency;
}
