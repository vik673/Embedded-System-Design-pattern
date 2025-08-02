#include <iostream>
#include <iomanip>
#include "EMGChannel.h"
#include "Channel.h"

/**
 * @brief Demonstration of the Channel Pattern Implementation
 * 
 * This program demonstrates the Channel Pattern with an EMG biofeedback
 * system that processes muscle signals into visual color feedback.
 */

void printHeader() {
    std::cout << "===========================================================" << std::endl;
    std::cout << "           Channel Pattern Implementation Demo            " << std::endl;
    std::cout << "                EMG Biofeedback System                   " << std::endl;
    std::cout << "===========================================================" << std::endl;
    std::cout << std::endl;
}

void printChannelPatternInfo() {
    std::cout << "Channel Pattern Overview:" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "The Channel Pattern provides an architectural structure for" << std::endl;
    std::cout << "end-to-end data processing from raw acquisition through" << std::endl;
    std::cout << "transformations to physical actuation." << std::endl;
    std::cout << std::endl;
    
    std::cout << "EMG Biofeedback Processing Chain:" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "1. EMG Sensor → Acquire muscle voltage signals" << std::endl;
    std::cout << "2. Frequency Converter → Convert voltage to frequency domain" << std::endl;
    std::cout << "3. Moving Average Filter → Smooth frequency variations" << std::endl;
    std::cout << "4. Color Calculator → Map frequency to RGB values" << std::endl;
    std::cout << "5. Light Driver → Display color feedback" << std::endl;
    std::cout << std::endl;
}

void demonstrateBasicChannel() {
    std::cout << "=== Basic Channel Pattern Demonstration ===" << std::endl;
    
    EMGChannel emgChannel;
    
    // Initialize the channel
    emgChannel.initialize();
    
    if (!emgChannel.isInitialized()) {
        std::cout << "Failed to initialize EMG channel!" << std::endl;
        return;
    }
    
    std::cout << "Channel initialized successfully." << std::endl;
    std::cout << std::endl;
    
    // Configure channel parameters
    emgChannel.setSensitivity(3);
    emgChannel.setBrightness(0.9);
    
    std::cout << "Running biofeedback processing..." << std::endl;
    emgChannel.runBiofeedback(20);
    
    std::cout << std::endl;
}

void demonstrateChannelConfiguration() {
    std::cout << "=== Channel Configuration Demonstration ===" << std::endl;
    
    EMGChannel emgChannel;
    emgChannel.initialize();
    
    // Test different sensitivity settings
    std::cout << "Testing different sensitivity settings:" << std::endl;
    
    int sensitivities[] = {1, 3, 5};
    for (int sensitivity : sensitivities) {
        std::cout << "\nSensitivity Level: " << sensitivity << std::endl;
        std::cout << "-------------------" << std::endl;
        
        emgChannel.setSensitivity(sensitivity);
        emgChannel.runBiofeedback(5);
    }
    
    // Test different brightness levels
    std::cout << "\nTesting different brightness levels:" << std::endl;
    
    double brightnessLevels[] = {0.3, 0.6, 1.0};
    for (double brightness : brightnessLevels) {
        std::cout << "\nBrightness Level: " << brightness << std::endl;
        std::cout << "-------------------" << std::endl;
        
        emgChannel.setBrightness(brightness);
        emgChannel.runBiofeedback(3);
    }
    
    std::cout << std::endl;
}

void demonstrateRealTimeProcessing() {
    std::cout << "=== Real-Time Processing Demonstration ===" << std::endl;
    
    EMGChannel emgChannel;
    emgChannel.initialize();
    
    std::cout << "Simulating continuous biofeedback processing..." << std::endl;
    std::cout << "Watch how the colors change based on simulated muscle activity." << std::endl;
    std::cout << std::endl;
    
    // Run longer processing to show continuous operation
    emgChannel.runBiofeedback(50);
    
    std::cout << "Real-time processing demonstration completed." << std::endl;
    std::cout << std::endl;
}

void printChannelBenefits() {
    std::cout << "Channel Pattern Benefits Demonstrated:" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "✓ Modular Design: Each component has a single responsibility" << std::endl;
    std::cout << "✓ Configurability: Parameters can be adjusted independently" << std::endl;
    std::cout << "✓ Testability: Each transform can be tested in isolation" << std::endl;
    std::cout << "✓ Reusability: Components can be reused in different channels" << std::endl;
    std::cout << "✓ Maintainability: Changes to one component don't affect others" << std::endl;
    std::cout << "✓ Fault Isolation: Problems in one stage don't cascade" << std::endl;
    std::cout << std::endl;
}

int main() {
    try {
        printHeader();
        printChannelPatternInfo();
        
        // Demonstrate basic channel functionality
        demonstrateBasicChannel();
        
        // Demonstrate channel configuration
        demonstrateChannelConfiguration();
        
        // Demonstrate real-time processing
        demonstrateRealTimeProcessing();
        
        // Print benefits
        printChannelBenefits();
        
        std::cout << "===========================================================" << std::endl;
        std::cout << "           Channel Pattern Demo Completed Successfully     " << std::endl;
        std::cout << "===========================================================" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
