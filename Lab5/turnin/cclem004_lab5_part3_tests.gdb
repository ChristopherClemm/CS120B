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


enum States{Init, NEXTSTATE, WAIT, WAIT2}state;
void tick();
unsigned char array[14] = {0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00};
unsigned char i = 0x00;

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
PORTC = 0x01;
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
			if((~PINA & 0x01) == 0x01)
			{
				state = NEXTSTATE;
			}
			else
			{
				state = WAIT;
			}	
			break;
		}
		case NEXTSTATE:
		{
			if((~PINA & 0x01) == 0x01)
			{
				state = WAIT2;
			}
			else
			{	
			state = WAIT;
			}
			break;
		}
		case WAIT2:
		{
			if((~PINA & 0x01) == 0x01)
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
		case NEXTSTATE:
		{
			i++;
			if(i > 13)
			{
				i = 0;
			}
			PORTC = array[i];
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
    

