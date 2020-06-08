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

enum keysmstates {out, w} keysmstate;
unsigned char count = 0;
int KeySM(int keystate) {
	unsigned char x;
	x = GetKeypadKey();
	
	switch(keysmstate) {
		case out:
			
			switch(x) {

				case '\0':
				{
					break;
				}
				case '0':
				{
				       	LCD_DisplayString(1,"0");
				       	keysmstate = w;
				       	break;
				}
				case '1':
				{
				       	LCD_DisplayString(1,"1");
				       	keysmstate = w; 
					break;
				}
				case '2':
				{
				       	LCD_DisplayString(1,"2");
				       	keysmstate = w;
				       	break;
				}
				case '3': 
				{
					LCD_DisplayString(1,"3");
				       	keysmstate = w;
				       	break;
				}
				case '4':
				{
				       	LCD_DisplayString(1,"4");
				       	keysmstate = w; 
					break;
				}
				case '5':
				{
				       	LCD_DisplayString(1,"5"); 
					keysmstate = w;
				       	break;
				}
				case '6':
				{
				       	LCD_DisplayString(1,"6");
				       	keysmstate = w;
				       	break;
				}
				case '7':
				{
					LCD_DisplayString(1,"7");
				       	keysmstate = w;
				       	break;
				}
				case '8':
				{
				       	LCD_DisplayString(1,"8");
				       	keysmstate = w;
				       	break;
				}
				case '9':
				{
				       	LCD_DisplayString(1,"9");
				       	keysmstate = w;
				       	break;
				}
				case 'A':
				{ 
					LCD_DisplayString(1,"A");
				       	keysmstate = w;
				       	break;
				}
				case 'B':
				{
				       	LCD_DisplayString(1,"B"); 
					keysmstate = w; 
					break;
				}
				case 'C': 
				{
				       	LCD_DisplayString(1,"C"); 
					keysmstate = w;
				       	break;
				}
				case 'D':
				{
				       	LCD_DisplayString(1,"D");
				       	keystate = w; 
					break;
				}
				case '*':
				{
				       	LCD_DisplayString(1,"*");
				       	keysmstate = w;
				       	break;
				}
				case '#':
				{
				       	LCD_DisplayString(1,"#");
				       	keysmstate = w;
				       	break;
				default: 
				 {
					  break;
				 }
			}
			break;
			
			case w:
			if(x == '\0') keysmstate = out;
		
		
			//LCD_WriteData(0 +'0');
			break;
	}
	return keysmstate;
}




int main(void) {
	DDRA = 0x0F; PORTA = 0xF0;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1;


	task *tasks[] ={ &task1 };
	const unsigned short numTasks = 1;


	task1.state = out; 
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
