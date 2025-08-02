# Interrupt Pattern

## Overview
The **Interrupt Pattern** structures the system to immediately respond to asynchronous events by pausing normal processing, servicing the interrupt, and then resuming the original task. This pattern is critical in embedded systems where high urgency events must be processed promptly.

---

## Abstract
- Interrupt Service Routines (ISRs) are used to catch events even when the system is busy with other processing.
- Upon an interrupt, the current processing is paused, the ISR handles the event, then processing resumes.
- The pattern ensures that urgent events are not missed.

---

## Problem
- In systems with multiple asynchronous events, relying solely on polling can delay processing or miss events.
- High priority events must be serviced immediately.
- The Interrupt Pattern addresses this by using hardware/OS support to suspend main processing and execute an ISR.

---

## Pattern Structure
The pattern involves the following key elements:
1. **InterruptHandler**  
   - Installs and deinstalls interrupt vectors.
   - Contains the ISRs that handle specific events.
2. **InterruptVectorTable**  
   - An array of function pointers representing the ISR addresses.
3. **vectorPtr**  
   - A pointer type for the ISRs (function pointer with no parameters).

The design ensures that ISRs are parameterless (no "me" pointer) so that the Return From Interrupt (RTI) works correctly.

---

## Class Diagram Explanation
The following class diagram (presented in UML via PlantUML) shows the conceptual structure for the Interrupt Pattern:
- **InterruptHandler**  
  - Contains methods such as `install()`, `deinstall()`, and the ISRs (e.g., `handleButtonPushInterrupt()` and `handleButtonReleaseInterrupt()`).
- **InterruptVectorTable**  
  - Represents a fixed-size array that holds addresses of the ISRs.  
- **vectorPtr**  
  - A low-level pointer type used to store ISR addresses.

The diagram illustrates that the **InterruptHandler** registers its ISRs in the **InterruptVectorTable** and that the system uses these vectors to dispatch events immediately when an interrupt occurs.

---

## Sequence Diagram Explanation
The sequence diagram shows the dynamic behavior when an interrupt occurs:
1. **Interrupt Occurrence**  
   - The hardware triggers an interrupt (e.g., a button press).
2. **ISR Invocation**  
   - The CPU suspends current execution and accesses the relevant ISR from the **InterruptVectorTable**.
3. **ISR Execution**  
   - The ISR performs minimal processing (e.g., toggles an LED).
4. **Return to Main Processing**  
   - After executing, the ISR issues a Return From Interrupt, restoring the system to normal execution.

This diagram emphasizes the time-critical path where the hardware signals an event, it is immediately handled by the ISR, and then control returns to the interrupted process.

---

## Commands

### Compile the Code
```bash
gcc -o InteruptPattern.exe ButtonHandler.c main.c
```

### Execute the Code
```bash
./InteruptPattern.exe
```

---

## Summary
The **Interrupt Pattern** is essential for ensuring that high-priority events in embedded systems are handled promptly. The extra care required for saving registers, handling vector tables, and minimizing ISR duration is offset by the enhanced responsiveness of the system.
5. **Stack Management**: Ensure adequate stack space for ISR execution

## Example Output

```
Interrupt Pattern Example
========================

Interrupt vectors installed:
- Vector 0: Button Push Interrupt
- Vector 1: Button Release Interrupt

Simulating button press interrupt...
LED turned ON (Pin 13)

Simulating button release interrupt...
LED turned OFF (Pin 13)

Checking LED state: OFF

Interrupt vectors deinstalled.

Program completed successfully.
```

## Thread Safety Considerations

In real embedded systems, consider:
- Disabling interrupts during critical sections
- Using atomic operations for shared variables
- Implementing mutex protection for shared resources
- Avoiding blocking operations in ISRs

## Further Reading

Refer to the `Interruptpattern.txt` file for detailed pattern theory and embedded-specific implementation strategies.
