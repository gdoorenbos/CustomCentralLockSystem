#ifndef ARDUINO_GPIO_HANDLER
#define ARDUINO_GPIO_HANDLER

#include "GpioHandler.h"

class ArduinoGpioHandler : public GpioHandler
{
public:
    ArduinoGpioHandler();
    ~ArduinoGpioHandler();

    void configurePinForOutput(int pin);
    void configurePinForInput(int pin);
};

#endif
