/* ----------------------------------------------------------------------
"Simple" Protomatter library example sketch (once you get past all
the various pin configurations at the top, and all the comments).
Shows basic use of Adafruit_Protomatter library with different devices.

This example is written for a 64x32 matrix but can be adapted to others.

Once the RGB matrix is initialized, most functions of the Adafruit_GFX
library are available for drawing -- code from other projects that use
LCDs or OLEDs can be easily adapted, or may be insightful for reference.
GFX library is documented here:
https://learn.adafruit.com/adafruit-gfx-graphics-library
------------------------------------------------------------------------- */

#include <Adafruit_Protomatter.h>

/* ----------------------------------------------------------------------
The RGB matrix must be wired to VERY SPECIFIC pins, different for each
microcontroller board. This first section sets that up for a number of
supported boards. Notes have been moved to the bottom of the code.
------------------------------------------------------------------------- */
// MatrixPortal ESP32-S3 configuration:
  uint8_t rgbPins[]  = {42, 41, 40, 38, 39, 37};
  uint8_t addrPins[] = {45, 36, 48, 35, 21};
  uint8_t clockPin   = 2;
  uint8_t latchPin   = 47;
  uint8_t oePin      = 14;


/* ----------------------------------------------------------------------
Okay, here's where the RGB LED matrix is actually declared...

First argument is the matrix width, in pixels. Usually 32 or
64, but might go larger if you're chaining multiple matrices.

Second argument is the "bit depth," which determines color
fidelity, applied to red, green and blue (e.g. "4" here means
4 bits red, 4 green, 4 blue = 2^4 x 2^4 x 2^4 = 4096 colors).
There is a trade-off between bit depth and RAM usage. Most
programs will tend to use either 1 (R,G,B on/off, 8 colors,
best for text, LED sand, etc.) or the maximum of 6 (best for
shaded images...though, because the GFX library was designed
for LCDs, only 5 of those bits are available for red and blue.

Third argument is the number of concurrent (parallel) matrix
outputs. THIS SHOULD ALWAYS BE "1" FOR NOW. Fourth is a uint8_t
array listing six pins: red, green and blue data out for the
top half of the display, and same for bottom half. There are
hard constraints as to which pins can be used -- they must all
be on the same PORT register, ideally all within the same byte
of that PORT.

Fifth argument is the number of "address" (aka row select) pins,
from which the matrix height is inferred. "4" here means four
address lines, matrix height is then (2 x 2^4) = 32 pixels.
16-pixel-tall matrices will have 3 pins here, 32-pixel will have
4, 64-pixel will have 5. Sixth argument is a uint8_t array
listing those pin numbers. No PORT constraints here.

Next three arguments are pin numbers for other RGB matrix
control lines: clock, latch and output enable (active low).
Clock pin MUST be on the same PORT register as RGB data pins
(and ideally in same byte). Other pins have no special rules.

Last argument is a boolean (true/false) to enable double-
buffering for smooth animation (requires 2X the RAM). See the
"doublebuffer" example for a demonstration.
------------------------------------------------------------------------- */

Adafruit_Protomatter matrix(
  32,          // Width of matrix (or matrix chain) in pixels
  4,           // Bit depth, 1-6
  1, rgbPins,  // # of matrix chains, array of 6 RGB pins for each
  4, addrPins, // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin, // Other matrix control pins
  false);      // No double-buffering here (see "doublebuffer" example)

// SETUP - RUNS ONCE AT PROGRAM START --------------------------------------

void setup(void) {
  Serial.begin(9600);

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for(;;);
  }
  matrix.drawTriangle(32, 9, 41, 27, 23, 27, matrix.color565(0, 0, 255));
  matrix.println("HELLO WORLD"); // Default text color is white

  matrix.show(); // Copy data to matrix buffers
}

// LOOP - RUNS REPEATEDLY AFTER SETUP --------------------------------------

void loop(void) {

  delay(1000);
}