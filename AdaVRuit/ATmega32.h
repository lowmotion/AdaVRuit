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

#endif /* ATMEGA32_H_ */
