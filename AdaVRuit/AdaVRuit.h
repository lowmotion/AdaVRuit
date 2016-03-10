 /*****************************************************************************
*
* FILE: 		      ATmega32U4.h
* PROJECT:	      Spielekonsole
* MODULE:		      ???
*
* Description:		Header zu ATmega32U4.c
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date:   11.02.2016
* BY:	    Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/

#ifndef ADAVRUIT_H_
#define ADAVRUIT_H_

#include "main.h"
#include "twi.h"

#define DISABLE_WATCHDOG()  MCUSR &= ~(1<<WDRF); WDTCSR |= (1<<WDCE) | (1<<WDE); WDTCSR = 0x00

#define TRUE	1
#define FALSE	0

#define BIT0	0b00000001
#define BIT1	0b00000010
#define BIT2	0b00000100
#define BIT3	0b00001000
#define BIT4	0b00010000
#define BIT5	0b00100000
#define BIT6	0b01000000
#define BIT7	0b10000000

#define LED_ON	1
#define LED_OFF	0

/* Helligkeit der LEDs des Displays. Zwischen 0 und 15 */
#ifndef LED_BRIGHTNESS
#warning "LED_BRIGHTNESS was not set for AdaVRuit.h. Default is '7'. Possible between '0' and '15'!"
#endif

extern volatile uint8_t ui_timerFlag;

extern volatile uint16_t ui_timerOffset;


void clearDisplay();

void initSystem();

void printBit(uint8_t ui_row, uint8_t ui_column, uint8_t ui_ledState);

void printArray(uint16_t ui_matrix[8]);

uint8_t ui_getBit(uint8_t ui_row, uint8_t ui_column);

uint8_t ui_eingabe();

uint8_t ui_player1_L();
uint8_t ui_player1_R();
uint8_t ui_player1_U();
uint8_t ui_player1_D();
uint8_t ui_player2_L();
uint8_t ui_player2_R();
uint8_t ui_player2_U();
uint8_t ui_player2_D();

uint8_t b_player1_L(uint8_t _ui_buttons);
uint8_t b_player1_R(uint8_t _ui_buttons);
uint8_t b_player1_U(uint8_t _ui_buttons);
uint8_t b_player1_D(uint8_t _ui_buttons);
uint8_t b_player2_L(uint8_t _ui_buttons);
uint8_t b_player2_R(uint8_t _ui_buttons);
uint8_t b_player2_U(uint8_t _ui_buttons);
uint8_t b_player2_D(uint8_t _ui_buttons);


void resetPlayer1_L(uint8_t *_ui_buttons);
void resetPlayer1_R(uint8_t *_ui_buttons);
void resetPlayer1_U(uint8_t *_ui_buttons);
void resetPlayer1_D(uint8_t *_ui_buttons);
void resetPlayer2_L(uint8_t *_ui_buttons);
void resetPlayer2_R(uint8_t *_ui_buttons);
void resetPlayer2_U(uint8_t *_ui_buttons);
void resetPlayer2_D(uint8_t *_ui_buttons);

#endif /* ADAVRUIT_H_ */
