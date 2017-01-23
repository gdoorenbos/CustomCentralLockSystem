#ifndef ARDUINO_OUTPUT_PIN_H
#define ARDUINO_OUTPUT_PIN_H

class ArduinoOutputPin : public GenericOutputPin
{
public:
    ArduinoOutputPin(int pin);
    ~ArduinoOutputPin();

private:
    // intentionally not implemented
    ArduinoOutputPin();
};

#endif
