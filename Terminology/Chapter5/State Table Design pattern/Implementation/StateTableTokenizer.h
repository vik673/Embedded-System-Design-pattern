#ifndef STATE_TABLE_TOKENIZER_H
#define STATE_TABLE_TOKENIZER_H

#include "StateTableTypes.h"
#include "Mutex.h"

/**
 * @file StateTableTokenizer.h
 * @brief State Table Design Pattern implementation for a number tokenizer
 * 
 * This file implements the State Table Design Pattern for a finite state machine
 * that parses numbers from character input. The pattern uses a lookup table to
 * determine state transitions and actions, making it highly efficient and easy
 * to modify.
 */

/**
 * @brief Tokenizer context structure
 * 
 * This structure contains the state machine context including the current state,
 * parsing results, and synchronization mechanisms.
 */
struct TokenizerContext {
    /* Current state machine state */
    StateType currentState;       /**< Current state of the tokenizer */
    
    /* Business logic data */
    char currentChar;             /**< Current character being processed */
    double result;                /**< Current parsed number value */
    double tensPlace;             /**< Decimal place multiplier for fractional parts */
    
    /* Synchronization */
    Mutex* mutex;                 /**< Mutex for thread-safe operations */
    
    /* Statistics and debugging */
    int transitionCount;          /**< Number of state transitions performed */
    int eventCount[EVENT_MAX];    /**< Count of each event type processed */
};

/**
 * @brief State Table Tokenizer main class
 */
typedef struct {
    TokenizerContext* context;    /**< Tokenizer context */
    StateTableEntry stateTable[STATE_MAX][EVENT_MAX];  /**< The state transition table */
} StateTableTokenizer;

/* ============================================================================
 * Constructors and Destructors
 * ============================================================================ */

/**
 * @brief Create a new StateTableTokenizer instance
 * @return Pointer to newly created instance, or NULL on failure
 */
StateTableTokenizer* StateTableTokenizer_Create(void);

/**
 * @brief Destroy a StateTableTokenizer instance
 * @param me Pointer to the instance to destroy
 */
void StateTableTokenizer_Destroy(StateTableTokenizer* const me);

/**
 * @brief Initialize a StateTableTokenizer instance
 * @param me Pointer to the instance to initialize
 */
void StateTableTokenizer_Init(StateTableTokenizer* const me);

/**
 * @brief Cleanup a StateTableTokenizer instance
 * @param me Pointer to the instance to cleanup
 */
void StateTableTokenizer_Cleanup(StateTableTokenizer* const me);

/* ============================================================================
 * Core State Table Pattern Interface
 * ============================================================================ */

/**
 * @brief Process an event using the state table
 * @param me Pointer to the tokenizer instance
 * @param event Event type to process
 * @param eventData Additional data associated with the event
 * @return 0 on success, -1 on failure
 */
int StateTableTokenizer_ProcessEvent(StateTableTokenizer* const me, 
                                    EventType event, 
                                    char eventData);

/**
 * @brief Get the current state of the tokenizer
 * @param me Pointer to the tokenizer instance
 * @return Current state
 */
StateType StateTableTokenizer_GetCurrentState(const StateTableTokenizer* const me);

/**
 * @brief Get the current result value
 * @param me Pointer to the tokenizer instance
 * @return Current parsed number value
 */
double StateTableTokenizer_GetResult(const StateTableTokenizer* const me);

/* ============================================================================
 * Convenience Event Processing Methods
 * ============================================================================ */

/**
 * @brief Process a digit character
 * @param me Pointer to the tokenizer instance
 * @param c Digit character to process
 * @return 0 on success, -1 on failure
 */
int StateTableTokenizer_ProcessDigit(StateTableTokenizer* const me, char c);

/**
 * @brief Process a decimal point
 * @param me Pointer to the tokenizer instance
 * @return 0 on success, -1 on failure
 */
int StateTableTokenizer_ProcessDot(StateTableTokenizer* const me);

/**
 * @brief Process whitespace
 * @param me Pointer to the tokenizer instance
 * @return 0 on success, -1 on failure
 */
int StateTableTokenizer_ProcessWhitespace(StateTableTokenizer* const me);

/**
 * @brief Process end of string
 * @param me Pointer to the tokenizer instance
 * @return 0 on success, -1 on failure
 */
int StateTableTokenizer_ProcessEndOfString(StateTableTokenizer* const me);

/* ============================================================================
 * Mutex Management
 * ============================================================================ */

/**
 * @brief Set the mutex for this tokenizer
 * @param me Pointer to the tokenizer instance
 * @param mutex Pointer to the mutex to set
 */
void StateTableTokenizer_SetMutex(StateTableTokenizer* const me, Mutex* mutex);

/**
 * @brief Get the mutex associated with this tokenizer
 * @param me Pointer to the tokenizer instance
 * @return Pointer to the mutex
 */
Mutex* StateTableTokenizer_GetMutex(const StateTableTokenizer* const me);

/* ============================================================================
 * Debugging and Statistics
 * ============================================================================ */

/**
 * @brief Print the current state table
 * @param me Pointer to the tokenizer instance
 */
void StateTableTokenizer_PrintStateTable(const StateTableTokenizer* const me);

/**
 * @brief Print tokenizer statistics
 * @param me Pointer to the tokenizer instance
 */
void StateTableTokenizer_PrintStatistics(const StateTableTokenizer* const me);

/**
 * @brief Reset statistics counters
 * @param me Pointer to the tokenizer instance
 */
void StateTableTokenizer_ResetStatistics(StateTableTokenizer* const me);

/* ============================================================================
 * Action Functions (Internal)
 * ============================================================================ */

/**
 * @brief Action: Do nothing
 * @param context Tokenizer context
 * @param eventData Event data
 */
void action_none(TokenizerContext* context, char eventData);

/**
 * @brief Action: Start processing a new number
 * @param context Tokenizer context
 * @param eventData Event data (digit character)
 */
void action_start_number(TokenizerContext* context, char eventData);

/**
 * @brief Action: Add digit to whole part
 * @param context Tokenizer context
 * @param eventData Event data (digit character)
 */
void action_add_digit_whole(TokenizerContext* context, char eventData);

/**
 * @brief Action: Add digit to fractional part
 * @param context Tokenizer context
 * @param eventData Event data (digit character)
 */
void action_add_digit_fractional(TokenizerContext* context, char eventData);

/**
 * @brief Action: Start processing fractional part
 * @param context Tokenizer context
 * @param eventData Event data
 */
void action_start_fractional(TokenizerContext* context, char eventData);

/**
 * @brief Action: Finish processing current number
 * @param context Tokenizer context
 * @param eventData Event data
 */
void action_finish_number(TokenizerContext* context, char eventData);

/**
 * @brief Action: Reset the tokenizer
 * @param context Tokenizer context
 * @param eventData Event data
 */
void action_reset(TokenizerContext* context, char eventData);

#endif /* STATE_TABLE_TOKENIZER_H */
