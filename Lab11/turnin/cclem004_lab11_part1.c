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
#include "bit.h"
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"
//#include "lcd_8bit_task.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char led0_output = 0x00;
unsigned char led1_output = 0x00;
unsigned char pause = 0;

enum keystates{out} keystate;
int keyPadTick(int keystate)
{
	unsigned char x;
	x = GetKeypadKey();
	switch(keystate){
		case out:
		{
			if(x == '1') 
			{
				PORTB = 0x01;
			}
			switch(x)
			{
				case '\0':
				{
					PORTB = 0x1F;
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
                                        PORTB = 0x05;
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
				deafult:
				{
					PORTB = 0x01B;
					break;
				}

			}	
			keystate = out;
			break;

		}
		return keystate;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    static task task1, task2, task3, task4;
    task *tasks[] = { &task1, &task2, &task3, &task4};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    const char start = -1;

    task1.state = out;
    task1.period = 1000;
    task1.elapsedTime = task1.period;
    task1.TickFct = &keyPadTick;

    LCD_init();
    LCD_WriteData(0 + '0');

   /* //task 2 toggleLEDSM
    /
    task2.state = start;
    task2.period = 500;
    task2.elapsedTime = task2.period;
    task2.TickFct = &toggleLED0SMTick;
   
	//Task 3
    task3.state = start;
    task3.period = 1000;
	task3.elapsedTime = task3.period;
    	task3.TickFct = &toggleLED1SMTick;
	
	//task4 displaysm
	
	task4.state = start;
	task4.period = 10;
	task4.elapsedTime = task4.period;
	task4.TickFct = &displaySMTick;
	*/
	unsigned long GCD = tasks[0]->period;
	unsigned short i;
	for(i = 1; i <numTasks; i++)
	{
		GCD = findGCD(GCD, tasks[i]->period);
	}
	
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	
		

    /* Insert your solution below */
    while (1) {
	
	for(i = 0; i <numTasks; i++)
	{
		if(tasks[i]->elapsedTime = tasks[i]->period)
		{
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += GCD;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
