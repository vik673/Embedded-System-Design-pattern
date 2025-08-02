#include "OS_TaskSwitching.h"
#include <stdio.h>

/* Mock implementation for demonstration purposes
 * In a real embedded system, these would be RTOS-specific calls
 * or assembly language instructions to disable/enable interrupts
 */

static int task_switching_disabled = 0;
static int critical_region_count = 0;

void OS_disable_task_switching(void) {
    critical_region_count++;
    
    if (!task_switching_disabled) {
        task_switching_disabled = 1;
        printf("[OS] Task switching DISABLED (count: %d)\n", critical_region_count);
        
        /* In a real system, this might be:
         * 
         * For RTOS-based approach:
         * vTaskSuspendAll();  // FreeRTOS
         * or
         * OSSchedLock();      // uC/OS
         * 
         * For hardware interrupt approach:
         * __asm volatile ("cpsid i" : : : "memory");  // ARM Cortex-M
         * or
         * __disable_irq();    // Using CMSIS
         */
    } else {
        printf("[OS] Task switching already disabled (nested count: %d)\n", critical_region_count);
    }
}

void OS_enable_task_switching(void) {
    if (critical_region_count > 0) {
        critical_region_count--;
    }
    
    if (task_switching_disabled && critical_region_count == 0) {
        task_switching_disabled = 0;
        printf("[OS] Task switching ENABLED (count: %d)\n", critical_region_count);
        
        /* In a real system, this might be:
         * 
         * For RTOS-based approach:
         * xTaskResumeAll();   // FreeRTOS
         * or
         * OSSchedUnlock();    // uC/OS
         * 
         * For hardware interrupt approach:
         * __asm volatile ("cpsie i" : : : "memory");  // ARM Cortex-M
         * or
         * __enable_irq();     // Using CMSIS
         */
    } else if (critical_region_count > 0) {
        printf("[OS] Task switching remains disabled (nested count: %d)\n", critical_region_count);
    } else {
        printf("[OS] Warning: Attempt to enable task switching when not disabled!\n");
    }
}

int OS_is_task_switching_disabled(void) {
    return task_switching_disabled;
}
