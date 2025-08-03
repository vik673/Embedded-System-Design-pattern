#ifndef DUAL_CHANNEL_PATTERN_H
#define DUAL_CHANNEL_PATTERN_H

#include <memory>
#include <functional>
#include "Channel.h"

/**
 * @brief Dual Channel Pattern implementation for fault-tolerant systems
 * 
 * This class manages two channels to provide redundancy and fault tolerance.
 * It can operate in different modes:
 * - Homogeneous: Both channels use identical designs
 * - Heterogeneous: Channels use different designs for diverse redundancy
 */
class DualChannelPattern {
public:
    enum class RedundancyType {
        HOMOGENEOUS,    // Identical channels
        HETEROGENEOUS   // Different channel designs
    };

    enum class OperationMode {
        SIMULTANEOUS,   // Both channels run simultaneously with comparison
        PRIMARY_BACKUP  // One channel runs until fault, then switch to backup
    };

private:
    std::shared_ptr<Channel> primaryChannel;
    std::shared_ptr<Channel> secondaryChannel;
    RedundancyType redundancyType;
    OperationMode operationMode;
    bool faultDetected;
    double tolerance;  // Tolerance for output comparison in simultaneous mode
    
    // Callback for fault-safe state
    std::function<void()> faultSafeCallback;

public:
    /**
     * @brief Constructor
     * @param type Type of redundancy (homogeneous or heterogeneous)
     * @param mode Operation mode (simultaneous or primary-backup)
     * @param outputTolerance Tolerance for output comparison (for simultaneous mode)
     */
    DualChannelPattern(RedundancyType type, OperationMode mode, double outputTolerance = 0.1);

    /**
     * @brief Destructor
     */
    ~DualChannelPattern();

    /**
     * @brief Initialize the dual channel system
     * @param primary Primary channel
     * @param secondary Secondary channel
     * @return true if initialization successful, false otherwise
     */
    bool initialize(std::shared_ptr<Channel> primary, std::shared_ptr<Channel> secondary);

    /**
     * @brief Start the dual channel system
     */
    void start();

    /**
     * @brief Stop the dual channel system
     */
    void stop();

    /**
     * @brief Process data through the dual channel system
     * @return true if processing successful, false otherwise
     */
    bool process();

    /**
     * @brief Check if system is operational
     * @return true if at least one channel is operational, false otherwise
     */
    bool isOperational();

    /**
     * @brief Set callback function for fault-safe state
     * @param callback Function to call when entering fault-safe state
     */
    void setFaultSafeCallback(std::function<void()> callback);

    /**
     * @brief Get the currently active channel
     * @return Pointer to active channel, nullptr if none active
     */
    std::shared_ptr<Channel> getActiveChannel();

    /**
     * @brief Get redundancy type
     * @return Current redundancy type
     */
    RedundancyType getRedundancyType() const;

    /**
     * @brief Get operation mode
     * @return Current operation mode
     */
    OperationMode getOperationMode() const;

    /**
     * @brief Check if fault has been detected
     * @return true if fault detected, false otherwise
     */
    bool isFaultDetected() const;

private:
    /**
     * @brief Process in simultaneous mode - both channels run and outputs are compared
     * @return true if processing successful, false otherwise
     */
    bool processSimultaneous();

    /**
     * @brief Process in primary-backup mode - one channel at a time
     * @return true if processing successful, false otherwise
     */
    bool processPrimaryBackup();

    /**
     * @brief Compare outputs from both channels
     * @param output1 Output from first channel
     * @param output2 Output from second channel
     * @return true if outputs are within tolerance, false otherwise
     */
    bool compareOutputs(double output1, double output2);

    /**
     * @brief Handle fault detection and switch channels if needed
     */
    void handleFault();

    /**
     * @brief Enter fault-safe state
     */
    void enterFaultSafeState();

    /**
     * @brief Switch from primary to secondary channel
     */
    void switchToSecondary();
};

#endif // DUAL_CHANNEL_PATTERN_H
