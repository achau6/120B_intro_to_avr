/*	Author: achau020
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab 2  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "stdbool.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int Addition(int x, int y){
	int z = 0;
	while(y != 0){
		z = (x & y) << 1;
		x = x ^ y;
		y = z;
	}

	return x;
}

int Subtraction(int x, int y){
	int z = 0; // this is carry bit
	y = Addition(~y, 1);
	while(y != 0){
		z = (x & y) << 1;
		x = x ^ y;
		y = z;
	}

	return x;

}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as outputs, initialize to 0s
	DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
        DDRD = 0xFF; PORTD = 0x00;
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpB = 0x00;
	unsigned char tmpD = 0x00;
	
	while(1){
	tmpA = PINA;
	tmpB = PINB;
	tmpC = PINC;
	
	bool overweight = false;
	bool bigDifference = false;
	if(Addition(Addition(tmpA, tmpB), tmpC) >= 0x8C){ //set PD0 to 1
		overweight = true;
	}
	
	if(Subtraction(tmpA, tmpC) >= 0x50){ //set PD1 to 1
		bigDifference = true;
	}	

	tmpD = Addition(Addition(tmpA, tmpB), tmpC);
	tmpD = tmpD >> 2;
	if(overweight == true) {
		tmpD = tmpD | 0x01;
	} else {
		tmpD = tmpD & 0x3E;
	}	
	if(bigDifference == true){
		tmpD = tmpD | 0x02;
	} else {
	  	tmpD = tmpD & 0xFD;
	}
	

	/*if(Addition(Addition(tmpA, tmpB), tmpC) == 0xC0){
                tmpD = Addition(Addition(tmpA, tmpB), tmpC);
		tmpD = tmpD | 0x01;
        } else {
                tmpD = 0x02;
        }*/

	PORTD = tmpD;
	}

    return 0;
}
