/*	Author: Christopher Clemm4
 *  Partner(s) Name: NA
 *	Lab Section:23
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
	//DDRC = 0xFF; PORTC = 0x00; //output
	
	enum States{Init, LED1ON, LED2ON}state;

	//unsigned char button, LEDB0, LEDB1;
	//button = 0x00;
	//LEDB0 = 0x00;
	//LEDB1 =0x00;

	while(1)
	{
	//	button = PINA;
	
		switch(state)
		{

			case Init: 
			{
				state = LED1ON;
				break;
			}
			case LED1ON:
			{
				if((PINA & 0x01 ) == 0x01)
				{
					state = LED1ON;
				}	
				else
				{
					state = LED2ON;
				}
				break;
			}
			case LED2ON:
			{
				if((PINA & 0x01) == 0x00)
				{
					state = LED2ON;
				}
				else
				{
					state = LED1ON;		
				}
				break;
			}
			default:
			{
				state = Init;
				break;
			}
		}

			 


	}
	
    /* Insert DDR and PORT initializations */
	
    /* Insert your solution below */
    
	
    
    return 1;
}
