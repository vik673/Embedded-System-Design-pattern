# Ordered Locking Pattern

## Overview
The **Ordered Locking Pattern** eliminates deadlock by enforcing a global ordering on resource locking. Resources must be locked by a client in a predefined order, ensuring that circular wait conditions cannot occur. This pattern is particularly useful when clients hold locks over an extended period (dyadic operations) and must explicitly lock and unlock resources.

## Abstract
- Resources (OrderedResources) are assigned a unique resourceID.
- A client (ResourceClient) must acquire locks on resources in increasing order of their resourceIDs.
- The ResourceList manages the currently locked resourceIDs to enforce the rule.
- For monadic operations, the resource locks and unlocks internally.
- For dyadic operations, the client explicitly calls lock and release operations, ensuring the lock order is respected.

## Problem
Deadlock elimination is achieved by preventing circular wait. If every resource is locked in the same global order, a circular dependency among resources cannot form. The challenge is to assign and enforce unique resourceIDs and validate the order at the time of locking.

## Pattern Structure
Typical elements include:
- **Mutex:** A locking mechanism provided by the RTOS.
- **OrderedResource:** A resource with a unique resourceID. It provides both monadic and dyadic access functions.
- **ResourceList:** A global structure maintaining an array of resourceIDs currently held. It validates locking orders.
- **ResourceClient:** The calling thread that requests access to one or more OrderedResources and must follow the ordered locking policy.

## Class Diagram Explanation
See the file *ClassDiagram.puml*. In this design:
- **OrderedResource** represents the resource instance with a unique resourceID and an associated Mutex.  
- **ResourceList** manages the locked resourceIDs, enforcing that a new resource can be locked only if its resourceID is greater than any of the currently locked resources.
- **ResourceClient** calls dyadic locking functions (lockDyadic() and releaseDyadic()) on OrderedResources.  
This arrangement prevents circular waiting because clients can only acquire resources in a globally defined order.

## Sequence Diagram Explanation
See the file *SequenceDiagram.puml*. The sequence diagram depicts a typical resource locking scenario:
1. **ResourceClient** calls lockDyadic() on the first OrderedResource.
2. The OrderedResource, via its Mutex, allows the lock as it is the first resource.
3. The client then proceeds to lock additional resources in increasing order; the ResourceList validates each new lock against the highest current resourceID.
4. Once all required resources are locked, the client performs its operations.
5. Finally, the client releases the resources in any order; the ResourceList updates the locked resource IDs accordingly.
This process ensures that all resource acquisitions are performed in a proper ascending order, eliminating the possibility of deadlock.

---

## Commands

### Compile the Code
```bash
gcc -o OrderedLockingPattern.exe OrderedResource.c ResourceList.c ResourceClient.c ...existing code...
```

### Execute the Code
```bash
./OrderedLockingPattern.exe
```

---

## Summary
The Ordered Locking Pattern effectively prevents deadlocks by enforcing an ordered lock acquisition process. By ensuring that resources are always locked in ascending order of their unique resourceIDs, circular waiting cannot occur, thus safeguarding against the deadlock condition.
