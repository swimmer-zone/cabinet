#include <Adafruit_NeoPixel.h>
#include <IRremote.hpp>

#define LED_PIN           6
#define RECV_PIN          10
#define LED_COUNT         300
#define HEXAGON_COUNT     20
#define HEXAGON_LED_COUNT 108
#define TIMEOUT           50

#define C_PURPLE  strip.Color( 92,  94, 220)
#define C_RED     strip.Color(255,   0,   0)
#define C_YELLOW  strip.Color(255, 255,   0)
#define C_GREEN   strip.Color(  0, 255,   0)
#define C_CYAN    strip.Color(  0, 255, 255)
#define C_BLUE    strip.Color(  0,   0, 255)
#define C_MAGENTA strip.Color(255,   0, 255)

// Stuff for remote
int Program = 0;
int maxProgram = 2;
int Horizontal = 0;
int Vertical = 0;
int Brightness = 50;
bool Active = false;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); //  bitstream (most NeoPixel products w/WS2812 LEDs)

// Runs once at startup
void setup() {
  Serial.begin(9600);
  Serial.println('Arduino is set up!');
  IrReceiver.begin(RECV_PIN, true);
  
  strip.begin();
  show(); // Turn OFF all pixels
  strip.setBrightness(50);
}


// Runs repeatedly
void loop() {
//  if (IrReceiver.decode()) {
//    uint32_t myRawdata = IrReceiver.decodedIRData.decodedRawData;
//    // Serial.println(myRawdata, HEX);
    
//    RM_translate(myRawdata);
//    IrReceiver.resume();
//  }

  FX_hexCircle(C_PURPLE,  TIMEOUT);
  FX_hexCircle(C_RED,     TIMEOUT);
  FX_hexCircle(C_YELLOW,  TIMEOUT);
//  FX_hexCircle(C_GREEN,   TIMEOUT);
//  FX_hexCircle(C_CYAN,    TIMEOUT);
//  FX_hexCircle(C_BLUE,    TIMEOUT);
//  FX_hexCircle(C_MAGENTA, TIMEOUT);
  
//  FX_colorWipeMulti(C_PURPLE,  10, TIMEOUT);
//  FX_colorWipeMulti(C_RED,     20, TIMEOUT);
//  FX_colorWipeMulti(C_YELLOW,  30, TIMEOUT);
//  FX_colorWipeMulti(C_GREEN,   40, TIMEOUT);
//  FX_colorWipeMulti(C_CYAN,    50, TIMEOUT);
//  FX_colorWipeMulti(C_BLUE,    60, TIMEOUT);
//  FX_colorWipeMulti(C_MAGENTA, 70, TIMEOUT);
}

void show() {
  if (IrReceiver.isIdle()) {
    strip.show();
  }
}

void FX_hexCircle(uint32_t color, int wait) {
  for (int j = 0; j < HEXAGON_LED_COUNT; j++) {
    for (int i = 0; i < strip.numPixels(); i+=HEXAGON_LED_COUNT) {
      strip.setPixelColor(i + j, color);
      strip.setPixelColor(i + j -5, strip.Color(0, 0, 0));
    }
    show();
    delay(wait);
  }
}

void FX_colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    show();
    delay(wait);
  }
}

void FX_colorWipeMulti(uint32_t color, int pixels, int wait) {
  for (int i = 0; i < strip.numPixels(); i += pixels) {
    for (int j = 0; j < pixels; j++) {
      strip.setPixelColor(i + j, color);
    }
    show();
    delay(wait);
  }
}

void FX_rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    show();
    delay(wait);
  }
}


void RM_translate(uint32_t signal) {
  // Pioneer Remote
  // Stop signal: 66995CA3

  
  switch(signal) {
    case 0x5EA150AF:
      Program = 1;
      Serial.println("Each hexagon is turning on one by one");
      Serial.println("- use < and > to control the color");
      strip.clear();
      Active = true;
    break;

    case 0x5DA250AF:
      Program = 2;
      Serial.println("Each hexagon starts circling around");
      Serial.println("- use < and > to control the amount of lit LEDs");
      Serial.println("- use UP and DOWN to control the speed");
      strip.clear();
      Active = true;
    break;

    case 0x5CA350AF:
      Program = 3;
      Serial.println("Each hexagon fils up");
      Serial.println("- use UP and DOWN to control the speed");
      strip.clear();
      Active = true;
    break;

    case 0x5BA450AF:
      Program = 4;
      Serial.println("Everything is quite dim but with a motion sensor a single hexagon can light up if I come close");
      Serial.println("- use < and > to control the color");
      strip.clear();
      Active = true;
    break;

    case 0x5AA550AF:
      Program = 5;
      Serial.println("All off, except when approached");
      Serial.println("- use < and > to control the color");
    break;

    case 0x59A650AF:
      Program = 6;
      Serial.println("Circle around 6 hexagons");
      Serial.println("- use < and > to control the color");
      Serial.println("- use UP and DOWN to control the speed");
      strip.clear();
      Active = true;
    break;

    case 0x58A750AF:
      Program = 7;
      Serial.println("Light up certain hexagons");
      Serial.println("- use arrows to pick which");
      strip.clear();
      Active = true;
    break;

    case 0x57A850AF:
      Program = 8;
      Serial.println("Equalizer");
      strip.clear();
      Active = true;
    break;

    case 0x56A950AF:
      Program = 9;
      Serial.println("Ableton with Max4Live control");
      strip.clear();
      Active = true;
    break;
    
    case 0x5FA050AF:
      Program = 0;
      Serial.println("TBD");
      strip.clear();
      Active = true;
    break;

    case 0xDF250AF: // up
      RM_move(0);
      Serial.println("Vertical: " + Vertical);
      strip.clear();
      Active = true;
    break;
    
    case 0x9B6450AF: // right
      RM_move(1);
      Serial.println("Horizontal: " + Horizontal);
      strip.clear();
      Active = true;
    break;
    
    case 0xCF350AF: // down
      RM_move(2);
      Serial.println("Vertical: " + Vertical);
      strip.clear();
      Active = true;
    break;
    
    case 0x9C6350AF: // left
      RM_move(3);
      Serial.println("Horizontal: " + Horizontal);
      strip.clear();
      Active = true;
    break;
    
    case 0x10EF50AF: // enter
    break;

    case 0xF50A5AA5: // volume up
      RM_brightness(1);
      Serial.println("Brightness: " + Brightness);
    break;
    
    case 0xF40B5AA5: // volume down
      RM_brightness(0);
      Serial.println("Brightness: " + Brightness);
    break;

    case 0x1CE350AF: // disp
    break;
    
    case 0x1AE550AF: // clr
      strip.clear();
      Active = false;
      break;

    default: // Other button
    break;
  }
}

void RM_move(int direction) {
  switch (direction) {
    case 0:
      if (Vertical < 100) Vertical += 10;
      break;
    case 1:
      if (Horizontal < 100) Horizontal += 10;
      break;
    case 2:
      if (Vertical > 0) Vertical -= 10;
      break;
    case 3:
      if (Horizontal > 0) Horizontal -= 10;
      break;
  }
}

void RM_brightness(int direction) {
  switch (direction) {
    case 1:
      if (Brightness < 250) Brightness += 25;
      break;
    case 0:
      if (Brightness > 25) Brightness -= 25;
      break;
  }
  strip.setBrightness(Brightness);
}
