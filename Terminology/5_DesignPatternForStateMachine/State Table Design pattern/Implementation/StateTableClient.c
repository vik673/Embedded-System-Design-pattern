#include "StateTableTokenizer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @file StateTableClient.c
 * @brief Example client demonstrating the State Table Design Pattern usage
 * 
 * This file shows how to use the StateTableTokenizer to parse numbers
 * from strings using the State Table Design Pattern.
 */

/**
 * @brief Process a string using the state table tokenizer
 * @param tokenizer Pointer to the tokenizer instance
 * @param input String to process
 */
void processString(StateTableTokenizer* tokenizer, const char* input) {
    if (tokenizer == NULL || input == NULL) {
        return;
    }
    
    printf("\n=== Processing string: \"%s\" ===\n", input);
    
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        
        if (isdigit(c)) {
            StateTableTokenizer_ProcessDigit(tokenizer, c);
        } else if (c == '.') {
            StateTableTokenizer_ProcessDot(tokenizer);
        } else if (isspace(c)) {
            StateTableTokenizer_ProcessWhitespace(tokenizer);
        }
        /* Ignore other characters */
    }
    
    /* Signal end of string */
    StateTableTokenizer_ProcessEndOfString(tokenizer);
    printf("=== End of processing ===\n\n");
}

/**
 * @brief Demonstrate the state table pattern with various test cases
 */
void demonstrateStateTable(void) {
    /* Create tokenizer instance */
    StateTableTokenizer* tokenizer = StateTableTokenizer_Create();
    if (tokenizer == NULL) {
        printf("Failed to create tokenizer\n");
        return;
    }
    
    /* Create and set mutex */
    Mutex* mutex = Mutex_Create();
    if (mutex != NULL) {
        StateTableTokenizer_SetMutex(tokenizer, mutex);
    }
    
    /* Print the state table */
    StateTableTokenizer_PrintStateTable(tokenizer);
    
    /* Test cases */
    const char* testCases[] = {
        "123",           /* Simple integer */
        "123.456",       /* Decimal number */
        "0.789",         /* Fractional number starting with 0 */
        ".5",            /* Fractional number starting with dot */
        "42 58",         /* Multiple numbers separated by space */
        "3.14 2.71",     /* Multiple decimal numbers */
        "100.0",         /* Number with trailing zero */
        "12..34",        /* Invalid: multiple dots */
        ""               /* Empty string */
    };
    
    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    printf("=== State Table Design Pattern Demonstration ===\n");
    printf("Testing StateTableTokenizer with various inputs\n\n");
    
    for (size_t i = 0; i < numTests; i++) {
        /* Reset tokenizer for each test */
        StateTableTokenizer_Init(tokenizer);
        StateTableTokenizer_SetMutex(tokenizer, mutex);
        StateTableTokenizer_ResetStatistics(tokenizer);
        
        processString(tokenizer, testCases[i]);
        
        /* Print statistics for this test */
        StateTableTokenizer_PrintStatistics(tokenizer);
    }
    
    /* Cleanup */
    if (mutex != NULL) {
        Mutex_Destroy(mutex);
    }
    StateTableTokenizer_Destroy(tokenizer);
}

/**
 * @brief Interactive mode for testing the tokenizer
 */
void interactiveMode(void) {
    char input[256];
    StateTableTokenizer* tokenizer = StateTableTokenizer_Create();
    if (tokenizer == NULL) {
        printf("Failed to create tokenizer\n");
        return;
    }
    
    Mutex* mutex = Mutex_Create();
    if (mutex != NULL) {
        StateTableTokenizer_SetMutex(tokenizer, mutex);
    }
    
    printf("\n=== Interactive Mode ===\n");
    printf("Enter strings to parse (empty line to quit):\n");
    printf("Special commands:\n");
    printf("  'table' - Show state table\n");
    printf("  'stats' - Show statistics\n");
    printf("  'reset' - Reset statistics\n\n");
    
    while (1) {
        printf("Input: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        /* Remove newline */
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        /* Check for empty input (quit condition) */
        if (strlen(input) == 0) {
            break;
        }
        
        /* Check for special commands */
        if (strcmp(input, "table") == 0) {
            StateTableTokenizer_PrintStateTable(tokenizer);
            continue;
        }
        
        if (strcmp(input, "stats") == 0) {
            StateTableTokenizer_PrintStatistics(tokenizer);
            continue;
        }
        
        if (strcmp(input, "reset") == 0) {
            StateTableTokenizer_ResetStatistics(tokenizer);
            printf("Statistics reset\n");
            continue;
        }
        
        /* Reset tokenizer state but keep statistics */
        StateType oldState = StateTableTokenizer_GetCurrentState(tokenizer);
        StateTableTokenizer_Init(tokenizer);
        StateTableTokenizer_SetMutex(tokenizer, mutex);
        printf("Reset state from %s to %s\n", 
               stateToString(oldState), 
               stateToString(StateTableTokenizer_GetCurrentState(tokenizer)));
        
        processString(tokenizer, input);
    }
    
    /* Final statistics */
    printf("\n=== Final Statistics ===\n");
    StateTableTokenizer_PrintStatistics(tokenizer);
    
    /* Cleanup */
    if (mutex != NULL) {
        Mutex_Destroy(mutex);
    }
    StateTableTokenizer_Destroy(tokenizer);
    printf("Goodbye!\n");
}

/**
 * @brief Demonstrate table-driven approach vs. traditional switch statements
 */
void compareApproaches(void) {
    printf("\n=== State Table Pattern vs. Traditional Approach ===\n\n");
    
    printf("State Table Pattern Benefits:\n");
    printf("1. Data-driven: State transitions defined in a table\n");
    printf("2. Easy to modify: Change table entries without recompiling logic\n");
    printf("3. Consistent: All transitions follow the same pattern\n");
    printf("4. Debuggable: Table can be printed and analyzed\n");
    printf("5. Performance: O(1) lookup time for transitions\n");
    printf("6. Maintainable: Clear separation of states, events, and actions\n\n");
    
    printf("Traditional Switch-Case Approach:\n");
    printf("1. Logic-driven: State transitions embedded in code\n");
    printf("2. Harder to modify: Requires code changes and recompilation\n");
    printf("3. Potentially inconsistent: Different handling patterns\n");
    printf("4. Less debuggable: Logic scattered across functions\n");
    printf("5. Variable performance: Depends on switch implementation\n");
    printf("6. More complex: Logic and data mixed together\n\n");
    
    printf("The State Table Pattern is ideal when:\n");
    printf("- You have a well-defined set of states and events\n");
    printf("- State transitions are frequent and need to be efficient\n");
    printf("- The state machine needs to be easily modifiable\n");
    printf("- You need runtime analysis of state transitions\n");
    printf("- You want to separate state logic from business logic\n\n");
}

/**
 * @brief Main function
 */
int main(int argc, char* argv[]) {
    printf("State Table Design Pattern - Tokenizer Example\n");
    printf("===============================================\n\n");
    
    /* Compare approaches */
    compareApproaches();
    
    /* Run demonstration */
    demonstrateStateTable();
    
    /* Interactive mode */
    if (argc > 1 && strcmp(argv[1], "-i") == 0) {
        interactiveMode();
    }
    
    return 0;
}
