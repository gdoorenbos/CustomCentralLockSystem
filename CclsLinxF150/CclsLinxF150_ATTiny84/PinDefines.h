#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

// Power Locks
const int LOCK_CMD_PIN = 9;         // Physical Pin 3
const int UNLOCK_CMD_PIN = 10;      // Physical Pin 2

// Linx RX Module - Data Pins
const int LOCK_REQ_RF_PIN = 1;      // Physical Pin 12
const int UNLOCK_REQ_RF_PIN = 0;    // Physical Pin 13

// push buttons
const int LOCK_REQ_BTN_PIN = 3;     // Physical Pin 10
const int UNLOCK_REQ_BTN_PIN = 2;   // Physical Pin 11

// other pins
// * Arduino Pins 4,5,6 (Physical pins 7,8,9) used for programming
// * Physical Pin 1 is VCC
// * Physical Pin 14 is GND

#endif
