/*
 * ATmega32.h
 *
 *  Created on: Feb 11, 2016
 *      Author: marco
 */

#ifndef ATMEGA32_H_
#define ATMEGA32_H_

#include "main.h"

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

uint8_t ui_player1_L(uint8_t _ui_buttons);
uint8_t ui_player1_R(uint8_t _ui_buttons);
uint8_t ui_player1_U(uint8_t _ui_buttons);
uint8_t ui_player1_D(uint8_t _ui_buttons);
uint8_t ui_player2_L(uint8_t _ui_buttons);
uint8_t ui_player2_R(uint8_t _ui_buttons);
uint8_t ui_player2_U(uint8_t _ui_buttons);
uint8_t ui_player2_D(uint8_t _ui_buttons);


void resetPlayer1_L(uint8_t *_ui_buttons);
void resetPlayer1_R(uint8_t *_ui_buttons);
void resetPlayer1_U(uint8_t *_ui_buttons);
void resetPlayer1_D(uint8_t *_ui_buttons);
void resetPlayer2_L(uint8_t *_ui_buttons);
void resetPlayer2_R(uint8_t *_ui_buttons);
void resetPlayer2_U(uint8_t *_ui_buttons);
void resetPlayer2_D(uint8_t *_ui_buttons);

#endif /* ATMEGA32_H_ */
