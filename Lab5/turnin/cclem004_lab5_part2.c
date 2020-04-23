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


enum States{Init, INCREASE, DECREASE, WAIT, RESET, WAIT2}state;
void tick();

int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF; //input
DDRC = 0xFF; PORTC = 0x00; //output
	//unsigned char button; //, LEDB0, LEDB1;
	//button = 0x00;
	//LEDB0 = 0x00;
	//LEDB1 =0x00;
   /* Insert your solution below */
state = Init;
PORTC = 0x07;
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
			state = WAIT;
			break;
		}
		case WAIT:
		{
			if((~PINA & 0x03) == 0x01)
			{
				state = INCREASE;
			}
			else if((~PINA & 0x03) == 0x02)
			{
				state = DECREASE;
			}
			else if((~PINA & 0x03) == 0x03)
			{
				state = RESET;
			}
			else
			{
				state = WAIT;
			}	
			break;
		}
		case INCREASE:
		{
			state = WAIT2;
			break;
		}
		
		case DECREASE:
		{
			state = WAIT2;
			break;
		} 
		
		case RESET:
		{
			state = WAIT2;
			break;
		}
		case WAIT2:
		{
			if((~PINA & 0x03) == 0x03)
			{
				state = RESET;
			}
			else if((~PINA & 0x03) == 0x01 || ((~PINA & 0x03) == 0x02))
			{
				state = WAIT2;
			}
			else
			{

				state = WAIT;
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

		case WAIT:
		{
			break;					
		}
		case INCREASE:
		{
			if(PORTC < 0x09)
			{
				PORTC = PORTC + 0x01;	
			}
			break;
		}
		case DECREASE:
		{
			if(PORTC > 0x00)
			{
				PORTC = PORTC - 0x01;
			}
			break;
		}
		case RESET:
		{
			PORTC = 0x00;
			break;
		}
		case WAIT2:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}
    

