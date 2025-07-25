#ifndef AttitudeDataType_H
#define AttitudeDataType_H

/**
 * AttitudeDataType - Represents aircraft attitude data
 * Contains roll, pitch, and yaw orientation values
 * Used in the One's Complement Pattern for critical data protection
 */
typedef struct AttitudeDataType AttitudeDataType;
struct AttitudeDataType {
    int roll;   // Roll angle in degrees
    int pitch;  // Pitch angle in degrees  
    int yaw;    // Yaw angle in degrees
};

/**
 * Initialize an AttitudeDataType structure
 * @param me Pointer to the AttitudeDataType to initialize
 */
void AttitudeDataType_Init(AttitudeDataType* const me);

/**
 * Set all attitude values
 * @param me Pointer to the AttitudeDataType
 * @param roll Roll angle
 * @param pitch Pitch angle
 * @param yaw Yaw angle
 */
void AttitudeDataType_Set(AttitudeDataType* const me, int roll, int pitch, int yaw);

/**
 * Copy one AttitudeDataType to another
 * @param dest Destination AttitudeDataType
 * @param src Source AttitudeDataType
 */
void AttitudeDataType_Copy(AttitudeDataType* const dest, const AttitudeDataType* const src);

/**
 * Compare two AttitudeDataType structures for equality
 * @param a First AttitudeDataType
 * @param b Second AttitudeDataType
 * @return 1 if equal, 0 if not equal
 */
int AttitudeDataType_IsEqual(const AttitudeDataType* const a, const AttitudeDataType* const b);

#endif /* AttitudeDataType_H */
