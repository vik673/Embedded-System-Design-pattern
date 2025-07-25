#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "DualChannelPattern.h"
#include "Channel.h"
#include "OpticalWheelSpeedSensor.h"
#include "GPSSpeedSensor.h"
#include "EngineActuator.h"
#include "SpeedFilterTransform.h"
#include "SpeedToEngineOutputTransform.h"
#include "ReasonablenessChecker.h"

/**
 * @brief Demonstration of the Dual Channel Pattern implementation
 * 
 * This program demonstrates a heterogeneous dual channel train speed control system
 * as described in the embedded systems design pattern documentation.
 */

void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void faultSafeHandler() {
    std::cout << "\n*** FAULT-SAFE STATE ACTIVATED ***" << std::endl;
    std::cout << "*** ALL CHANNELS DISABLED - TRAIN EMERGENCY STOP ***" << std::endl;
}

int main() {
    printSeparator("DUAL CHANNEL PATTERN DEMONSTRATION");
    std::cout << "Train Speed Control System with Heterogeneous Redundancy" << std::endl;

    try {
        // Create shared actuator (engine)
        auto engine = std::make_shared<EngineActuator>(0.0, 1.0);

        // ===== OPTICAL WHEEL SPEED CHANNEL (Primary) =====
        printSeparator("Setting up Optical Wheel Speed Channel");
        
        auto opticalChannel = std::make_shared<Channel>("OpticalWheelSpeed");
        auto opticalSensor = std::make_unique<OpticalWheelSpeedSensor>(2.5); // 2.5m wheel circumference
        
        // Initialize optical channel
        if (!opticalChannel->initialize(std::move(opticalSensor), engine)) {
            std::cerr << "Failed to initialize optical channel" << std::endl;
            return 1;
        }

        // Add transforms for optical channel
        auto opticalFilter = std::make_shared<SpeedFilterTransform>(3, 0.0, 50.0);
        auto opticalController = std::make_shared<SpeedToEngineOutputTransform>(12.0, 0.08); // Target 12 m/s
        
        opticalChannel->addTransform(opticalFilter);
        opticalChannel->addTransform(opticalController);

        // Add reasonableness checker to controller
        auto opticalChecker = std::make_shared<ReasonablenessChecker>(0.3, 0.0, 1.0);
        opticalController->setChecker(opticalChecker);

        // ===== GPS SPEED CHANNEL (Secondary) =====
        printSeparator("Setting up GPS Speed Channel");
        
        auto gpsChannel = std::make_shared<Channel>("GPSSpeed");
        auto gpsSensor = std::make_unique<GPSSpeedSensor>();
        
        // Initialize GPS channel
        if (!gpsChannel->initialize(std::move(gpsSensor), engine)) {
            std::cerr << "Failed to initialize GPS channel" << std::endl;
            return 1;
        }

        // Add transforms for GPS channel (different design - heterogeneous)
        auto gpsFilter = std::make_shared<SpeedFilterTransform>(5, 0.0, 50.0); // Different filter window
        auto gpsController = std::make_shared<SpeedToEngineOutputTransform>(12.0, 0.1); // Different gain
        
        gpsChannel->addTransform(gpsFilter);
        gpsChannel->addTransform(gpsController);

        // Add reasonableness checker to GPS controller
        auto gpsChecker = std::make_shared<ReasonablenessChecker>(0.4, 0.0, 1.0); // Different limits
        gpsController->setChecker(gpsChecker);

        // Set up cross-channel references for checkers
        opticalChecker->setCurrentChannel(opticalChannel.get());
        opticalChecker->setAlternativeChannel(gpsChannel.get());
        gpsChecker->setCurrentChannel(gpsChannel.get());
        gpsChecker->setAlternativeChannel(opticalChannel.get());

        // ===== DUAL CHANNEL PATTERN SETUP =====
        printSeparator("Initializing Dual Channel Pattern");
        
        DualChannelPattern dualSystem(
            DualChannelPattern::RedundancyType::HETEROGENEOUS,
            DualChannelPattern::OperationMode::PRIMARY_BACKUP,
            0.2 // 0.2 m/s tolerance for output comparison
        );

        dualSystem.setFaultSafeCallback(faultSafeHandler);

        if (!dualSystem.initialize(opticalChannel, gpsChannel)) {
            std::cerr << "Failed to initialize dual channel system" << std::endl;
            return 1;
        }

        // ===== NORMAL OPERATION =====
        printSeparator("Starting Normal Operation");
        
        dualSystem.start();

        std::cout << "\nProcessing train speed control for 10 cycles..." << std::endl;
        
        for (int cycle = 1; cycle <= 10; ++cycle) {
            std::cout << "\n--- Cycle " << cycle << " ---" << std::endl;
            
            if (!dualSystem.process()) {
                std::cout << "Processing failed in cycle " << cycle << std::endl;
            }

            auto activeChannel = dualSystem.getActiveChannel();
            if (activeChannel) {
                std::cout << "Active Channel: " << activeChannel->getChannelId() << std::endl;
            }

            // Simulate some time passing
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // ===== FAULT SIMULATION =====
        printSeparator("Simulating Primary Channel Fault");
        
        std::cout << "Simulating optical sensor failure..." << std::endl;
        
        // Get the optical sensor and simulate failure
        // Note: In a real implementation, you might have a way to access and control sensors
        std::cout << "Primary channel will fail on next processing cycle..." << std::endl;
        
        // Continue processing to demonstrate fault handling
        for (int cycle = 11; cycle <= 15; ++cycle) {
            std::cout << "\n--- Cycle " << cycle << " (After Fault) ---" << std::endl;
            
            if (!dualSystem.process()) {
                std::cout << "Processing failed in cycle " << cycle << std::endl;
                break;
            }

            auto activeChannel = dualSystem.getActiveChannel();
            if (activeChannel) {
                std::cout << "Active Channel: " << activeChannel->getChannelId() << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // ===== SHUTDOWN =====
        printSeparator("System Shutdown");
        
        dualSystem.stop();
        std::cout << "Dual channel pattern demonstration completed successfully." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
