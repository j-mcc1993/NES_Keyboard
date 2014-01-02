/*
	NES_Keyboard.h - A library to control a keyboard with an NES controller.

	*WARNING* This code requires a Leonardo or Micro (NOT DUE!!!)
	(The Due runs on 3.3v and would likely break if you try to run this code)

	Copyright (c) 2014 James P. McCullough. All rights reserved.
*/
#ifndef NES_Keyboard_h
#define NES_Keyboard_h

#include <Arduino.h>

class NES_Keyboard {
	public:
		NES_Keyboard(void);
		NES_Keyboard(byte l, byte p, byte d);
		void latchData(void);
		void writeData(void);
		void readData(void);
		void setKeys(char input[]);
	private:
		void pulseClock(void);
		byte latch, pulse, data, data_byte, tempbit;
};

#endif