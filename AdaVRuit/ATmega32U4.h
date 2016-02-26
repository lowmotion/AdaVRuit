/*
 * ATmega32U4.h
 *
 *  Created on: Feb 11, 2016
 *      Author: marco
 */

#ifndef ATMEGA32U4_H_
#define ATMEGA32U4_H_

#include "main.h"

#define TRUE	0x01
#define FALSE	0x00

#define BIT0	0b00000001
#define BIT1	0b00000010
#define BIT2	0b00000100
#define BIT3	0b00001000
#define BIT4	0b00010000
#define BIT5	0b00100000
#define BIT6	0b01000000
#define BIT7	0b10000000

void initATMega32();

void TWI_sendByte(uint8_t ui_adress, uint8_t ui_data);

void TWI_sendArray(uint8_t ui_data[8][2]);

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

#endif /* ATMEGA32U4_H_ */
