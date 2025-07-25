#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cctype>

/**
 * State Pattern Implementation - Number Tokenizer
 * 
 * This implementation demonstrates the State Pattern using a number tokenizer
 * that can parse decimal numbers (e.g., "1.23", "456", "78.9")
 * 
 * The pattern allows an object to change its behavior when its internal state changes.
 * The object will appear to change its class.
 */

// Forward declarations
class Context;

// Abstract State Base Class
class State {
public:
    virtual ~State() = default;
    virtual bool handleDigit(Context* context, char digit) = 0;
    virtual bool handleDot(Context* context) = 0;
    virtual bool handleWhitespace(Context* context) = 0;
    virtual bool handleEndOfString(Context* context) = 0;
    virtual void entryAction(Context* context) {}
    virtual void exitAction(Context* context) {}
    virtual std::string getStateName() const = 0;
};

// Context Class - Number Tokenizer
class Context {
private:
    std::unique_ptr<State> currentState;
    double result;
    double tensPlace;
    char currentChar;
    std::string input;
    size_t position;

public:
    Context();
    ~Context() = default;

    // State management
    void setState(std::unique_ptr<State> newState);
    State* getCurrentState() const { return currentState.get(); }

    // Event handlers
    bool processDigit(char digit);
    bool processDot();
    bool processWhitespace();
    bool processEndOfString();

    // Data accessors
    double getResult() const { return result; }
    void setResult(double value) { result = value; }
    double getTensPlace() const { return tensPlace; }
    void setTensPlace(double value) { tensPlace = value; }
    char getCurrentChar() const { return currentChar; }
    void setCurrentChar(char c) { currentChar = c; }

    // Process complete string
    void processString(const std::string& str);
    void printResult() const;
    void reset();

    // Helper functions
    static int digitValue(char c) { return c - '0'; }
    static bool isDigit(char c) { return std::isdigit(c); }
};

// Concrete State: No Number State
class NoNumberState : public State {
public:
    bool handleDigit(Context* context, char digit) override;
    bool handleDot(Context* context) override;
    bool handleWhitespace(Context* context) override;
    bool handleEndOfString(Context* context) override;
    void entryAction(Context* context) override;
    std::string getStateName() const override { return "NoNumberState"; }
};

// Concrete State: Processing Whole Part State
class ProcessingWholeState : public State {
public:
    bool handleDigit(Context* context, char digit) override;
    bool handleDot(Context* context) override;
    bool handleWhitespace(Context* context) override;
    bool handleEndOfString(Context* context) override;
    void entryAction(Context* context) override;
    std::string getStateName() const override { return "ProcessingWholeState"; }
};

// Concrete State: Processing Fraction State
class ProcessingFractionState : public State {
public:
    bool handleDigit(Context* context, char digit) override;
    bool handleDot(Context* context) override;
    bool handleWhitespace(Context* context) override;
    bool handleEndOfString(Context* context) override;
    void entryAction(Context* context) override;
    std::string getStateName() const override { return "ProcessingFractionState"; }
};

// Context Implementation
Context::Context() : result(0.0), tensPlace(10.0), currentChar('\0'), position(0) {
    currentState = std::make_unique<NoNumberState>();
    currentState->entryAction(this);
}

void Context::setState(std::unique_ptr<State> newState) {
    if (currentState) {
        currentState->exitAction(this);
    }
    currentState = std::move(newState);
    if (currentState) {
        currentState->entryAction(this);
    }
}

bool Context::processDigit(char digit) {
    currentChar = digit;
    return currentState->handleDigit(this, digit);
}

bool Context::processDot() {
    return currentState->handleDot(this);
}

bool Context::processWhitespace() {
    return currentState->handleWhitespace(this);
}

bool Context::processEndOfString() {
    return currentState->handleEndOfString(this);
}

void Context::processString(const std::string& str) {
    input = str;
    position = 0;
    
    std::cout << "\n=== Processing String: \"" << str << "\" ===" << std::endl;
    
    for (char c : str) {
        std::cout << "Current State: " << currentState->getStateName() 
                  << ", Processing char: '" << c << "'" << std::endl;
        
        if (isDigit(c)) {
            processDigit(c);
        } else if (c == '.') {
            processDot();
        } else if (std::isspace(c)) {
            processWhitespace();
        }
        position++;
    }
    
    // Process end of string
    processEndOfString();
}

void Context::printResult() const {
    std::cout << "Parsed Number: " << result << std::endl;
}

void Context::reset() {
    result = 0.0;
    tensPlace = 10.0;
    currentChar = '\0';
    position = 0;
    setState(std::make_unique<NoNumberState>());
}

// NoNumberState Implementation
bool NoNumberState::handleDigit(Context* context, char digit) {
    exitAction(context);
    
    // Transition action
    context->setCurrentChar(digit);
    context->setTensPlace(10.0);
    
    // Change state
    context->setState(std::make_unique<ProcessingWholeState>());
    return true;
}

bool NoNumberState::handleDot(Context* context) {
    std::cout << "Error: Cannot start with dot" << std::endl;
    return false; // Discard event
}

bool NoNumberState::handleWhitespace(Context* context) {
    return false; // Discard event
}

bool NoNumberState::handleEndOfString(Context* context) {
    return false; // Discard event
}

void NoNumberState::entryAction(Context* context) {
    context->setResult(0.0);
}

// ProcessingWholeState Implementation
bool ProcessingWholeState::handleDigit(Context* context, char digit) {
    context->setCurrentChar(digit);
    // Stay in same state, but trigger entry action
    entryAction(context);
    return true;
}

bool ProcessingWholeState::handleDot(Context* context) {
    exitAction(context);
    context->setState(std::make_unique<ProcessingFractionState>());
    return true;
}

bool ProcessingWholeState::handleWhitespace(Context* context) {
    exitAction(context);
    context->printResult();
    context->setState(std::make_unique<NoNumberState>());
    return true;
}

bool ProcessingWholeState::handleEndOfString(Context* context) {
    exitAction(context);
    context->printResult();
    context->setState(std::make_unique<NoNumberState>());
    return true;
}

void ProcessingWholeState::entryAction(Context* context) {
    double current = context->getResult();
    char digit = context->getCurrentChar();
    context->setResult(current * 10 + Context::digitValue(digit));
}

// ProcessingFractionState Implementation
bool ProcessingFractionState::handleDigit(Context* context, char digit) {
    // Transition action - process fractional digit
    context->setCurrentChar(digit);
    double current = context->getResult();
    double tens = context->getTensPlace();
    current += Context::digitValue(digit) / tens;
    context->setResult(current);
    context->setTensPlace(tens * 10);
    
    // Stay in same state
    return true;
}

bool ProcessingFractionState::handleDot(Context* context) {
    std::cout << "Error: Multiple dots not allowed" << std::endl;
    return false; // Discard event
}

bool ProcessingFractionState::handleWhitespace(Context* context) {
    exitAction(context);
    context->printResult();
    context->setState(std::make_unique<NoNumberState>());
    return true;
}

bool ProcessingFractionState::handleEndOfString(Context* context) {
    exitAction(context);
    context->printResult();
    context->setState(std::make_unique<NoNumberState>());
    return true;
}

void ProcessingFractionState::entryAction(Context* context) {
    // Setup for fractional processing
    context->setTensPlace(10.0);
}

// Demo function
void demonstrateStatePattern() {
    std::cout << "=== State Pattern Demo - Number Tokenizer ===" << std::endl;
    
    Context tokenizer;
    
    // Test cases
    std::vector<std::string> testCases = {
        "123",
        "45.67",
        "1.23 456.78",
        "89",
        "0.5",
        ".5",  // Error case
        "12.34.56"  // Error case
    };
    
    for (const auto& testCase : testCases) {
        tokenizer.processString(testCase);
        tokenizer.reset();
        std::cout << std::endl;
    }
}

int main() {
    demonstrateStatePattern();
    return 0;
}
