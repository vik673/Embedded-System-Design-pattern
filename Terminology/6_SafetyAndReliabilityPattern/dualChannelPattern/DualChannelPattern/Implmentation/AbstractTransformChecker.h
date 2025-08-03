#ifndef ABSTRACT_TRANSFORM_CHECKER_H
#define ABSTRACT_TRANSFORM_CHECKER_H

// Forward declarations
class Channel;

/**
 * @brief Abstract base class for transformation validation
 * 
 * This class provides the interface for checking the validity of data processing
 * or transformations at specific points in the processing chain.
 */
class AbstractTransformChecker {
protected:
    Channel* itsChannel;        // Current channel that owns this checker
    Channel* itsOtherChannel;   // Alternative channel for dual channel pattern

public:
    AbstractTransformChecker() : itsChannel(nullptr), itsOtherChannel(nullptr) {}
    virtual ~AbstractTransformChecker() = default;

    /**
     * @brief Pure virtual function to validate a transformation
     * @param input Input value to the transformation
     * @param output Output value from the transformation
     * @return true if transformation is valid, false otherwise
     */
    virtual bool validateTransformation(double input, double output) = 0;

    /**
     * @brief Set the current channel
     * @param channel Current channel
     */
    void setCurrentChannel(Channel* channel);

    /**
     * @brief Set the alternative channel
     * @param channel Alternative channel
     */
    void setAlternativeChannel(Channel* channel);

    /**
     * @brief Switch from current channel to alternative channel
     * Called when current channel fails validation
     */
    virtual void switchToAlternativeChannel();

protected:
    /**
     * @brief Get the current channel
     * @return Pointer to current channel
     */
    Channel* getCurrentChannel() const;

    /**
     * @brief Get the alternative channel
     * @return Pointer to alternative channel
     */
    Channel* getAlternativeChannel() const;
};

#endif // ABSTRACT_TRANSFORM_CHECKER_H
