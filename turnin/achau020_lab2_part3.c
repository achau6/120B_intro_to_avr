/*	Author: achau020
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab 2  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	//DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char cntavail;
	
	DDRC = 0xFF; PORTC = cntavail; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
        //unsigned char tmpAcopy = 0x00; // Temporary variable to hold the value of A

	while(1) {
		// 1) Read input
		tmpA = PINA & 0x0F;
		// 2) Perform computation

		if (tmpA == ((tmpA & 0xF0) | 0x00)) { // True if BA0 is 1
			tmpC = 0x04;

		} else if (tmpA == ((tmpA & 0xF0) | 0x01)) {
			tmpC = 0x03;
		} else if (tmpA == ((tmpA & 0xF0) | 0x02)) {
                        tmpC = 0x02;
                } else if (tmpA == ((tmpA & 0xF0) | 0x03)) {
                        tmpC = 0x01;
                } else if (tmpA == ((tmpA & 0xF0) | 0x04)) {
                        tmpC = 0x80;
                } else {
			//edge case for something
		}
		// 3) Write output
		
		PORTC = tmpC;	
	}

    return 0;
}
