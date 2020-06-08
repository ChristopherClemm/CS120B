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

enum keysmstates {out} keysmstate;
int Key(int keystate) {
	unsigned char x;
	x = GetKeypadKey();
	switch(keysmstate) {
		case out:
			switch(x) {
				case '\0':
				{
					PORTB=0x1F;
				       	break;
				}
				case '1':
				{
					PORTB = 0x01;
				       	break;
				}

				case '2':
				{
					PORTB = 0x02;
				       	break;
				}
				case '3':
				{
					PORTB = 0x03; 
					break;
				}
				case '4': 
				{
					PORTB = 0x04;
				       	break;
				}
				case '5':
				{
					PORTB = 0x05; 
					break;
				}
				case '6': 
				{
					PORTB = 0x06;
				       	break;
				}
				case '7':
				{	
					PORTB = 0x07;
				       	break;
				}
				case '8': 
				{
					PORTB = 0x08;
				       	break;
				}
				case '9':
				{
					 PORTB = 0x09;
					 break;
				}
				case 'A':
				{
					PORTB = 0x0A;
				       	break;
				}
				case 'B':
				{
					PORTB = 0x0B; 
					break;
				}
				case 'C': 
				{
					PORTB = 0x0C;
				       	break;
				}
				case 'D': 
				{
					PORTB = 0x0D;
				       	break;
				}
				case '*':
				{
					PORTB = 0x0E; 
					break;
				}
				case '#': 
				{
					PORTB = 0x0F;
				       	break;
				}
				default: 
				{
					PORTB = 0x01B;
				       	break;
				}
			}
			keysmstate = out;
			break;
	}
	return keysmstate;
}


enum lcdstates {start, wait, disp} lcdstate;
unsigned char show[54] = {'C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.',' ','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};


unsigned char temp = 1;

int LCDSM(int lcdstate) {
	switch(lcdstate) {
		case start:
		{
			lcdstate = wait;
			break;
		}
		case wait:
		{
			LCD_ClearScreen();
			
			temp = 1;
			lcdstate = disp;
			break;
		}
		case disp:
		{
			LCD_ClearScreen();
			for(unsigned char i = temp-1;  i  < temp+15; i++) {
				LCD_WriteData(show[i]);
			}
			temp++;
			if(temp == 40)
			{
				temp = 1;
			}
			break;
		}
	}
	return lcdstate;
}



int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1, task2;


	task *tasks[] ={ &task1, &task2 };
	
	const unsigned short numTasks = 2;

	
	task1.state = out; 
	task1.period = 1000; 
	
	task1.elapsedTime = task1.period; 
	task1.TickFct = &Key; 
	
	task2.state = start;
	task2.period = 500;
	task2.elapsedTime = task2.period;
	task2.TickFct = &LCDSM;
	LCD_init();
	TimerSet(500);
	TimerOn();
	while (1) {
    		for(unsigned char i = 0; i<numTasks ; i++) {
			if(tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 500;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
    	return 1;
}
