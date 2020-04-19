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


enum States{Init, LOCK, FIRSTBUTTON, FIRSTBUTTONRELEASE, SECONDBUTTON,WAIT, UNLOCK}state;
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
			state = WAIT;
			break;
		}
		case WAIT:
		{
			if((PINA & 0x80) == 0x80)
			{
				state = LOCK;
			}
			else if((PINA & 0x07) == 0x04)
			{
				state = FIRSTBUTTON;
			}
			else
			{
				state = WAIT;
			}	
			break;
		}
		case LOCK:
		{
			state = WAIT;
			break;
		}
		
		case FIRSTBUTTON:
		{
			state = FIRSTBUTTONRELEASE;
			break;
		} 
		
		case FIRSTBUTTONRELEASE:
		{
			if((PINA & 0x07) == 0x04)
			{
				state = FIRSTBUTTONRELEASE;
			} 
			else if(PINA  == 0x00)
			{
				state = SECONDBUTTON;
			}
			else
			{
				state = WAIT;
			}

			break;
		}
		case SECONDBUTTON:
		{
			if((PINA & 0x07) == 0x02)
			{
				state = UNLOCK;
			}
			else if (PINA == 0x00)
			{
				state = SECONDBUTTON;
			}
			else
			{
				state = WAIT;
			}
			break;

		}
		case UNLOCK:
		{
			state = WAIT;
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
		case FIRSTBUTTON:
		{
			break;
		}
		case SECONDBUTTON:
		{
			break;
		}
		case UNLOCK:
		{
			if( PORTB == 0x01)
			{
				PORTB = 0x00;
			}
			PORTB = 0x01;
			break;
		}
		case LOCK:
		{	
			PORTB = 0x00;
			break;
		}
		case FIRSTBUTTONRELEASE:
		{	
			break;
		}
		
		default:
		{
			break;
		}
	}
}
    

