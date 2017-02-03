// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
#include <SPI.h>

// SPI Pins
#define USE_SPI_PINS false
#define FEATHER_M0_SPI_SCK_PIN  24
#define FEATHER_M0_SPI_MOSI_PIN 23
#define FEATHER_M0_SPI_MISO_PIN 22

// LED Strip
#define NUMPIXELS 144
#define CLOCKPIN  USE_SPI_PINS ? FEATHER_M0_SPI_SCK_PIN  : 11 // yellow on strip (grey)
#define DATAPIN   USE_SPI_PINS ? FEATHER_M0_SPI_MOSI_PIN : 13 // green on strip (purple)

#if !USE_SPI_PINS
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
#else
// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//       | Board       | SCK | MOSI | MISO |
//       |-------------|-----|------|------|
//       | Feather M0  | 24  | 23   | 22   |
//       | Arduino Uno | 13  | 11   | 12   |
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);
#endif

void setup() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int      head = 0, tail = -10;
uint32_t color = 0xFF0000;

void loop() {
  // Our loop
  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(20);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
}
