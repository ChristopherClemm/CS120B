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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{INIT, ONE, TWO, THREE, WAIT} state;
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
				state = ONE;
			}
			else if ((~PINA & 0x07) == 0x02)
			{
				state = TWO;
			}
			else if ((~PINA & 0x07) == 0x04)
			{
				state = THREE;
			}
			else
			{
				state = WAIT;
			}
			break;
		}
		case ONE:
		{
			if((~PINA & 0x07) == 0x01)
			{
				state = ONE;
			}
			else
			{
				state = WAIT;
			}
			break;
		}
		case TWO:
		{
			if((~PINA & 0x07) == 0x02)
                        {
                                state = TWO;
                        }
                        else
                        {
                                state = WAIT;
                        }
                        break;

		}
		case THREE:
		{
			if((~PINA & 0x07) == 0x04)
                        {
                                state = THREE;
                        }
                        else
                        {
                                state = WAIT;
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
			break;
		}
		case WAIT:
		{
			set_PWM(0);
			break;
		}
		case ONE:
		{
			set_PWM(261.63);
			break;
		}
		case TWO:
		{
			set_PWM(293.66);
			break;
		}
		case THREE:
		{
			set_PWM(329.63);
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
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}


