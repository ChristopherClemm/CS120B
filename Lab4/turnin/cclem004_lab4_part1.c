/*	Author: cclem004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{Init, LED1ON, LED2ON}state;
void tick();

int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF; //input
DDRB = 0xFF; PORTB = 0x00; //output
	//unsigned char button; //, LEDB0, LEDB1;
	//button = 0x00;
	//LEDB0 = 0x00;
	//LEDB1 =0x00;
   /* Insert your solution below */
state = Init;
PORTB = 0x00;
while(1)
{
	tick();

}
	return 1;
}
   
void tick()
{	
	switch(state)
	{
		case Init:
		{
			state = LED1ON;
			break;
		}
		case LED1ON:
			if((PINA & 0x01) == 0x01)
			{
				state = LED2ON;
			}
			else
			{
				state = LED1ON;
			}	
			break;
		
		case LED2ON:
		{
			if((PINA & 0x01) == 0x01)
			{
			
				state = LED1ON;
			}
			else
			{
				state = LED2ON;
			}
			break;
		}
		default:
		{
			state = Init;
			break;
		}
	}

	switch(state)
	{
		case Init:
			break;

		case LED1ON:
		{
			PORTB = 0x01;
			break;					
		}
		case LED2ON:
		{
			PORTB = 0x02;
			break;
		}
		default:
		{
			break;
		}
	}
}
    

