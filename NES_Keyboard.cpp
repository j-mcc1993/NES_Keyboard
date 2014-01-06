/*
  NES_Keyboard.h - A library to control a keyboard with an NES controller.

  *WARNING* This code requires a Leonardo or Micro (NOT DUE!!!)
  (The Due runs on 3.3v and would likely break if you try to run this code)

  Copyright (c) 2014 James P. McCullough. All rights reserved.
*/
#include "NES_Keyboard.h"
#include <Arduino.h>  

//stores 1 or 0 indicating whether a button is pressed or not
byte count[] = {0,0,0,0,0,0,0,0}; 
char keys[] = "abcdefgh"; //the keys to be pressed

NES_Keyboard::NES_Keyboard(void) {
  pulse = 5;
  latch = 7;
  data = 9;

  pinMode(latch, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(data, INPUT);
  //set a clean low signal
  digitalWrite(latch, LOW); 
  digitalWrite(pulse, LOW);
}

NES_Keyboard::NES_Keyboard(byte p, byte l, byte d) {
  pulse = p;
  latch = l;
  data = d;

  pinMode(latch, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(data, INPUT);
  digitalWrite(latch, LOW); 
  digitalWrite(pulse, LOW);
}

//tells controller to latch data by sending 12uS pulse on latch pin
void NES_Keyboard::latchData(void) {
  digitalWrite(latch, HIGH);
  delayMicroseconds(12);
  digitalWrite(latch, LOW);
  delayMicroseconds(6);
}

//shifts data from controller by pulsing clock pin
void NES_Keyboard::pulseClock(void) {
  digitalWrite(pulse, HIGH);
  delayMicroseconds(5);

  digitalWrite(pulse, LOW);
  delayMicroseconds(5);
}

<<<<<<< HEAD
=======
//stores data from controller to be iterated through
>>>>>>> Added Comments
void NES_Keyboard::storeData(void) {
  data_byte = 0;
  for (int i = 0; i < 8; i++) {
    data_byte = data_byte | (digitalRead(data) << i);
    pulseClock();
  }
}

//iterates through data and presses appropiate keys
void NES_Keyboard::readData(void) {
  for (int i = 0; i < 8; i++) {
    tempbit = bitRead(data_byte, i);
    if (tempbit == 0 && count[i] == 0) { 
      count[i] = 1;
      Keyboard.press(keys[i]);
    }
    else if (tempbit == 1 && count[i] == 1) {
      count[i] = 0;
      Keyboard.release(keys[i]);
    }
  }
  delay(16);
}

//set which keys to be pressed
void NES_Keyboard::setKeys(char input[]) {
	for (int i = 0; i < 8; i++) {
		keys[i] = input[i];
	}
}