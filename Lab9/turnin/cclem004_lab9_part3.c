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

unsigned char i = 0x00;
unsigned char j = 0x00;
double notes[9] = {392.00,523.25, 329.63, 349.23, 392.00, 523.25, 493.88, 523.25};
int time[9] = {5, 5, 10, 5, 5, 5, 10, 10};
enum States{INIT, WAIT, PLAY, WAIT2} state;
void set_PWM(double frequency)
{
	static double current_frequency;
	if( frequency != current_frequency)
	{
		if(!frequency) TCCR3B &= 0x08;
		else TCCR3B |= 0x03;
		
		if(frequency < .954) OCR3A = 0xFFFF;

		else if (frequency > 31250) OCR3A = 0x0000;

		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;


		TCNT3 = 0;
		current_frequency = frequency;		
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void Tick(){
	switch(state)
	{
		case INIT:
		{
			state = WAIT;
			break;
		}
		case WAIT:
		{
			if ((~PINA & 0x07) == 0x01)
			{
				state = PLAY;
			}
			else
			{
				state = WAIT;
			}
			break;
		}
		case PLAY:
		{
			if(i > 8)
			{
				i = 0;
				j = 0;
				if((~PINA & 0x07) == 0x01)
				{
					state = WAIT2;
				}
				else
				{
					state = WAIT;
				}
			}
			else
			{
				state = PLAY;
			}
			
			break;
			
		}
		
		case WAIT2:
		{
			if((~PINA & 0x07) == 0x01)
			{
				state = WAIT2;
			}
			else
			{
				state = PLAY;
			}
			break;
		}
		
		default:
		{
			break;
		}
	}
	switch(state)
	{
		case INIT:
		{
			set_PWM(0);
			break;
		}
		case WAIT:
		{
			set_PWM(0);
			break;
		}
		case PLAY:
		{
			if ( j == time[i])
			{
				i = i + 1;
				j = 0;
			}
			else
			{
				j = j + 1;
			}
			set_PWM(notes[i]);
			break;
		}
		case WAIT2:
		{
			set_PWM(0);
			break;
		}
		default:
		{
			break;
		}


	}

	}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00; //OUTPUT
	DDRA = 0x00; PORTA = 0xFF; //INPUT
	PWM_on();
	state = INIT;
	TimerSet(100);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}


