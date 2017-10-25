/* Add the following URL to the boards manager to build on the ATTiny2313
 *  
 *  http://drazzy.com/package_drazzy.com_index.json
 *  Obtained from: https://github.com/SpenceKonde/ATTinyCore/blob/master/Installation.md
 *  
 *  Unfortunately could not re-use libraries due to memory constraints of the 2313
 * 
 */

#include "PinDefines.h"

// GENERIC FUNCTIONS

void configure_push_button(const int pin)
{
    pinMode(pin, INPUT_PULLUP);
}

bool is_button_pressed(const int pin)
{
    if( digitalRead(pin) == LOW )
    {
        delay(100);
        return digitalRead(pin) == LOW;
    }
    return false;
}

void configure_lock_driver_pins(const int lock_pin, const int unlock_pin)
{
    // set pin modes
    pinMode(lock_pin, OUTPUT);
    pinMode(unlock_pin, OUTPUT);

    // set pin levels - init low
    digitalWrite(lock_pin, LOW);
    digitalWrite(unlock_pin, LOW);
}

void pulse_lock_driver_pin(const int pin)
{
    digitalWrite(pin, HIGH);
    delay(700);
    digitalWrite(pin, LOW);
}

void turn_on_led(const int pin)
{
    digitalWrite(pin, HIGH);
}

void turn_off_led(const int pin)
{
    digitalWrite(pin, LOW);
}

void blink_led(const int pin, const int period)
{
    turn_on_led(pin);
    delay(period);
    turn_off_led(pin);
}

void configure_led(const int pin)
{
    // set pin mode
    pinMode(pin, OUTPUT);

    // set pin level - init off
    turn_off_led(pin);
}

// SPECIFIC FUNCTIONS

void setup_pins()
{
    // push buttons
    configure_push_button(LOCK_REQ_BTN_PIN);
    configure_push_button(UNLOCK_REQ_BTN_PIN);

    // lock driver pins
    configure_lock_driver_pins(LOCK_CMD_PIN, UNLOCK_CMD_PIN);

    // configure LEDs
    configure_led(RED_LED_PIN);
    configure_led(GREEN_LED_PIN);
}

void led_startup_sequence()
{
    // blink green
    blink_led(GREEN_LED_PIN, 200);
    
    // blink red
    blink_led(RED_LED_PIN, 200);

    // blink both
    turn_on_led(GREEN_LED_PIN);
    turn_on_led(RED_LED_PIN);
    delay(200);
    turn_off_led(GREEN_LED_PIN);
    turn_off_led(RED_LED_PIN);
}

void lock_doors()
{
    pulse_lock_driver_pin(LOCK_CMD_PIN);
}

void unlock_doors()
{
    pulse_lock_driver_pin(UNLOCK_CMD_PIN);
}

void setup()
{
    setup_pins();
    led_startup_sequence();
}

void loop()
{
    if( is_button_pressed(LOCK_REQ_BTN_PIN) )
    {
        lock_doors();
    }
    else if ( is_button_pressed(UNLOCK_REQ_BTN_PIN) )
    {
        unlock_doors();
    }
}

