# Queuing Pattern

## Overview
The **Queuing Pattern** facilitates asynchronous communication between tasks by storing messages in a first-in-first-out (FIFO) queue. In this pattern, the sender posts a message to the queue, and later the receiver removes the message to process it. By making copies of messages (pass-by-value), this pattern avoids race conditions and mutual exclusion issues when sharing data. However, the message is processed only when the receiver's task cycles and retrieves it, so there is inherent latency.

## Abstract
- **Message Queuing:** Tasks exchange information via queued messages.
- **Decoupling:** Senders and receivers are not synchronized in time; they communicate asynchronously.
- **Isolation:** Data is passed by value, which protects against concurrent modifications.
- **Resource Serialization:** The queue serializes access to the shared resource, ensuring that only one message is handled at any given time.

## Problem
In multithreaded systems, tasks must exchange information without corrupting shared data. The Queuing Pattern addresses both synchronization and data integrity by placing messages in a queue and processing them one at a time using a mutual exclusion mechanism (i.e., a mutex).

## Pattern Components
- **Message:** An abstraction representing the data exchanged between tasks.
- **MessageQueue:** A FIFO structure that holds messages until they are processed.
  - Operations include `insert()`, `remove()`, and helper functions like `getNextIndex()`.
- **Mutex:** Ensures that operations on the MessageQueue are performed atomically, preventing race conditions.
- **QTask:** Represents a client that either inserts messages into the queue or removes and processes them.

## Class Diagram Explanation
The class diagram (see *ClassDiagram.puml*) illustrates:
- **MessageQueue:** Encapsulates the FIFO data structure. It maintains the head, tail, and size of the queue. It uses a **Mutex** to serialize access.
- **Message:** Represents the individual unit of data, which may be a simple value or a more complex structure.
- **QTask:** Acts as the producer or consumer, depending on whether it inserts messages or removes them from the queue.

This separation of concerns guarantees that messages can be safely enqueued and dequeued without interference from concurrent tasks.

## Sequence Diagram Explanation
The sequence diagram (see *SequenceDiagram.puml*) demonstrates the typical processing flow:
1. A **QTask (Producer)** creates a message and calls the `insert()` operation on the **MessageQueue**.
2. The **MessageQueue** locks its associated **Mutex**, enqueues the message, updates its indices, and then releases the lock.
3. Later, a **QTask (Consumer)** calls the `remove()` operation.
4. The **MessageQueue** locks the mutex, removes the oldest message, updates the queue indices, releases the mutex, and returns the message.
5. The consumer then processes the message independently.

This asynchronous mechanism decouples the sending and receiving tasks, allowing each to operate at its own pace.

---

## Commands

### Compile the Code
```bash
gcc -o QueuingPattern.exe MessageQueue.c QTask.c ...existing code...
```

### Execute the Code
```bash
./QueuingPattern.exe
```

---

## Summary
The Queuing Pattern provides a robust framework for asynchronous communication between tasks, ensuring message integrity and serialization of access through the use of a FIFO queue and mutexes. This design simplifies intertask communication without risking data corruption.