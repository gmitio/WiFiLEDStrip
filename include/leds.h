#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 96

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 23
#define CLOCK_PIN 22

/** Function Declarations **/
void LEDSetup(void);
void led_chase(void);           // Pattern
void steady_rotation(void);     // Pattern
void steady(uint32_t colorval);