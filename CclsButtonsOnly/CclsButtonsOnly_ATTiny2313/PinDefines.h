#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

// Power Locks
const int LOCK_CMD_PIN = 9;         // Physical Pin 4
const int UNLOCK_CMD_PIN = 10;      // Physical Pin 5

// push buttons
const int LOCK_REQ_BTN_PIN = 3;     // Physical Pin 11
const int UNLOCK_REQ_BTN_PIN = 2;   // Physical Pin 12

// LEDs
const int RED_LED_PIN = 0;          // Physical Pin 2
const int GREEN_LED_PIN = 1;        // Physical Pin 3

// other pins
// * Arduino Pins 14,15,16,17 (Physical pins 17,18,19,1) used for programming
// * Physical Pin 20 is VCC
// * Physical Pin 10 is GND

#endif
