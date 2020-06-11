
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


typedef enum gamestates{GAMEINIT, PLAY, OVER, RESTART} gamestates;
typedef enum player_one_states{PLAYER_ONE_INIT,PLAYER_ONE_STAY, PLAYER_ONE_WAIT, PLAYER_ONE_UP, PLAYER_ONE_DOWN, PLAYER_ONE_DEAD} player_one_states;
unsigned char i = 0x00;
unsigned char b = 0x00;
unsigned short player_one_cursor = 1;
unsigned char play = 0x01;

gamestates gamestate;
player_one_states player_one_state;

#include "game.h"
#include "player_one.h"


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

LCD_init();

TimerSet(100);
TimerOn();
gamestate = GAMEINIT;
player_one_state = PLAYER_ONE_INIT;

while(1)
{

	PlayGame();
	PlayerOne();
	while(!TimerFlag);
	TimerFlag = 0;
}	
	return 1;
}

    

