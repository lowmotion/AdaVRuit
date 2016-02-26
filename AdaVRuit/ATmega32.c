/*
 * ATmega32.c
 *
 *  Created on: Feb 11, 2016
 *      Author: Marco, Michael, Michel, Christian, Tobias
 */

#include "ATmega32.h"

void initATMega32() {
	/* Taster */
    DDRB = 0b10110001;       // Eingänge PortB 1 3 2 6
    DDRF = 0b00001111;       // Eingänge PortF 4 5 6 7
}

void initTWI() {

}

void TWI_sendByte(uint8_t ui_adress, uint8_t ui_data) {

}

void TWI_sendArray(uint8_t ui_data[8][2]) {

}

// Diese Funktionen geben die Zahl = 1, wenn der Taster gedr�ckt ist - =0 wenn der Taster nicht gedr�ckt ist
uint8_t ui_player1_L(uint8_t _ui_buttons) {return ((_ui_buttons & 0x80) >> 7);}
uint8_t ui_player1_R(uint8_t _ui_buttons) {return ((_ui_buttons & 0x40) >> 6);}
uint8_t ui_player1_U(uint8_t _ui_buttons) {return ((_ui_buttons & 0x20) >> 5);}
uint8_t ui_player1_D(uint8_t _ui_buttons) {return ((_ui_buttons & 0x10) >> 4);}
uint8_t ui_player2_L(uint8_t _ui_buttons) {return ((_ui_buttons & 0x08) >> 3);}
uint8_t ui_player2_R(uint8_t _ui_buttons) {return ((_ui_buttons & 0x04) >> 2);}
uint8_t ui_player2_U(uint8_t _ui_buttons) {return ((_ui_buttons & 0x02) >> 1);}
uint8_t ui_player2_D(uint8_t _ui_buttons) {return (_ui_buttons & 0x01);}

void resetPlayer1_L(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x80);}
void resetPlayer1_R(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x40);}
void resetPlayer1_U(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x20);}
void resetPlayer1_D(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x10);}
void resetPlayer2_L(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x08);}
void resetPlayer2_R(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x04);}
void resetPlayer2_U(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x02);}
void resetPlayer2_D(uint8_t *_ui_buttons) {(*_ui_buttons &= ~0x01);}

/* Vergabe der  Pins:
        Spieler 1:  Richtung - Port - Pin (Anschluss)
                    Left     - PF4  - A3
                    Right    - PF5  - A2
                    Up       - PF6  - A1
                    Down     - PF7  - A0
                    (A6 bis A9 sind als analoge Eing�nge verf�gbar)
        Spieler 2:
                    Left     - PB1  - 15
                    Right    - PB3  - 14
                    Up       - PB2  - 16
                    Down     - PB6  - 10
    Die Pins liegen alle in genau dieser Reihenfolge untereinander
*/



/*
 * Beschreibung:       	Auslesen der  Eingabetasten (PortB und  PortF).
 *                     	Man geht davon aus, dass die Tasten AKTIVE LOW sind.
 *                     	Es wurden Makros definiert, um direkt die Richtungen abzufragen
 * Aufbau der Variable: uint8_t ui_buttons;
 *                      	Bit 0-3 -> player 1
 *                     		Bit 4-7 -> player 2
 *                         		Bit 0/4 -> Left
 *                         		Bit 1/5 -> Right
 *                         		Bit 2/6 -> Up
 *                         		Bit 3/7 -> Down
 */
uint8_t ui_eingabe(){
    uint8_t ui_bufferPF = 0x00, ui_bufferPB = 0x00, ui_buttons = 0x00;
    ui_bufferPF = ~PINF;
    ui_bufferPB = ~PINB;

    ui_buttons |= ((ui_bufferPF & 0x10) << 3);     // Bit 4 -> Bit 7 in ui_buttons
    ui_buttons |= ((ui_bufferPF & 0x20) << 1);     // Bit 5 -> Bit 6 in ui_buttons
    ui_buttons |= ((ui_bufferPF & 0x40) >> 1);     // Bit 6 -> Bit 5 in ui_buttons
    ui_buttons |= ((ui_bufferPF & 0x80) >> 3);     // Bit 7 -> Bit 4 in ui_buttons

    ui_buttons |= ((ui_bufferPB & 0x02) << 2);     // Bit 1 -> Bit 3 in ui_buttons
    ui_buttons |= ((ui_bufferPB & 0x08) >> 1);     // Bit 3 -> Bit 2 in ui_buttons
    ui_buttons |= ((ui_bufferPB & 0x04) >> 1);     // Bit 2 -> Bit 1 in ui_buttons
    ui_buttons |= ((ui_bufferPB & 0x40) >> 6);     // Bit 6 -> Bit 0 in ui_buttons

	return ui_buttons;
}

/* Beschreibung:	Die (überladene) Funktionen fragen beim Aufruf die zugehörigen Pins ab. 
 * 			Sie geben eine 0x01 zurück, falls die Taste gedrückt ist. ansonten = 0x00
 * 			Es findet bisher kein Entprellen statt.
 * Globale Variablen:	Keine
 */
uint8_t ui_player1_L() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & 0x10) >0) return 0x01;
	else return 0x00;
}
uint8_t ui_player1_R() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & 0x20) >0) return 0x01;
	else return 0x00;
}
uint8_t ui_player1_U() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & 0x40) >0) return 0x01;
	else return 0x00;
}
uint8_t ui_player1_D() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & 0x80) >0) return 0x01;
	else return 0x00;
}

uint8_t ui_player2_L() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & 0x02) >0) return 0x01;
	else return 0x00;
}
uint8_t ui_player2_R() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & 0x08) >0) return 0x01;
	else return 0x00;
}
uint8_t ui_player2_U() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & 0x04) >0) return 0x01;
	else return 0x00;
}
uint8_t ui_player2_D() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & 0x40) >0) return 0x01;
	else return 0x00;
}
