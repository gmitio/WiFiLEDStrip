#include "leds.h"

// Define the array of leds
CRGB leds[NUM_LEDS];

void LEDSetup() {
          // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  	  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

unsigned long prev_time = 0; // Holds current time to create delay

void led_chase()  {

  int chase_amnt = 4;

  for(int i=0;i<NUM_LEDS;i=i) {
    if(millis() - prev_time >= 50)
    {
        prev_time = millis();
        i++;
    }
    for(int j=0;j<chase_amnt;j++) {
      leds[i+j] = CRGB::BlueViolet;
    }
    
    FastLED.show();
  
    for(int j=chase_amnt; j>=0; j--)  {
      leds[i+j] = CRGB::Black;
    }
  }
}

/** Rotates through RED, GREEN, then BLUE **/
unsigned long prev_time_1 = 0;
unsigned int cnt = 0;
void steady_rotation()  {
  /** Implement a counter to select the led strip color **/
  if(millis() - prev_time_1 >= 500) {
      prev_time_1 = millis();
      if(cnt < 3)   {
          cnt++;
      }
      else  {
          cnt = 0;
      }
  }
  uint32_t color = 0;   // Init to black
  switch(cnt)   {
      case 0:
        color = CRGB::Red;
        break;
      case 1:
        color = CRGB::Blue;
        break;
      case 2:
        color = CRGB::Green;    
        break;
      case 3:
        color = CRGB::Black;
        break;
      default:
        color = CRGB::Black;
  }
  // Turn the LED on, then pause
  for(int i=0;i<NUM_LEDS;i++){
    leds[i] = color;
  }
  FastLED.show();

}

void steady(uint32_t colorval)
{
    for(int i=0; i<NUM_LEDS;i++)    {
        leds[i] = colorval;
    }
    //fill_rainbow(leds, 40, 100);
    FastLED.show();
}
