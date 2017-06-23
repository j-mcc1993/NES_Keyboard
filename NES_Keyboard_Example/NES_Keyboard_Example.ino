#include <NES_Keyboard.h>

NES_Keyboard nes;

// Clock, Latch and Data are pins 5,7, and 9 by default
void setup() {}

//A-B-Select-Start-Up-Down-Left-Right
//a-b-c-d-e-f-g-h <--- Pressed on keyboard by default
void loop() {
  nes.latchData();  // Latch controller data
  nes.storeData();  // Store button states
  nes.readData();   // Read button states + Press keys
}
