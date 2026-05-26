
#ifndef MOTION_H_
#define MOTION_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include "launchpad.h"
#include <driverlib/gpio.h>



// Handle Interrupts using ISR
static void MotionSensorISR();

// Initialize the PIR motion sensor
void MotionSensorInit();
// Register the callback_event event (if valid)
void MotionSensorEventRegister(Event* callback_event);
// Read the port and pin used by the PIR motion sensor
int ReadMotionSensor();
bool ReadMotionSensorASM();


#endif /* MOTION_H_ */
