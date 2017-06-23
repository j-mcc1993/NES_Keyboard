/*
 * Filename: NES_Keyboard.cpp
 * Author: James McCullough
 * Description: This program encapsulates an interface for controlling NES
 * 		controllers with arduino.
 * !! WARNING !!  This code requires a Leonardo or Micro.  Using a Due may
 * brick your board due its 3.3v requirement.
 *
 * Copyright (c) 2014 James P. McCullough. All rights reserved.
 */

#include "NES_Keyboard.h"

/* Stores true or false indicating whether a button is pressed or not */
boolean isPressed[] = {false, false, false, false, false, false, false, false};

char keys[] = "abcdefgh"; 	/* the keys to be pressed */


/*
 * NES_Keyboard::NES_Keyboard(void);
 *
 * This class handles the serial communication between the arduino and the
 * NES controller.  This code sets the default pins and starts the interaction
 * with the keyboard.
 */
NES_Keyboard::NES_Keyboard() {
  clck = CLOCK;
  latch = LATCH;
  data = DATA;

  pinMode(latch, OUTPUT);
  pinMode(clck, OUTPUT);
  pinMode(data, INPUT);
  
  /* set a clean low signal */
  digitalWrite(latch, LOW); 
  digitalWrite(clck, LOW);

  Keyboard.begin();
}


/*
 * NES_Keyboard::NES_Keyboard(byte p, byte l, byte d);
 *
 * An overloaded constructor to allow users to choose which pins to use.
 */
NES_Keyboard::NES_Keyboard(byte c, byte l, byte d) {
  clck = c;
  latch = l;
  data = d;

  pinMode(latch, OUTPUT);
  pinMode(clck, OUTPUT);
  pinMode(data, INPUT);

  /* set a clean low signal */
  digitalWrite(latch, LOW); 
  digitalWrite(clck, LOW);

  Keyboard.begin();
}


/*
 * void NES_Keyboard::latchData(void);
 *
 * Sends a 12uS high pulse to instruct controller to latch or store its
 * button states internally.
 *
 * No return value.
 */
void NES_Keyboard::latchData() {
  digitalWrite(latch, HIGH);
  delayMicroseconds(LONG_DELAY);

  digitalWrite(latch, LOW);
  delayMicroseconds(SHORT_DELAY);
}


/*
 * void NES_Keyboard::pulseClock(void);
 *
 * Sends a 12uS high pulse to the clock pin with a 50% duty cycle.
 * Each call to this function instructs the controller to respond
 * with a high or low signal on the data line indicated whether
 * the corresponding button was pressed.
 *
 * No return value.
 */
void NES_Keyboard::pulseClock() {
  digitalWrite(clck, HIGH);
  delayMicroseconds(CLOCK_DELAY);

  digitalWrite(clck, LOW);
  delayMicroseconds(SHORT_DELAY);
}


/*
 * void NES_Keyboard::storeData(void);
 *
 * Stores the high and low signals from the data line while pulsing the
 * clock line to obtain button states.
 *
 * No return value.
 */
void NES_Keyboard::storeData(void) {
  state = 0;
  for (int i = 0; i < BYTE_SIZE; i++) {
    if (digitalRead(data) == LOW) {
      state |= (MASK << i);
    }
    pulseClock();
  }
}


/*
 * void NES_Keyboard::readData(void);
 *
 * This function obtains the button states by using a bitmask to obtain
 * the value of each bit in the data_byte.  The controller sends a low
 * pulse when the controller is low, and a high pulse when the button
 * is unpressed.  The isPressed array stores a 1 or 0 to indicate whether
 * a button is currently pressed or not, which will determine whether to
 * press or release that button.
 *
 * No return value.
 */
void NES_Keyboard::readData(void) {
  for (int i = 0; i < BYTE_SIZE; i++) {
    byte currentbit = state & (MASK << i);
    if (currentbit && !isPressed[i]) { 
      isPressed[i] = true;
      Keyboard.press(keys[i]);
    }
    else if (!currentbit && isPressed[i]) {
      isPressed[i] = 0;
      Keyboard.release(keys[i]);
    }
  }

  delay(READ_DELAY);
}


/*
 * void NES_Keyboard::setKeys(void);
 *
 * This function initializes the keys array with a user supplied array to allow
 * for custom keyboard setups.
 *
 * No return value.
 */
void NES_Keyboard::setKeys(char input[]) {
  for (int i = 0; i < BYTE_SIZE; i++) {
    keys[i] = input[i];
  }
}
