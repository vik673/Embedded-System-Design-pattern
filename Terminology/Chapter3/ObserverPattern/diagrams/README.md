# Observer Pattern

## Overview
The **Observer Pattern** (or Publish-Subscribe Pattern) enables a data source (server) to notify a set of interested clients when data have changed. This decouples the client from the server, allowing clients to subscribe or unsubscribe dynamically without altering the server code.

---

## Abstract
- Clients subscribe to the data server to receive notifications when new data arrive.
- This pattern eliminates the need for clients to poll the server.
- Data are pushed to clients according to a notification policy (e.g., upon data change or at specified intervals).

---

## Problem
- Periodic polling wastes compute and communication resources.
- The data server traditionally would need to know its clients, making the design rigid.
- The Observer Pattern allows the server to broadcast updates without prior client knowledge.

---

## Pattern Structure
The pattern comprises:
1. **AbstractSubject**:
   - Maintains a list of subscribers.
   - Provides `subscribe()` and `unsubscribe()` services.
   - Notifies all registered clients via `notify()`.
2. **AbstractClient**:
   - Declares an `accept(data)` function to process updates.
3. **ConcreteSubject**:
   - A specific implementation of the AbstractSubject (often combined with a hardware proxy).
   - Manages the actual data (the Datum) and calls `notify()` when updates occur.
4. **ConcreteClient**:
   - Implements the `accept(data)` function.
5. **NotificationHandle**:
   - Typically a function pointer (or callback) used to invoke the `accept(data)` method on the client.

---

## Class Diagram Explanation
The class diagram (see ClassDiagram.puml) shows:
- The **AbstractSubject** which provides the subscription, unsubscription, and notification functions.
- The **AbstractClient** interface that defines the `accept(data)` method.
- The **ConcreteSubject** and **ConcreteClient**, which are the realizations used in a system.
- A **NotificationHandle** (typically modeled as an array or linked list of function pointers) that binds the subject to each client.

This structure decouples the subject from its clients, allowing for runtime flexibility and efficient updates.

---

## Sequence Diagram Explanation
The sequence diagram (see SequenceDiagram.puml) illustrates:
1. **Client Subscription**: The client subscribes to the subject by providing a callback.
2. **Data Change**: When the ConcreteSubject obtains new data, it calls `notify()`.
3. **Notification Dispatch**: The subject iterates over the list of subscribers (via NotificationHandles) and calls their `accept(data)` functions.
4. **Client Processing**: Each client processes the updated data.

This flow ensures that the clients are updated only when needed, while the subject remains unaware of client specifics.

---

## Commands

### Compile the Code
```bash
gcc -o ObserverPattern.exe ConcreteSubject.c ConcreteClient.c
```

### Execute the Code
```bash
./ObserverPattern.exe
```

---

## Summary
The Observer Pattern simplifies dynamic data distribution by decoupling the data server from its clients. This allows flexible, efficient, and maintainable notification mechanisms in embedded systems.
