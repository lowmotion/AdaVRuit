/*
 * main.h
 *
 *  Created on: Feb 11, 2016
 *      Author: marco
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ATmega32U4.h"
#include "pong.h"

#define LED_ON	1
#define LED_OFF	0

void printBit(uint8_t ui_row, uint8_t ui_column, uint8_t ui_ledState);

void printArray(uint8_t ui_matrix[8][2]);

uint8_t ui_getBit(uint8_t ui_row, uint8_t ui_column);

#endif /* MAIN_H_ */
