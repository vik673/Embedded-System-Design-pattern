#ifndef OS_TaskSwitching_H
#define OS_TaskSwitching_H

/* OS Abstraction Layer for Critical Region Pattern
 * In a real embedded system, these functions would be provided by the RTOS
 * or implemented using hardware-specific interrupt disable/enable instructions
 */

/* Disable task switching - enters critical region */
void OS_disable_task_switching(void);

/* Enable task switching - exits critical region */
void OS_enable_task_switching(void);

/* Get current task switching state (for debugging/verification) */
int OS_is_task_switching_disabled(void);

#endif
