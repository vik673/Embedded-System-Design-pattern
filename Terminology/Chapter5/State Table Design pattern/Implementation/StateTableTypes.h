#ifndef STATE_TABLE_TYPES_H
#define STATE_TABLE_TYPES_H

/**
 * @file StateTableTypes.h
 * @brief Basic types and enumerations for the State Table Design Pattern
 * 
 * This file defines the state, event, and action types used by the
 * State Table Design Pattern implementation for a tokenizer state machine.
 */

/**
 * @brief State enumeration for the tokenizer state machine
 */
typedef enum {
    STATE_NONUMBER = 0,           /**< No number being processed */
    STATE_GOTNUMBER_WHOLE,        /**< Processing whole part of number */
    STATE_GOTNUMBER_FRACTIONAL,   /**< Processing fractional part of number */
    STATE_MAX                     /**< Maximum state value (for bounds checking) */
} StateType;

/**
 * @brief Event enumeration for the tokenizer state machine
 */
typedef enum {
    EVENT_DIGIT = 0,              /**< Digit character event */
    EVENT_DOT,                    /**< Decimal point event */
    EVENT_WHITESPACE,             /**< Whitespace character event */
    EVENT_END_OF_STRING,          /**< End of string event */
    EVENT_MAX                     /**< Maximum event value (for bounds checking) */
} EventType;

/**
 * @brief Action enumeration for state transitions
 */
typedef enum {
    ACTION_NONE = 0,              /**< No action required */
    ACTION_START_NUMBER,          /**< Start processing a new number */
    ACTION_ADD_DIGIT_WHOLE,       /**< Add digit to whole part */
    ACTION_ADD_DIGIT_FRACTIONAL,  /**< Add digit to fractional part */
    ACTION_START_FRACTIONAL,      /**< Start processing fractional part */
    ACTION_FINISH_NUMBER,         /**< Finish processing current number */
    ACTION_RESET,                 /**< Reset the tokenizer */
    ACTION_MAX                    /**< Maximum action value (for bounds checking) */
} ActionType;

/**
 * @brief Forward declaration of the tokenizer context
 */
typedef struct TokenizerContext TokenizerContext;

/**
 * @brief Function pointer type for action functions
 * @param context Pointer to the tokenizer context
 * @param eventData Additional data associated with the event (e.g., character)
 */
typedef void (*ActionFunction)(TokenizerContext* context, char eventData);

/**
 * @brief State table entry structure
 */
typedef struct {
    StateType nextState;          /**< Next state to transition to */
    ActionType actionType;        /**< Type of action to perform */
    ActionFunction actionFunc;    /**< Function pointer to action implementation */
} StateTableEntry;

/**
 * @brief Convert character digit to integer value
 * @param c Character representing a digit ('0'-'9')
 * @return Integer value of the digit (0-9)
 */
int digit(char c);

/**
 * @brief Convert state enum to string for debugging
 * @param state State to convert
 * @return String representation of the state
 */
const char* stateToString(StateType state);

/**
 * @brief Convert event enum to string for debugging
 * @param event Event to convert
 * @return String representation of the event
 */
const char* eventToString(EventType event);

/**
 * @brief Convert action enum to string for debugging
 * @param action Action to convert
 * @return String representation of the action
 */
const char* actionToString(ActionType action);

#endif /* STATE_TABLE_TYPES_H */
