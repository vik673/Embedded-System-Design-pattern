# Polling Pattern

## Overview
The **Polling Pattern** is a simple way to receive sensor data or hardware signals by periodically checking (or polling) a device rather than waiting for an interrupt. It can operate in two modes:
- **Opportunistic Polling**: The system checks for data when convenient, often within a processing loop.
- **Periodic Polling**: A timer triggers regular polling of the devices.

This pattern is useful when sensor data or signals are not time-critical or when hardware cannot generate interrupts.

---

## Abstract
- **Polling** involves periodically checking a device for new data or state changes.
- In periodic polling, a timer (or poll timer) guarantees that the hardware will be sampled at a regular interval.
- Opportunistic polling is embedded into the main processing loop at convenient times.
- The pattern ensures that data are collected without requiring the hardware to support interrupts.

---

## Problem
Many embedded systems can obtain sensor data using interrupts; however, if data are not urgent or hardware lacks interrupt capabilities, polling offers a simpler design. The challenge is to ensure the polling frequency is sufficient to catch updates without imposing excessive processing overhead.

---

## Pattern Structure
The polling pattern generally includes:
1. **ApplicationProcessingElement**:  
   - Contains the main function loop that periodically calls the poll() function.
2. **Device**:  
   - The hardware or sensor that provides data and state information.
3. **Poller**:  
   - Either an opportunistic poller (embedded within a processing loop) or a periodic poller (triggered by a timer).
4. **PollDataClient**:  
   - Receives and processes the polled data.

A concrete example is implemented as the `BCPeriodicPoller` class, which aggregates a timer (`BCTimer`), several sensor devices (e.g., `BreathingCircuitSensor`), and a display element (`MedicalDisplay`).

---

## Class Diagram Explanation
The class diagram (see ClassDiagram.puml) shows the relationships among key components:
- **BCPeriodicPoller**
  - Manages the polling process by periodically sampling the sensors.
  - Contains attributes such as `pollTime`, an array of pointers to `BreathingCircuitSensor`, a pointer to a `BCTimer`, and a pointer to a `MedicalDisplay`.
- **BCTimer**
  - Provides timer services to start and stop regular polling.
- **BreathingCircuitSensor**
  - Represents a sensor device that provides data (e.g., oxygen concentration, gas pressure).
- **MedicalDisplay**
  - Receives and displays the polled data.

In this design, the `BCPeriodicPoller` coordinates the polling process by querying each sensor and then relaying the data to the `MedicalDisplay`.

---

## Sequence Diagram Explanation
The sequence diagram (see SequenceDiagram.puml) illustrates the following flow:
1. The system starts and the application initiates polling by invoking `BCPeriodicPoller_startPolling()`.
2. The `BCTimer` is started with the desired poll period.
3. When the timer interrupts, it triggers the poll() function of `BCPeriodicPoller`.
4. The poll() function retrieves data from each `BreathingCircuitSensor` and updates the `MedicalDisplay`.
5. This cycle repeats at each timer tick.

This sequence ensures regular, timely data acquisition from multiple devices.

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
The **Polling Pattern** is an effective approach for non-time-critical data acquisition in embedded systems. By either opportunistically or periodically polling devices, the system ensures that sensor data are gathered and delivered without relying on hardware interrupts.
