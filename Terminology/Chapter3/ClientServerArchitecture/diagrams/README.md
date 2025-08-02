# Client-Server Architecture with Observer Pattern

## Overview
This implementation demonstrates a **client-server architecture** using the **Observer Pattern**, where:
- The **Subject** (server) manages a list of observers (clients) and notifies them of changes.
- Observers dynamically subscribe to or unsubscribe from the subject.
- The subject notifies all subscribed observers when data changes.

---

## Key Components

### 1. **AbstractSubject**
- Base class for the server.
- Manages a list of observers and provides methods to:
  - `subscribe(observer)`: Add an observer.
  - `unsubscribe(observer)`: Remove an observer.
  - `notify(data)`: Notify all subscribed observers.

### 2. **AbstractObserver**
- Base class for clients.
- Provides an `update(data)` method to process notifications from the subject.

### 3. **ConcreteSubject**
- Implements the server-side logic.
- Inherits from `AbstractSubject`.
- Provides application-specific data or services.

### 4. **ConcreteObserver**
- Implements the client-side logic.
- Inherits from `AbstractObserver`.
- Processes notifications from the subject.

---

## Class Diagram Explanation
The class diagram represents the relationships between the subject and observers:
1. **AbstractSubject**:
   - Manages a list of observers and provides methods for subscription and notification.

2. **AbstractObserver**:
   - Defines the `update` method for processing notifications.

3. **ConcreteSubject**:
   - Implements the server-side logic, including data management and notification.

4. **ConcreteObserver**:
   - Implements the client-side logic, including subscribing, unsubscribing, and processing updates.

---

## Sequence Diagram Explanation
The sequence diagram illustrates the flow of operations:
1. Observers subscribe to the subject using the `subscribe` method.
2. The subject updates its data and notifies all subscribed observers using the `notify` method.
3. Observers process the notification using their `update` method.

---

## Commands

### Compile the Code
```bash
gcc -o ObserverPattern.exe main.c Subject.c Observer.c
```

### Execute the Code
```bash
./ObserverPattern.exe
```

---

## Summary
This implementation demonstrates the observer pattern, allowing dynamic addition and removal of clients while ensuring efficient and timely updates.
