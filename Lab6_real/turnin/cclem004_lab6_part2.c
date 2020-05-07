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
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Init, First, SecondThird, Third, SecondFirst, Hold, Reset}state;
void tick();
unsigned char i = 0x00;

int main(void) {
	DDRA = 0x00;
       	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	//unsigned char tmpB = 0x00;
	
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

void tick()
{
	switch(state)
	{
		case Init:
		{

			state = First;
			break;
		}
		case First:
		{ 
			if((~PINA & 0x01) == 0x01 && i == 0x00)
                        {
                                state = Hold;
                        }
			else if ((~PINA & 0x01) == 0x00 && i == 0x01)
			{
				i = 0x00;
				state = SecondThird;
			}
			else
			{
				state = SecondThird;
			}
			break;
		}
		case SecondThird:
		{
			 if((~PINA & 0x01) == 0x01 && i == 0x00)
                        {
                                state = Hold;
                        }
			else if ((~PINA & 0x01) == 0x00 && i == 0x01)
                        {
                                i = 0x00;
				state = Third;
                        }
			else
			{
	
				state = Third;
			 }
			break;
		}
		case Third:
		{
			 if((~PINA & 0x01) == 0x01 && i == 0x00)
                        {
                                state = Hold;
                        }
			 else if ((~PINA & 0x01) == 0x00 && i == 0x01)
                        {
                                i = 0x00;
				state = SecondFirst;
                        }
			else
			{
				state = SecondFirst;
			}
			break;
		}
		case  SecondFirst:
		{ 
			if((~PINA & 0x01) == 0x01 && i == 0x00)
                        {
                                state = Hold;
                        }
			else if ((~PINA & 0x01) == 0x00 && i == 0x01)
                        {
                                i = 0x00;
				state = First;
                        }
			else
			{	
				state = First;
			}
			break;
		}
		case Hold:
		{
			
			if((~PINA & 0x01) == 1)
			{
				state = Hold;
			}
			else
			{
				state = Reset;
			}
			break;
		}
		case Reset:
		{
			if((~PINA & 0x01) == 1)
			{
				i = 0x01;
				state = First;
			}
			else
			{
				state = Reset;
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
		case First:
			PORTB = 0x01;
			break;
		case SecondThird:
			PORTB = 0x02;
			break;
		case Third:
			PORTB = 0x04;
			break;
		case SecondFirst:
			PORTB = 0x02;
			break;
		case Hold:
			break;
		case Reset:
			break;	
		default:
			break;
	}



}
