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
 
#ifndef NES_Keyboard_h
#define NES_Keyboard_h

#include <Arduino.h>
#include <Keyboard.h>

#define BYTE_SIZE 8
	
#define LATCH_PULSE 12
#define LATCH_DELAY 6
#define PULSE_DELAY 6
#define READ_DELAY 16

#define PULSE 5
#define LATCH 7
#define DATA 9

class NES_Keyboard {
	public:
		NES_Keyboard(void);
		NES_Keyboard(byte l, byte p, byte d);
		void latchData(void);
		void storeData(void);
		void readData(void);
		void setKeys(char input[]);
	private:
		void pulseClock(void);
		byte latch, pulse, data, data_byte, currentbit, mask;
};

#endif
