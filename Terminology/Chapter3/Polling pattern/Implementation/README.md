# Polling Pattern Implementation

## Overview
The **Polling Pattern** is used for gathering sensor data or hardware signals by periodically checking (polling) the devices. This pattern is ideal when data are not so urgent as to require interrupts and when the hardware does not support interrupt generation.

## Abstract
Polling can be implemented in two forms:
- **Opportunistic Polling:** Embedded in the main processing loop—data are polled when it is convenient.
- **Periodic Polling:** Uses a timer to trigger polling at regular intervals.

A key advantage is simplicity—avoiding the complexity of interrupts—while ensuring that sensor data are collected consistently.

## Problem
When hardware signals do not arrive very urgently or if the device lacks interrupt capability, polling provides a straightforward method for obtaining sensor data. The challenge is ensuring that the polling frequency is high enough so as not to miss updates, yet not so high as to waste system resources.

## Pattern Structure
The structure of a typical periodic polling implementation includes:
1. **ApplicationProcessingElement:**  
   Contains the main processing loop that calls the poll() function.
2. **Device:**  
   Represents the hardware sensor or signal source.
3. **Poller:**  
   - *PeriodicPoller:* Uses a timer (e.g., via BCTimer) to invoke poll() at a set interval.
   - *OpportunisticPoller:* Polls at convenient moments during processing.
4. **PollDataClient:**  
   Receives and processes the data gathered by the poller.

## Included Hardware Basics
Software-accessible hardware is categorized into:
- **Infrastructure:** CPUs, memory, storage, timers, I/O devices, ports, and interrupts.
- **Sensors:** Devices that monitor physical phenomena.
- **Actuators:** Devices that change a physical state.

## Class Diagram Explanation
See the file *ClassDiagram.puml*. In this design:
- **BCPeriodicPoller** coordinates the polling process by:
  - Managing a poll time,
  - Aggregating multiple sensor devices (e.g., BreathingCircuitSensor),
  - Updating a display (MedicalDisplay) based on the collected data.
- **BCTimer** is responsible for generating periodic timeouts that trigger the poll() method.
- **BreathingCircuitSensor** models each sensor device that provides data.
- **MedicalDisplay** is in charge of presenting the polled data.

This decoupled design lets the poller refresh sensor data and update the display without interfering with the primary application processing.

## Sequence Diagram Explanation
See the file *SequenceDiagram.puml*. The diagram outlines:
1. **Initialization:**  
   The application creates a BCPeriodicPoller instance and installs timer handlers.
2. **Polling Cycle:**  
   - The timer triggers a poll() call in BCPeriodicPoller.
   - The poll() method reads data from each BreathingCircuitSensor.
   - The collected data (such as O2 concentration, gas flow, and circuit pressure) are then forwarded to the MedicalDisplay.
3. **Termination:**  
   The application eventually stops the polling process by stopping the timer.

This flow ensures regular, timely data acquisition.

---

## Commands

### Compile the Code
```bash
gcc -o PollingPattern.exe BCPeriodicPoller.c BCTimer.c BreathingCircuitSensor.c MedicalDisplay.c main.c
```

### Execute the Code
```bash
./PollingPattern.exe
```

---

## Summary
The Polling Pattern implementation demonstrates an effective method for non-time-critical sensor data acquisition. It leverages periodic polling to gather data from multiple devices and update a user display, while keeping the hardware basics intact.