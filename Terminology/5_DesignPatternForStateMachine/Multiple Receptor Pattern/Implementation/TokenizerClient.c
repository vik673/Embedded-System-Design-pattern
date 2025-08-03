#include "TokenizerMultiReceptor.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @file TokenizerClient.c
 * @brief Example client demonstrating the Multiple Receptor Pattern usage
 * 
 * This file shows how to use the TokenizerMultiReceptor to parse numbers
 * from strings using the Multiple Event Receptor Pattern.
 */

/**
 * @brief Process a string using the tokenizer
 * @param tokenizer Pointer to the tokenizer instance
 * @param input String to process
 */
void processString(TokenizerMultiReceptor* tokenizer, const char* input) {
    if (tokenizer == NULL || input == NULL) {
        return;
    }
    
    printf("\n=== Processing string: \"%s\" ===\n", input);
    
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        
        if (isdigit(c)) {
            TokenizerMultiReceptor_evDigit(tokenizer, c);
        } else if (c == '.') {
            TokenizerMultiReceptor_evDot(tokenizer);
        } else if (isspace(c)) {
            TokenizerMultiReceptor_evWhiteSpace(tokenizer);
        }
        /* Ignore other characters */
    }
    
    /* Signal end of string */
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    printf("=== End of processing ===\n\n");
}

/**
 * @brief Demonstrate the tokenizer with various test cases
 */
void demonstrateTokenizer(void) {
    /* Create tokenizer instance */
    TokenizerMultiReceptor* tokenizer = TokenizerMultiReceptor_Create();
    if (tokenizer == NULL) {
        printf("Failed to create tokenizer\n");
        return;
    }
    
    /* Create and set mutex */
    Mutex* mutex = Mutex_Create();
    if (mutex != NULL) {
        TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    }
    
    /* Test cases */
    const char* testCases[] = {
        "123",           /* Simple integer */
        "123.456",       /* Decimal number */
        "0.789",         /* Fractional number starting with 0 */
        ".5",            /* Fractional number starting with dot */
        "42 58",         /* Multiple numbers separated by space */
        "3.14 2.71",     /* Multiple decimal numbers */
        "100.0",         /* Number with trailing zero */
        ""               /* Empty string */
    };
    
    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    printf("=== Multiple Receptor Pattern Demonstration ===\n");
    printf("Testing TokenizerMultiReceptor with various inputs\n\n");
    
    for (size_t i = 0; i < numTests; i++) {
        /* Reset tokenizer for each test */
        TokenizerMultiReceptor_Init(tokenizer);
        TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
        
        processString(tokenizer, testCases[i]);
    }
    
    /* Cleanup */
    if (mutex != NULL) {
        Mutex_Destroy(mutex);
    }
    TokenizerMultiReceptor_Destroy(tokenizer);
}

/**
 * @brief Interactive mode for testing the tokenizer
 */
void interactiveMode(void) {
    char input[256];
    TokenizerMultiReceptor* tokenizer = TokenizerMultiReceptor_Create();
    if (tokenizer == NULL) {
        printf("Failed to create tokenizer\n");
        return;
    }
    
    Mutex* mutex = Mutex_Create();
    if (mutex != NULL) {
        TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    }
    
    printf("\n=== Interactive Mode ===\n");
    printf("Enter strings to parse (empty line to quit):\n");
    
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
        
        /* Reset tokenizer */
        TokenizerMultiReceptor_Init(tokenizer);
        TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
        
        processString(tokenizer, input);
    }
    
    /* Cleanup */
    if (mutex != NULL) {
        Mutex_Destroy(mutex);
    }
    TokenizerMultiReceptor_Destroy(tokenizer);
    printf("Goodbye!\n");
}

/**
 * @brief Main function
 */
int main(int argc, char* argv[]) {
    printf("Multiple Event Receptor Pattern - Tokenizer Example\n");
    printf("==================================================\n\n");
    
    /* Run demonstration */
    demonstrateTokenizer();
    
    /* Interactive mode */
    if (argc > 1 && strcmp(argv[1], "-i") == 0) {
        interactiveMode();
    }
    
    return 0;
}
