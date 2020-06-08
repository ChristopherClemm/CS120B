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
#include "scheduler.h"
#include "keypad.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum keysmstates {out, w,start} keysmstate;
unsigned char cursor = 1;
int Key(int keystate) {
	unsigned char x;
	x = GetKeypadKey();
	
	switch(keysmstate) {
		case start:
		{
			LCD_DisplayString(1,"Congratulations!");
			LCD_Cursor(cursor);
			keysmstate = out;
			break;
		}
		case out:
			
			switch(x) {

				case '\0':
				{
					break;
				}
				case '0':
				{
				       	LCD_WriteData(0+'0');
				       	cursor++;	
					keysmstate = w;
				       	break;
				}
				case '1':
				{
				       LCD_WriteData(1+'0'); cursor++;
				       	keysmstate = w; 
					break;
				}
				case '2':
				{
				       	LCD_WriteData(2+'0');
                                        cursor++;
				       	keysmstate = w;
				       	break;
				}
				case '3': 
				{
					LCD_WriteData(3+'0');
                                        cursor++;
				       	keysmstate = w;
				       	break;
				}
				case '4':
				{
				       	LCD_WriteData(4+'0');
                                        cursor++;
				       	keysmstate = w; 
					break;
				}
				case '5':
				{
				       	LCD_WriteData(5+'0');
                                        cursor++;
					keysmstate = w;
				       	break;
				}
				case '6':
				{
					LCD_WriteData(6+'0');
                                        cursor++;
				       	LCD_DisplayString(1,"6");
				       	keysmstate = w;
				       	break;
				}
				case '7':
				{
					LCD_WriteData(7+'0');
                                        cursor++;
				       	keysmstate = w;
				       	break;
				}
				case '8':
				{
					LCD_WriteData(8+'0');
                                        cursor++;
				       
				       	keysmstate = w;
				       	break;
				}
				case '9':
				{
					LCD_WriteData(9+'0');
                                        cursor++;
				       	keysmstate = w;
				       	break;
				}
				case 'A':
				{ 
					LCD_WriteData('A');
                                        cursor++;

				       	keysmstate = w;
				       	break;
				}
				case 'B':
				{
				       	LCD_WriteData('B');
                                        cursor++;

					keysmstate = w; 
					break;
				}
				case 'C': 
				{
				       LCD_WriteData('C');
                                        cursor++;

					keysmstate = w;
				       	break;
				}
				case 'D':
				{
				       	LCD_WriteData('D');
                                        cursor++;

				       	keystate = w; 
					break;
				}
				case '*':
				{
				       	LCD_WriteData('*');
                                        cursor++;

				       	keysmstate = w;
				       	break;
				}
				case '#':
				{
				       	LCD_WriteData('#');
                                        cursor++;
				       	keysmstate = w;
				       	break;
				default: 
				 {
					  break;
				 }
			}
			break;
		case w:
			if(cursor == 17)
			{
				cursor = 1;
				LCD_Cursor(cursor);
			}
			if(x == '\0') 
			{
				keysmstate = out;
			}
			break;
	}
	return keysmstate;
}
}




int main(void) {
	DDRA = 0x0F; PORTA = 0xF0;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1;


	task *tasks[] ={ &task1 };
	const unsigned short numTasks = 1;


	task1.state = start; 
	task1.period = 50; 
	task1.elapsedTime = task1.period; 
	task1.TickFct = &Key; 
	

	TimerSet(10);

	TimerOn();

	LCD_init();
	LCD_ClearScreen();
	while (1) {
    		for(unsigned char i = 0; i<numTasks ; i++) {
			if(tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 10;
		}


		while(!TimerFlag);
		TimerFlag = 0;
	
	}
    	return 1;
}
