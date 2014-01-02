#include <NES_Keyboard.h>

//(clock, latch, data) <--- See README.txt in library folder for connector info
NES_Keyboard nes(5,6,7);

void setup() {
  // A-B-Sel-Start-Up-Down-Lt-Rt
  nes.setKeys("abcdefgh"); // <--These keys will be pressed by default
}

void loop() {
  nes.latchData();  // Latch controller data
  nes.storeData();  // Store button states
  nes.readData();   // Read button states + Press keys
}
