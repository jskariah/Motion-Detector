# Embedded Motion Detection Alarm

## Overview

This project is an embedded motion detection alarm built for the TM4C/Tiva C LaunchPad. The system uses a PIR motion sensor, buzzer, push buttons, and LED indicators to create an interrupt-driven alarm system.

## Features

- PIR motion sensor detection
- Push-button alarm activation and deactivation
- Buzzer alarm output
- RGB LED status indicators
- GPIO interrupt handling
- Event-driven callback scheduling
- ARM assembly helper functions
- Embedded C system state management

## Hardware Used

- TM4C/Tiva C LaunchPad
- PIR motion sensor
- Grove buzzer
- On-board push buttons
- On-board RGB LED

## Hardware Connections

| Component | Connection |
|---|---|
| Buzzer | Grove J17 |
| Buzzer Signal | GPIO PC5 |
| Motion Sensor | GPIO PC4 |
| SW1 Button | GPIO PF4 |
| SW2 Button | GPIO PF0 |
| RGB LED | On-board LaunchPad LED |

## System Behavior

The alarm system has three main states:

| State | Description |
|---|---|
| Inactive | Alarm is off and motion is ignored |
| Active | Alarm is armed and waiting for motion |
| Alerted | Motion has been detected and the buzzer alarm is active |

## User Controls

| Input | Action |
|---|---|
| SW1 | Activates the alarm system |
| SW2 | Deactivates the alarm system |
| Motion Sensor | Triggers alert state when motion is detected |

## LED Status

| LED Output | Meaning |
|---|---|
| Red LED | Motion detected / alert active |
| Green LED | System active but no motion detected |
| Off | System inactive |

## Project Structure

```text
Embedded-Motion-Alarm/
├── lab5_main.c
├── buzzer.c
├── buzzer.h
├── buzzer_asm.asm
├── motion.c
├── motion.h
├── motion_asm.asm
├── pushbutton.c
├── tm4c123gh6pm_startup_ccs.c
├── tm4c123gh6pm.cmd
└── README.md
```

## File Descriptions

| File | Description |
|---|---|
| `lab5_main.c` | Main alarm logic, system state, event scheduling, button handling, and motion response |
| `buzzer.c` | Initializes the buzzer GPIO pin |
| `buzzer.h` | Header file for buzzer functions |
| `buzzer_asm.asm` | ARM assembly functions for turning the buzzer on and off |
| `motion.c` | Initializes the motion sensor and handles motion sensor interrupts |
| `motion.h` | Header file for motion sensor functions |
| `motion_asm.asm` | ARM assembly helper for reading motion sensor state |
| `pushbutton.c` | Push-button interrupt reference implementation |
| `tm4c123gh6pm_startup_ccs.c` | Startup code for the TM4C123GH6PM microcontroller |
| `tm4c123gh6pm.cmd` | Linker command file for Code Composer Studio |

## How It Works

The system uses an event-driven structure instead of continuously polling all hardware inputs.

The program flow is:

1. Initialize the LaunchPad, buzzer, and motion sensor.
2. Register push-button and motion sensor events.
3. Wait for hardware interrupts.
4. Execute scheduled event callbacks.
5. Update the alarm state based on button and motion sensor input.
6. Turn the buzzer and LEDs on or off depending on the system state.

## Alarm Logic

When the system is inactive, motion is ignored.

When SW1 is pressed, the system becomes active. Once active, the motion sensor determines whether the system should be alerted.

If motion is detected:

- The red LED turns on.
- The system enters the alerted state.
- The buzzer begins beeping.

If no motion is detected:

- The green LED turns on.
- The system remains active but not alerted.

When SW2 is pressed:

- The system is deactivated.
- The alert state is cleared.
- The buzzer is turned off.
- The LED is turned off.

## Buzzer Control

The buzzer is connected to GPIO PC5. The project uses ARM assembly functions to turn the buzzer on and off by writing directly to the GPIO pin through TivaWare calls.

The buzzer beeps periodically when the system is alerted. This is handled through a scheduled event that alternates the buzzer between on and off states.

## Motion Sensor

The PIR motion sensor is connected to GPIO PC4. The motion sensor is configured as a GPIO input with interrupts enabled on both rising and falling edges.

When the motion sensor changes state, an interrupt schedules a callback event. The callback then checks whether motion was detected and updates the alarm state.

## ARM Assembly Components

This project includes ARM assembly routines for low-level hardware interaction.

Assembly was used for:

- Turning the buzzer on
- Turning the buzzer off
- Reading the stored motion sensor input state

## How to Build and Run

This project is intended to be built and flashed using Texas Instruments Code Composer Studio.

General steps:

1. Open Code Composer Studio.
2. Import the project into the workspace.
3. Connect the TM4C/Tiva C LaunchPad.
4. Connect the PIR motion sensor and buzzer.
5. Build the project.
6. Flash the program to the board.
7. Use SW1 to activate the alarm and SW2 to deactivate it.

## What I Learned

Through this lab, I practiced:

- Embedded C programming
- GPIO input and output
- GPIO interrupt configuration
- PIR motion sensor integration
- Push-button interrupt handling
- Event-driven embedded system design
- Buzzer control
- RGB LED status output
- ARM assembly integration
- Hardware/software debugging on a microcontroller

## Future Improvements

Potential future improvements include:

- Adding a 7-segment or LCD display for system status
- Adding adjustable buzzer patterns
- Adding debounce handling for motion sensor changes
- Adding a delay before arming the system
- Adding a password or button sequence to deactivate the alarm
- Adding a battery-powered enclosure
- Adding a wiring diagram and demo video

## Author

Created by Justin Skariah.

Developed for ECE 266.
