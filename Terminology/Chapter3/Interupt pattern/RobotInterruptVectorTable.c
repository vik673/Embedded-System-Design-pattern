#include "RobotInterruptVectorTable.h"

// Global interrupt vector table
// In a real embedded system, this would be at a specific memory location
ButtonVectorPtr ISRAddress[10];
