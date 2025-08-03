# Guarded Call Pattern

## Overview
The **Guarded Call Pattern** serializes access to a set of services that could interfere with one another if invoked simultaneously by multiple threads. By using a locking mechanism (typically a semaphore), the pattern ensures that only one thread can execute the protected resource's functions at any time. This is critical in preemptive multitasking environments to prevent data corruption and erroneous computation.

## Abstract
The pattern establishes mutual exclusion by having the guarded resource call lock and release operations on a semaphore surrounding its critical code sections. When a thread invokes a service on the guarded resource, it first locks the semaphore, performs its critical operation, and then releases the semaphore before returning. This guarantees that access to the shared resource is serialized.

## Problem
- Timely synchronization between threads is needed for safe, reliable operation.
- Without proper locking, concurrent accesses can corrupt shared data or lead to inconsistent system state.
- However, naive locking can cause issues such as unbounded priority inversion. Such issues are typically mitigated by employing additional strategies like priority inheritance (if supported by the RTOS).

## Pattern Structure
In a typical implementation:
- **GuardedResource**: Encapsulates the shared resource and offers functions (e.g., `setValue()` and `getValue()`) that include a lock–critical region–unlock sequence.
- **PreemptiveTask**: Represents any thread that might invoke a guarded function.
- **Semaphore**: Implements the actual locking mechanism. It provides `lock()` and `release()` operations.
- **StaticPriorityScheduler** (RTOS provided): Coordinates task execution and handles blocking/unblocking when semaphore calls are made.

## Class Diagram Explanation
The class diagram (see *ClassDiagram.puml*) illustrates the key components:
- **GuardedResource**: Represents the shared resource. It includes methods that lock a semaphore before accessing the resource and release it afterward.
- **PreemptiveTask**: Models threads that use the guarded resource.
- **Semaphore**: Provides the mutual exclusion mechanism required to protect the guarded resource.
  
This design decouples the synchronization logic from the application code, allowing for safe access to shared data across multiple threads.

## Sequence Diagram Explanation
The sequence diagram (see *SequenceDiagram.puml*) shows the flow when a task calls a guarded function:
1. **PreemptiveTask** calls a service (e.g., `setValue()`) on **GuardedResource**.
2. The **GuardedResource** invokes the `lock()` operation on the **Semaphore** to enter the critical region.
3. Once the lock is acquired, the critical operation is executed.
4. After completing the operation, **GuardedResource** calls the `release()` operation to exit the critical region.
5. Control returns to the **PreemptiveTask**.

This flow guarantees that only one task can access critical parts of the resource at any time.

---

## Commands

### Compile the Code
```bash
gcc -o GuardedCallPattern.exe GuardedCallExample.c ...existing code...
```

### Execute the Code
```bash
./GuardedCallPattern.exe
```

---

## Summary
The Guarded Call Pattern provides a structured approach to synchronizing access to shared resources using semaphores. By serializing access, it prevents concurrent executions that could lead to data corruption. However, care must be taken to avoid issues like unbounded priority inversion.