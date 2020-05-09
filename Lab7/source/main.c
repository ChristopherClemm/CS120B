/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"

int main(void) {
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	LCD_init();

	LCD_DisplayString(1, "BRUUUUUUUUUUUUUUUUUUHHHH");
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {
	    continue;

    }
    return 1;
}
