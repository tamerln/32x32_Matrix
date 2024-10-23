#include <Adafruit_Protomatter.h>

// MatrixPortal ESP32-S3 pins
  uint8_t rgbPins[]  = {42, 41, 40, 38, 39, 37};
  uint8_t addrPins[] = {45, 36, 48, 35, 21};
  uint8_t clockPin   = 2;
  uint8_t latchPin   = 47;
  uint8_t oePin      = 14;

Adafruit_Protomatter matrix(
  32,          // Width of matrix (or matrix chain) in pixels
  4,           // Bit depth, 1-6
  1, rgbPins,  // # of matrix chains, array of 6 RGB pins for each
  4, addrPins, // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin, // Other matrix control pins
  false);      // No double-buffering here 

int currWidth;
int startX = matrix.height()/2;
int startY = matrix.width()/2;

void setup(void) {
  Serial.begin(9600);
//initialize matrix
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for(;;);
  }

}

void loop(void) {
  swirl(10, 255, 200);
  swirl(0, 0, 0);
}
void swirl(int red, int green, int blue) { ;//draws a swirl on a 32x32 matrix in whatever color is passed 
    currWidth = 0;
    int x = startX;
    int y = startY;
    matrix.drawPixel(x, y, matrix.color565(red, green, blue));
    matrix.show();
    do {
    currWidth++;

    for (int i = currWidth; i > 0; i--) {
    //draw currWidth pixels left
    x--; //x = x-1 (left)
    matrix.drawPixel(x, y, matrix.color565(red, green, blue));
    matrix.show();
    delay(10);
    }

       for (int i = currWidth; i > 0; i--) {
    //draw currWidth pixels up
    y--; //x = x-1 (up)
    matrix.drawPixel(x, y, matrix.color565(red, green, blue));
    matrix.show();
    delay(10);
    }

    currWidth++;

       for (int i = currWidth; i > 0; i--) {
    //draw currWidth pixels right
    x++; //x = x+1 (right)
    matrix.drawPixel(x, y, matrix.color565(red, green, blue));
    matrix.show();
    delay(10);
    }

     for (int i = currWidth; i > 0; i--) {
    //draw currWidth pixels down
    y++; //y = y+1 (down)
    matrix.drawPixel(x, y, matrix.color565(red, green, blue));
    matrix.show();
    delay(10);
    }


  } while (currWidth < matrix.width());

}
