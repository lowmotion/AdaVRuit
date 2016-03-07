/*
 * main.c
 *
 *  Created on: Feb 11, 2016
 *      Author: marco
 */

#include "main.h"

/*
 * Variable:		matrix
 * Beschreibung:	Diese Matrix representiert die derzeitige Ausgabe auf den LEDs. Sie besitzt acht Zeilen und zwei Spalten
 * 					mit jeweils acht Bit. Jedes einzelne Bit ist also eine LED.
 * 					8 Zeilen x 2 Spalten x 8 Bit = 16 Spalten x 8 Reihen
 */
uint8_t matrix[8][2];

/*
 * Funktion:			printBit
 * Beschreibung:		Ändert ein bestimmtes Bit in der LED Matrix.
 * 						Adressierung:
 * 							Zeilen: 	0 bis 7
 * 							Spalten: 	0 bis 15
 * Globale Variablen:	matrix[8][2]
 */
void printBit(uint8_t ui_row, uint8_t ui_column, uint8_t ui_ledState) {
	uint8_t leftRight = 0x00;
	switch(ui_ledState) {
	case LED_OFF:
		if(ui_column > 7) {
				matrix[ui_row][1] &= ~(1 << (ui_column-8));
				leftRight = 1;
			} else {
				matrix[ui_row][0] &= ~(1 << ui_column);
				leftRight = 0;
			}
		TWI_sendByte(ui_row*2)+leftRight, matrix[ui_row][leftRight]);
		break;
	case LED_ON:
		if(ui_column > 7) {
				matrix[ui_row][1] |= (1 << (ui_column-8));
				leftRight = 1;
			} else {
				matrix[ui_row][0] |= (1 << ui_column);
				leftRight = 0;
			}
		TWI_sendByte((ui_row*2)+leftRight, matrix[ui_row][leftRight]);
		break;
	}

}

/*
 * Funktion:			printArray
 * Beschreibung:		Gibt ein ganzes Array vom Format 8 Zeilen x 2 Spalten x 8 Bit auf den LEDs aus.
 * Globale Variablen:	matrix
 */
void printArray(uint8_t ui_matrix[8][2]) {
	for(short row = 0; row < 8; row++) {
		for(short column = 0; column < 2; column++) {
			matrix[row][column] = ui_matrix[row][column];
		}
	}
	TWI_sendArray(matrix);
}

/*
 * Funktion:		ui_getBit
 * Beschreibung:	Diese Funktion gibt den Werte des Bits an der gefragten Stelle in der matrix wieder.
 */
uint8_t ui_getBit(uint8_t ui_row, uint8_t ui_column) {
	if(ui_column > 7) {	//
		return matrix[ui_row][1] & (1 << (ui_column-8));
	} else {
		return matrix[ui_row][0] & (1 << ui_column);
	}
}

int main() {
	return 0;
}
