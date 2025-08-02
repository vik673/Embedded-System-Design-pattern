#include "EMGChannel.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

EMGChannel::EMGChannel() 
    : emgSensor(nullptr), frequencyConverter(nullptr), filter(nullptr),
      colorCalculator(nullptr), lightDriver(nullptr) {
    channel = std::make_unique<Channel>();
}

EMGChannel::~EMGChannel() {
    // Unique pointers and Channel will handle cleanup
}

void EMGChannel::initialize() {
    createComponents();
    setupProcessingChain();
    
    std::cout << "EMG Biofeedback Channel initialized successfully." << std::endl;
}

void EMGChannel::acquireData() {
    if (channel && channel->getInitializationStatus()) {
        channel->processChannel();
    }
}

double EMGChannel::getFrequency() {
    if (filter) {
        return filter->getFilteredFrequency();
    }
    return 0.0;
}

long EMGChannel::getLightColor() {
    if (lightDriver) {
        return lightDriver->getCurrentColor();
    }
    return 0;
}

int EMGChannel::getVoltage() {
    if (emgSensor) {
        return emgSensor->getVoltage();
    }
    return 0;
}

void EMGChannel::setSensitivity(int sensitivity) {
    if (emgSensor) {
        emgSensor->setSensitivity(sensitivity);
    }
}

void EMGChannel::setBrightness(double brightness) {
    if (lightDriver) {
        lightDriver->setBrightness(brightness);
    }
}

void EMGChannel::getCurrentRGB(int& red, int& green, int& blue) {
    if (lightDriver) {
        red = lightDriver->getCurrentRed();
        green = lightDriver->getCurrentGreen();
        blue = lightDriver->getCurrentBlue();
    } else {
        red = green = blue = 0;
    }
}

void EMGChannel::runBiofeedback(int iterations) {
    if (!isInitialized()) {
        std::cout << "Channel not initialized. Call initialize() first." << std::endl;
        return;
    }
    
    std::cout << "Starting EMG Biofeedback Processing..." << std::endl;
    std::cout << "Voltage -> Frequency -> Filtered Freq -> Color -> Light" << std::endl;
    std::cout << "========================================================" << std::endl;
    
    for (int i = 0; i < iterations; ++i) {
        // Process one cycle of data
        acquireData();
        
        // Display current state
        int red, green, blue;
        getCurrentRGB(red, green, blue);
        
        std::cout << "Cycle " << std::setw(3) << (i + 1) 
                  << " - Voltage: " << std::setw(3) << getVoltage()
                  << " mV, Frequency: " << std::setw(6) << std::fixed << std::setprecision(1) 
                  << getFrequency() << " Hz"
                  << ", RGB(" << std::setw(3) << red 
                  << "," << std::setw(3) << green 
                  << "," << std::setw(3) << blue << ")" << std::endl;
        
        // Small delay to simulate real-time processing
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "========================================================" << std::endl;
    std::cout << "Biofeedback processing completed." << std::endl;
}

bool EMGChannel::isInitialized() const {
    return channel && channel->getInitializationStatus();
}

void EMGChannel::createComponents() {
    // Create sensor
    auto sensor = std::make_unique<EMGSensorDeviceDriver>(1);
    emgSensor = sensor.get();
    
    // Create data transformations
    auto freqConverter = std::make_unique<ConvertToFrequency>(32, 1000.0);
    frequencyConverter = freqConverter.get();
    
    auto avgFilter = std::make_unique<MovingAverageFilter>(5);
    filter = avgFilter.get();
    
    auto colorCalc = std::make_unique<CalculateColor>(10.0, 300.0);
    colorCalculator = colorCalc.get();
    
    // Create actuator
    auto light = std::make_unique<LightDeviceDriver>(1);
    lightDriver = light.get();
    
    // Add transforms to channel
    channel->addTransform(std::move(freqConverter));
    channel->addTransform(std::move(avgFilter));
    channel->addTransform(std::move(colorCalc));
    
    // Initialize the channel
    channel->initialize(std::move(sensor), std::move(light));
}

void EMGChannel::setupProcessingChain() {
    // Set default configurations
    if (emgSensor) {
        emgSensor->setSensitivity(2);
        emgSensor->setAmplificationFactor(15);
        emgSensor->setNoiseThreshold(0.5);
    }
    
    if (frequencyConverter) {
        frequencyConverter->setSamplingRate(1000.0);
    }
    
    if (filter) {
        filter->setWindowSize(8);
    }
    
    if (colorCalculator) {
        colorCalculator->setFrequencyRange(20.0, 250.0);
    }
    
    if (lightDriver) {
        lightDriver->setBrightness(0.8);
    }
}
