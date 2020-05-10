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
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Init, First, SecondThird, Third, SecondFirst, Hold, Reset}state;
void tick();
unsigned char i = 0x00;
unsigned char score = 0x05;
unsigned char win = 0x00;
unsigned char gameWon = 0x00;
unsigned char stopCount = 0x00;
int main(void) {
	DDRA = 0x00;
       	PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(300);
	TimerOn();

	LCD_init();
	LCD_WriteData(score + '0');
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
				win = 0x00;
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
				win = 0x01;
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
				win = 0x00;
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
				win = 0x01;
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
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
			gameWon = 0x00;
			PORTB = 0x01;
			stopCount = 0x00;
			break;
		case SecondThird:
			PORTB = 0x02;
			stopCount = 0x00;
			break;
		case Third:
			PORTB = 0x04;
			stopCount = 0x00;
			break;
		case SecondFirst:
			stopCount = 0x00;
			PORTB = 0x02;
			break;
		case Hold:
			if(stopCount == 0x00)
			{
				stopCount = 0x01;
				LCD_ClearScreen();
				if(win == 0x01)
				{
					 if(score < 0x08)
					{
						score = score + 0x01;
						LCD_WriteData(score + '0');
					}
					else
					{
						gameWon = 0x01;
						LCD_DisplayString(1,"WINNER!!!!");
						score = 0x05;
					}
				}
				else
				{
					if(score > 0x00)
					{
						score = score - 0x01;
					}
				
					LCD_WriteData(score + '0');
				}
			}
			break;
		case Reset:
			LCD_ClearScreen();
			if(gameWon == 0x01)
			{
				LCD_DisplayString(1,"WINNER!!!!");
			}
			else
			{
				LCD_WriteData(score + '0');
			}
			break;	
		default:
			break;
	}



}
