// DEMO LINK: https://drive.google.com/open?id=1X-qm5kfKp4ExGr_LkTcBv4tOzAD68KCo
/*	Author: Christopher Clemm
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab # 5 Exercise #2
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


enum States{Init, INCREASE, DECREASE, WAIT, RESET, WAIT2}state;
void tick();
unsigned char i = 0x00;
unsigned char b = 0x00;
int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF; //input
DDRC = 0xFF; PORTC = 0x00; //output
DDRD = 0xFF; PORTD = 0x00; //output
	//unsigned char button; //, LEDB0, LEDB1;
	//button = 0x00;
	//LEDB0 = 0x00;
	//LEDB1 =0x00;
   /* Insert your solution below */
state = Init;

LCD_init();

LCD_WriteData(0 + '0');
TimerSet(100);
TimerOn();

while(1)
{
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
			state = WAIT;
			break;
		}
		case WAIT2:
		{
		 	i = i +1;	
			if((~PINA & 0x03) == 0x03)
			{
				state = RESET;
			}
			else if((~PINA & 0x03) == 0x01 && i == 10)
			{
				i = 0x00;
				state = INCREASE;
			}
			else if((~PINA & 0x03) == 0x02 && i == 10)
			{
				i = 0x00;
				state = DECREASE;
			}
			else if ((i < 10) && (((~PINA & 0x03) == 0x02) ||((~PINA & 0x03) == 0x01)))
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
			i= 0x00;
			LCD_ClearScreen();
			if(b < 0x09)
			{
				b = b + 0x01;	
			}
			LCD_WriteData(b + '0');
			break;
		}
		case DECREASE:
		{
			i = 0x00;
			LCD_ClearScreen();
			if(b > 0x00)
			{
				b = b - 0x01;
			}
			LCD_WriteData(b + '0');
			break;
		}
		case RESET:
		{
			i= 0x00;
			LCD_ClearScreen();
			b = 0x00;
			LCD_WriteData(b + '0');
			break;
		}
		/*case WAIT2:
		{
			break;
		}*/
		default:
		{
			break;
		}
	}
}
    

