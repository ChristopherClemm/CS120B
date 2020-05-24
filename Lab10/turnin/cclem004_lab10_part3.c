/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "timer.h"
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void tickThree();
void tickBlink();
void tickCombine();
void tickSpeaker();
enum StateSpeaker{init4, on2, off2}stateSpeaker;
enum StateThree{init1, one, two, three}stateThree;
enum StateBlink{init2, on, off}stateBlink;
enum StateCombine{init3, output}stateCombine;
unsigned char threeLEDS = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char b4 = 0x00;
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
	stateThree = init1;
	stateBlink = init2;
	stateCombine = init3;
	stateSpeaker = init4;
	TimerSet(2);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	    tickThree();
	    tickBlink();
	    tickCombine();
	    tickSpeaker();
	    while(!TimerFlag);
	    TimerFlag = 0;

    }
    return 1;
}
void tickThree()
{
	static unsigned char count = 0;
	count++;
	switch(stateThree)
	{
		case init1:
		{
			stateThree = one;
			break;
		}
		case one:
		{
			if(count == 150)
			{
				stateThree = two;
				count = 0;;
			}
			else
			{
				stateThree = one;
			}
			
			break;
		}
		case two:
		{
			if(count == 150)
			{
				stateThree = three;
				count = 0;
			}
			else
			{
				stateThree = two;
			}
			break;
		}
		case three:
		{
			if(count == 150)
			{
				stateThree = one;
				count = 0;
			}
			else
			{
				stateThree = three;
			}
			break;
		}
	}
	switch(stateThree)
	{
		case init1:
		{
			break;
		}
		case one:
		{
			threeLEDS = 0x01;
			break;
		}
		case two:
		{
			threeLEDS = 0x02;
			break;
		}
		case three:
		{
			threeLEDS = 0x04;
			break;
		}
		
	}
}

void tickBlink()
{
	static unsigned char count = 0;
	count++;
	static unsigned char count2 = 0;
	if(count == 250)
	{
		count = 0;
		count2++;
	}
	switch(stateBlink)
	{
	
		case init2:
		{
			stateBlink = off;
		        break;	
		}
		case on:
		{	if(count2 == 2)
			{
				stateBlink = off;
				count2 = 0;
			}
			else
			{
				stateBlink = on;
			}
				break;
		}
		case off:
		{	if(count2 == 2)
			{
				stateBlink = on;
				count2 = 0;
			}
			else
			{
				stateBlink = off;
			}
			break;
		}		
	}
	switch(stateBlink)
	{

		case init2:
		{
			break;
		}
		case on:
		{
			blinkingLED = 0x08;
			break;
		}
		case off:
		{
			blinkingLED = 0x00;
			break;
		}
	}
}
void tickSpeaker()
{
	static unsigned char count = 0;
	count++;

	switch(stateSpeaker)
	{
		case init4:
		{
			stateSpeaker = off2;
			break;
		}
		case off2:
		{
			if((~PINA & 0x04) == 0x04)
			{
				stateSpeaker = on2;
			}
			else
			{
				stateSpeaker = off2;
			}
			break;
		}
		case on2:
		{
			if((~PINA & 0x04) == 0x00)
			{
				stateSpeaker = off2;
			}
			else
			{
				stateSpeaker = on2;
			}
			break;
		}

	}
	switch(stateSpeaker)
	{
		case init4:
		{
			break;
		}
		case off:
		{
			b4= 0x00;
			break;
		}
		case on:
		{
			if(count%2 ==  0)
			{
				count = 0;
				b4 = 0x10;
			}
			else
			{
				b4 = 0x00;
			}
			break;
		}
	}
}
void tickCombine()
{
	switch(stateCombine)
	{
		case init3:
		{
			stateCombine = output;
			break;
		}
		case output:
		{
			stateCombine = output;
			break;
		}
	}
	switch(stateCombine)
	{
		case init3:
		{
			break;
		}
		case output:
		{
			PORTB = (threeLEDS + blinkingLED + b4);
			break;
		}
	}
}
