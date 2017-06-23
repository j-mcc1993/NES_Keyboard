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
	
#define LONG_DELAY  12        // Duration to set latch high
#define SHORT_DELAY 3         // Delay after setting latch high 
#define CLOCK_DELAY 6         // 50% of the clock duty cycle
#define READ_DELAY  16        // Delay between button state sampling

#define CLOCK 5               // Clock pin
#define LATCH 7               // Latch pin
#define DATA 9                // Data pin

#define MASK 0x1

class NES_Keyboard {

	public:

		NES_Keyboard();

		NES_Keyboard(byte c, byte l, byte d);

		void latchData();

		void storeData();

		void readData();

		void setKeys(char input[]);

	private:

		byte clck, latch, data, state;
    
		void pulseClock(void);
};

#endif
