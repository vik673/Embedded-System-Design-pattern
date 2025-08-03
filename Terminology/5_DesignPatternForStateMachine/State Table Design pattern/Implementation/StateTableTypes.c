#include "StateTableTypes.h"

/**
 * @brief Convert character digit to integer value
 * @param c Character representing a digit ('0'-'9')
 * @return Integer value of the digit (0-9)
 */
int digit(char c) {
    return c - '0';
}

/**
 * @brief Convert state enum to string for debugging
 * @param state State to convert
 * @return String representation of the state
 */
const char* stateToString(StateType state) {
    switch (state) {
        case STATE_NONUMBER:
            return "STATE_NONUMBER";
        case STATE_GOTNUMBER_WHOLE:
            return "STATE_GOTNUMBER_WHOLE";
        case STATE_GOTNUMBER_FRACTIONAL:
            return "STATE_GOTNUMBER_FRACTIONAL";
        default:
            return "UNKNOWN_STATE";
    }
}

/**
 * @brief Convert event enum to string for debugging
 * @param event Event to convert
 * @return String representation of the event
 */
const char* eventToString(EventType event) {
    switch (event) {
        case EVENT_DIGIT:
            return "EVENT_DIGIT";
        case EVENT_DOT:
            return "EVENT_DOT";
        case EVENT_WHITESPACE:
            return "EVENT_WHITESPACE";
        case EVENT_END_OF_STRING:
            return "EVENT_END_OF_STRING";
        default:
            return "UNKNOWN_EVENT";
    }
}

/**
 * @brief Convert action enum to string for debugging
 * @param action Action to convert
 * @return String representation of the action
 */
const char* actionToString(ActionType action) {
    switch (action) {
        case ACTION_NONE:
            return "ACTION_NONE";
        case ACTION_START_NUMBER:
            return "ACTION_START_NUMBER";
        case ACTION_ADD_DIGIT_WHOLE:
            return "ACTION_ADD_DIGIT_WHOLE";
        case ACTION_ADD_DIGIT_FRACTIONAL:
            return "ACTION_ADD_DIGIT_FRACTIONAL";
        case ACTION_START_FRACTIONAL:
            return "ACTION_START_FRACTIONAL";
        case ACTION_FINISH_NUMBER:
            return "ACTION_FINISH_NUMBER";
        case ACTION_RESET:
            return "ACTION_RESET";
        default:
            return "UNKNOWN_ACTION";
    }
}
