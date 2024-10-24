#include <Adafruit_Protomatter.h>

// MatrixPortal ESP32-S3 configuration:
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
  false);      // No double-buffering here (see "doublebuffer" example)

const int WIDTH = 32;
const int HEIGHT = 32;
int Board[HEIGHT][WIDTH] = {0};


void updateMatrix();
void doTurn();
void launchGlider();
int getNeighbors(int row, int column);

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
}

void loop(void) {

  launchGliders();

  for (int i = 0; i < 15; i++) {
  doTurn();
  updateMatrix();
  matrix.show();
  delay(20);
  }
  
  
  
}   

void doTurn() {
    int numNeighbors;
    int tempBoard[HEIGHT][WIDTH] = {0};

    for (int i = 0; i < HEIGHT; i++) { //row
        for(int j = 0; j < WIDTH; j++) { //column
            numNeighbors = getNeighbors(i, j);
            //death (neighbors < 2 || neighbors > 3)
            if (Board[i][j] == 1) { // Alive
                if (numNeighbors == 2 || numNeighbors == 3) {
                  tempBoard[i][j] = 1; 
                } 
            } else { // Dead
                if (numNeighbors == 3) {
                    tempBoard[i][j] = 1;
                } //if cell either doesnt stay alive or become alive, it will be a zero on tempBoard already
            }
          }
        }
          memcpy(Board, tempBoard, sizeof(Board));  //copy tempBoard to Board 
      }
   

  
int getNeighbors(int row, int column) { 
 int neighbors = 0;
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = column - 1; c <= column + 1; c++) {
            if (r == row && c == column) continue; //skip the cell itself
            if ((r > 31 || r < 0) || (c > 31 || c < 0)) continue; //if out of bounds count it dead and continue iterating
            if (Board[r][c] == 1) neighbors++; //if current cell is alive, add 1 to neighbors count
        }
    }
    return neighbors;
}

void updateMatrix() {
        for (int i = 0; i < HEIGHT; i++) { //row
              for(int j = 0; j < WIDTH; j++) { //column
                  if (Board[i][j] == 1) {
                  matrix.drawPixel(j, i, matrix.color565(0, 255, 0)); ;
                 } else {
                  matrix.drawPixel(j, i, matrix.color565(0, 0, 0));
                 }
              }
        }
}

void launchGliders() { //initializes  2 gosper gliders from top corners of matrix
  Board[0][1] = 1;
  Board[1][2] = 1;
  Board[2][0] = 1;
  Board[2][1] = 1;
  Board[2][2] = 1;

  Board[0][31] = 1;
  Board[1][30] = 1;
  Board[2][30] = 1;
  Board[1][29] = 1;
  Board[0][29] = 1;

}