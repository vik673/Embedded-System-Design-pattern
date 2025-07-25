#ifndef TOKENIZER_TYPES_H
#define TOKENIZER_TYPES_H

/**
 * @file TokenizerTypes.h
 * @brief Basic types and enumerations for the Multiple Receptor Pattern implementation
 * 
 * This file defines the state enumerations and utility functions used by the
 * TokenizerMultiReceptor state machine implementation.
 */

/**
 * @brief High-level states for the tokenizer state machine
 */
typedef enum TSTATETYPE {
    NULL_STATE,                 /**< Initial/invalid state */
    NONUMBER_STATE,            /**< No number being processed */
    GOTNUMBER_STATE            /**< Currently processing a number */
} TSTATETYPE;

/**
 * @brief Sub-states for when processing numbers
 */
typedef enum TSUBSTATETYPE {
    NULL_SSTATE,                        /**< No sub-state */
    PROCESSINGWHOLEPART_SSTATE,         /**< Processing whole part of number */
    PROCESSINGFRACTIONALPART_SSTATE     /**< Processing fractional part of number */
} TSUBSTATETYPE;

/**
 * @brief Convert character digit to integer value
 * @param c Character representing a digit ('0'-'9')
 * @return Integer value of the digit (0-9)
 */
int digit(char c);

#endif /* TOKENIZER_TYPES_H */
