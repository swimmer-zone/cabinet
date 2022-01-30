// See README.md for more info

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define LED_PIN           6
#define LED_COUNT         324
#define HEXAGON_COUNT     20
#define HEXAGON_LED_COUNT 108
#define BRIGHTNESS        50 // Max 255
#define TIMEOUT           50

#define C_PURPLE  strip.Color( 92,  94, 220)
#define C_RED     strip.Color(255,   0,   0)
#define C_YELLOW  strip.Color(255, 255,   0)
#define C_GREEN   strip.Color(  0, 255,   0)
#define C_CYAN    strip.Color(  0, 255, 255)
#define C_BLUE    strip.Color(  0,   0, 255)
#define C_MAGENTA strip.Color(255,   0, 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); //  bitstream (most NeoPixel products w/WS2812 LEDs)


// Runs once at startup
void setup() {
  strip.begin();
  strip.show(); // Turn OFF all pixels
  strip.setBrightness(255);
}


// Runs repeatedly
void loop() {
  hexCircle(C_PURPLE,  TIMEOUT);
  hexCircle(C_RED,     TIMEOUT);
  hexCircle(C_YELLOW,  TIMEOUT);
  hexCircle(C_GREEN,   TIMEOUT);
  hexCircle(C_CYAN,    TIMEOUT);
  hexCircle(C_BLUE,    TIMEOUT);
  hexCircle(C_MAGENTA, TIMEOUT);
  
//  colorWipeMulti(C_PURPLE,  10, TIMEOUT);
//  colorWipeMulti(C_RED,     20, TIMEOUT);
//  colorWipeMulti(C_YELLOW,  30, TIMEOUT);
//  colorWipeMulti(C_GREEN,   40, TIMEOUT);
//  colorWipeMulti(C_CYAN,    50, TIMEOUT);
//  colorWipeMulti(C_BLUE,    60, TIMEOUT);
//  colorWipeMulti(C_MAGENTA, 70, TIMEOUT);
}

void hexCircle(uint32_t color, int wait) {
  for (int j = 0; j < HEXAGON_LED_COUNT; j++) {
    for (int i = 0; i < strip.numPixels(); i+=HEXAGON_LED_COUNT) {
      strip.setPixelColor(i + j, color);
    }
      strip.show();
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void colorWipeMulti(uint32_t color, int pixels, int wait) {
  for (int i = 0; i < strip.numPixels(); i += pixels) {
    for (int j = 0; j < pixels; j++) {
      strip.setPixelColor(i + j, color);
    }
    strip.show();
    delay(wait);
  }
}

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show();
    delay(wait);
  }
}
