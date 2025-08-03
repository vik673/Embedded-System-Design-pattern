# Simultaneous Locking Pattern

## Overview
The **Simultaneous Locking Pattern** is designed to prevent deadlock by breaking the hold-and-wait condition. It ensures that either all required resources are locked at once or none are locked. This all-or-none approach helps avoid scenarios where a task holds some resources while waiting for others, thereby eliminating circular waiting.

## Abstract
Deadlock is prevented by ensuring that if a task cannot lock all necessary resources simultaneously, it will not lock any. This pattern is particularly useful for systems that require multiple resources to be acquired as a set, thus allowing higher priority tasks that do not need these resources to run without undue delay.

## Problem
Deadlock can occur when tasks hold certain resources while waiting for additional ones that are currently unavailable. By only granting a lock when all required resources can be simultaneously acquired, the Simultaneous Locking Pattern avoids this problematic condition (#2: hold and wait).

## Pattern Structure
The structure of the pattern typically involves:
- **MultimasteredResource:** Shared resources that may be part of multiple resource sets and require individual mutexes (with support for tryLock()).
- **ResourceMaster:** An entity that manages the locking of an entire set of resources. In the general case, it attempts to lock each resource using tryLock(); if any lock attempt fails, it releases all already acquired locks.
- **ResourceMasterSimplified:** A simplified version where each resource belongs exclusively to one resource group. This version does not require the tryLock() functionality, as it can use a single mutex to protect the grouped resources.
- **Mutex / QueryMutex:** The locking mechanism used to protect individual resources. In the general case, QueryMutex provides a tryLock() function that allows the ResourceMaster to test resource availability without blocking.
- **ResourceClient:** The client or task that tries to access a set of resources through the ResourceMaster. The ResourceClient must request all resources simultaneously and only proceeds if the lock is successful on all.

## Collaboration Roles
- **MasteredResource / MultimasteredResource:** Represents a resource that may be shared by multiple resource groups. When multiple ResourceMasters manage such resources, each resource requires its own mutex to support tryLock().
- **ResourceMaster:** Manages a set of MultimasteredResources. It attempts to lock all resources in the set and, on failure, releases any locks already acquired.
- **ResourceMasterSimplified:** In a scenario where resources are exclusively owned by a single manager, this simplified version locks and releases all resources using a single mutex.
- **ResourceClient:** Uses the services provided by the ResourceMaster (or ResourceMasterSimplified) to access the resources. It must only proceed when the ResourceMaster confirms that all required locks have been acquired.

## Implementation Strategies and Consequences
- The pattern requires careful assignment of unique resourceIDs, ideally at design time, to enforce the global ordering of resource locks.
- While effective at eliminating deadlock, the pattern may introduce delays because resources are only granted if all are immediately available.
- Priority inversion can worsen unless combined with additional techniques such as priority inheritance.
- Developer discipline is crucial in the general case; improper handling of resource locks can lead to subtle errors.

## Example Workflow
1. A ResourceClient requests to lock a set of resources.
2. The ResourceMaster (or ResourceMasterSimplified) attempts to lock each resource:
   - For the general case, it uses the tryLock() method on each MultimasteredResource.
   - If all locks are acquired, the client is allowed to proceed.
   - If any lock attempt fails, the ResourceMaster releases all acquired locks and returns an error.
3. Upon successful locking, the ResourceClient performs its operations and then releases the locks.

## Commands
```bash
gcc -o SimultaneousLockingPattern.exe MultimasteredResource.c ResourceMaster.c ResourceClient.c ...existing code...
./SimultaneousLockingPattern.exe
```

## Summary
The Simultaneous Locking Pattern prevents deadlock by ensuring that a task can only proceed if all required resources can be locked simultaneously. This eliminates the hold-and-wait condition and consequently the possibility of circular wait, though it may increase task delay and complicate priority handling.