#ifndef TOKENIZER_MULTI_RECEPTOR_H
#define TOKENIZER_MULTI_RECEPTOR_H

#include "TokenizerTypes.h"
#include "Mutex.h"

/**
 * @file TokenizerMultiReceptor.h
 * @brief Multiple Event Receptor Pattern implementation for a number tokenizer
 * 
 * This file implements the Multiple Event Receptor Pattern (MERSM) for a
 * synchronous finite state machine that parses numbers from character input.
 * Each event has its own receptor function, making the implementation simple
 * and robust.
 */

/**
 * @brief Forward declaration of the TokenizerMultiReceptor structure
 */
typedef struct TokenizerMultiReceptor TokenizerMultiReceptor;

/**
 * @brief TokenizerMultiReceptor structure definition
 * 
 * This structure contains both the business logic attributes (result, ch, tensPlace)
 * and the state management attributes (stateID, subStateID, itsMutex).
 */
struct TokenizerMultiReceptor {
    /* Business logic attributes */
    char ch;                    /**< Current character being processed */
    double result;              /**< Current value of the number being parsed */
    double tensPlace;           /**< Used for computing fractional parts */
    
    /* State management attributes */
    TSTATETYPE stateID;         /**< Current high-level state */
    TSUBSTATETYPE subStateID;   /**< Current sub-state */
    Mutex* itsMutex;           /**< Mutex for thread-safe operations */
};

/* ============================================================================
 * Constructors and Destructors
 * ============================================================================ */

/**
 * @brief Create a new TokenizerMultiReceptor instance
 * @return Pointer to newly created instance, or NULL on failure
 */
TokenizerMultiReceptor* TokenizerMultiReceptor_Create(void);

/**
 * @brief Destroy a TokenizerMultiReceptor instance
 * @param me Pointer to the instance to destroy
 */
void TokenizerMultiReceptor_Destroy(TokenizerMultiReceptor* const me);

/**
 * @brief Initialize a TokenizerMultiReceptor instance
 * @param me Pointer to the instance to initialize
 */
void TokenizerMultiReceptor_Init(TokenizerMultiReceptor* const me);

/**
 * @brief Cleanup a TokenizerMultiReceptor instance
 * @param me Pointer to the instance to cleanup
 */
void TokenizerMultiReceptor_Cleanup(TokenizerMultiReceptor* const me);

/* ============================================================================
 * Event Receptors - Multiple Event Receptor Pattern Core
 * ============================================================================ */

/**
 * @brief Process a digit character event
 * @param me Pointer to the tokenizer instance
 * @param c The digit character to process
 */
void TokenizerMultiReceptor_evDigit(TokenizerMultiReceptor* const me, char c);

/**
 * @brief Process a decimal point event
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_evDot(TokenizerMultiReceptor* const me);

/**
 * @brief Process an end of string event
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_evEndOfString(TokenizerMultiReceptor* const me);

/**
 * @brief Process a whitespace event
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_evWhiteSpace(TokenizerMultiReceptor* const me);

/* ============================================================================
 * State Entry Actions
 * ============================================================================ */

/**
 * @brief Entry action for GotNumber state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_enter_GotNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Entry action for NoNumber state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_enter_NoNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Entry action for ProcessingFractionalPart sub-state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_enter_ProcessingFractionalPart(TokenizerMultiReceptor* const me);

/**
 * @brief Entry action for ProcessingWholePart sub-state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_enter_ProcessingWholePart(TokenizerMultiReceptor* const me);

/* ============================================================================
 * State Exit Actions
 * ============================================================================ */

/**
 * @brief Exit action for GotNumber state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_exit_GotNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for NoNumber state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_exit_NoNumber(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for ProcessingFractionalPart sub-state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_exit_ProcessingFractionalPart(TokenizerMultiReceptor* const me);

/**
 * @brief Exit action for ProcessingWholePart sub-state
 * @param me Pointer to the tokenizer instance
 */
void TokenizerMultiReceptor_exit_ProcessingWholePart(TokenizerMultiReceptor* const me);

/* ============================================================================
 * Accessor Methods
 * ============================================================================ */

/**
 * @brief Get the mutex associated with this tokenizer
 * @param me Pointer to the tokenizer instance
 * @return Pointer to the mutex
 */
Mutex* TokenizerMultiReceptor_getItsMutex(const TokenizerMultiReceptor* const me);

/**
 * @brief Set the mutex for this tokenizer
 * @param me Pointer to the tokenizer instance
 * @param p_Mutex Pointer to the mutex to set
 */
void TokenizerMultiReceptor_setItsMutex(TokenizerMultiReceptor* const me, Mutex* p_Mutex);

/**
 * @brief Get the current result value
 * @param me Pointer to the tokenizer instance
 * @return Current parsed number value
 */
double TokenizerMultiReceptor_getResult(const TokenizerMultiReceptor* const me);

/**
 * @brief Get the current state
 * @param me Pointer to the tokenizer instance
 * @return Current high-level state
 */
TSTATETYPE TokenizerMultiReceptor_getState(const TokenizerMultiReceptor* const me);

/**
 * @brief Get the current sub-state
 * @param me Pointer to the tokenizer instance
 * @return Current sub-state
 */
TSUBSTATETYPE TokenizerMultiReceptor_getSubState(const TokenizerMultiReceptor* const me);

#endif /* TOKENIZER_MULTI_RECEPTOR_H */
