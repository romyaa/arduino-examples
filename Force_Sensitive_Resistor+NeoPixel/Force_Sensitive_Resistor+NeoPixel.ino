/* Force Sensitive Resistor (FSR) Variables */
int fsrPin = 0;     // the FSR and 10K pulldown are connected to A0
int fsrReading;     // the analog reading from the FSR resistor divider

/* Neopixel Variables */
#include <Adafruit_NeoPixel.h>
#define LED_PIN    13 // NeoPixel 'DataIn' pin is connected to Arduino pin 13
#define LED_COUNT 8 // the # of NeoPixels on the strip attached to Arduino

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t MAGENTA = strip.Color(255, 0, 160);
uint32_t WHITE = strip.Color(240, 240, 240);
 
void setup(void) {
  Serial.begin(9600);
  strip.begin(); // This initializes the NeoPixel library.
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(5);
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin); 
  Serial.print(fsrReading);     // print the raw analog reading
 
  if (fsrReading < 20) {
    // rainbow
    strip.setPixelColor(0, 204, 0, 1);
    strip.setPixelColor(1, 255, 117, 24);
    strip.setPixelColor(2, 255, 255, 1);
    strip.setPixelColor(3, 1, 204, 0);
    strip.setPixelColor(4, 3, 192, 198);
    strip.setPixelColor(5, 0, 0, 254);
    strip.setPixelColor(6, 75, 0, 130);
    strip.setPixelColor(7, 153 ,50, 204);
  } else if (fsrReading < 125) {
    strip.fill(WHITE, 0, 1);
  } else if (fsrReading < 250) {
    strip.fill(WHITE, 0, 2);
  } else if (fsrReading < 375) {
    strip.fill(WHITE, 0, 3);
  } else if (fsrReading < 500) {
    strip.fill(WHITE, 0, 4);
  } else if (fsrReading < 625) {
    strip.fill(WHITE, 0, 5);
  } else if (fsrReading < 750) {
    strip.fill(WHITE, 0, 6);
  } else if (fsrReading < 875) {
    strip.fill(WHITE, 0, 7);
  } else {
    strip.fill(WHITE, 0, 8);
  }

  delay(10);
  strip.show();
}