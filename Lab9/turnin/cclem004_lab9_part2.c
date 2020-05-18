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

unsigned char i = 0x00;
double notes[8] = {261.63,293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
enum States{INIT, UP, DOWN, ON, OFF, WAIT, OFFWAIT} state;
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
			state = OFF;
			break;
		}
		case WAIT:
		{
			if ((~PINA & 0x07) != 0x00)
			{
				state = WAIT;
			}
			else
			{
				state = ON;
			}
			break;
		}
		case OFF:
		{
			if((~PINA & 0x07) == 0x01)
			{
				state = WAIT;
			}
			else
			{
				state =  OFF;
			}
			break;
			
		}
		case ON:
		{
			if ((~PINA & 0x07) == 0x02)
			{
				state = DOWN;
			}
			else if ((~PINA & 0x07) == 0x04)
			{
				state = UP;
			}
			else if ((~PINA & 0x07) == 0x01)
			{
				state = OFFWAIT;
			}
			else
			{
				state = ON;
			}
			break;
		}
		case OFFWAIT:
		{
			 if ((~PINA & 0x07) != 0x00)
                        {
                                state = OFFWAIT;
                        }
                        else
                        {
                                state = OFF;
                        }
                        break;

		}
		case UP:
		{	
			state = WAIT;
			break;
		}
		case DOWN:
		{
                        state = WAIT;
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
			break;
		}
		case OFF:
		{
			set_PWM(0);
			break;
		}
		case OFFWAIT:
		{
			set_PWM(0);
			break;
		}
		case ON:
		{
			set_PWM(notes[i]);
			break;
		}
		case UP:
		{
			if ( i < 7)
			{
				i = i + 1;
			}
			set_PWM(notes[i]);
			break;
		}
		case DOWN:
		{
			if(i > 0 )
			{
				i = i - 1;
			}
			set_PWM(notes[i]);
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


