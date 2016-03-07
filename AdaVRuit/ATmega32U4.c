 /*****************************************************************************
*
* FILE: 		ATmega32U4.c
* PROJECT:		Spielekonsole
* MODULE:		???
*
* Description:		???
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date: 07.03.2016
* BY:	Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/

#include "ATmega32U4.h"

/**************************************************************************
* NAME:			initATMega32
* Description:		Initialisierung der Ein- und Ausgänge
*
* Subroutines Called:	keine
*
* Returns:		keine
*
* Globals:		keine
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void initATMega32() {
	/* Taster */
    DDRB = 0b10110001;       // Eingänge PortB 1 3 2 6
    DDRF = 0b00001111;       // Eingänge PortF 4 5 6 7
}


/**************************************************************************
* NAME:			initTWI
* Description:		Initialisierung des TWI (I2C)
*
* Subroutines Called:	???
*
* Returns:		keine
*
* Globals:		???
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void initTWI() {

}

/**************************************************************************
* NAME:			TWI_sendByte
* Description:		???
*
* Subroutines Called:	???
*
* Returns:		keine
*
* Globals:		???
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void TWI_sendByte(uint8_t ui_adress, uint8_t ui_data) {

}

/**************************************************************************
* NAME:			TWI_sendArray
* Description:		???
*
* Subroutines Called:	???
*
* Returns:		keine
*
* Globals:		???
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void TWI_sendArray(uint8_t ui_data[8][2]) {

}

// Diese Funktionen geben die Zahl = 1, wenn der Taster gedr�ckt ist - =0 wenn der Taster nicht gedr�ckt ist
uint8_t b_player1_L(uint8_t _ui_buttons) {return ((_ui_buttons & BIT7) >> 7);}
uint8_t b_player1_R(uint8_t _ui_buttons) {return ((_ui_buttons & BIT6) >> 6);}
uint8_t b_player1_U(uint8_t _ui_buttons) {return ((_ui_buttons & BIT5) >> 5);}
uint8_t b_player1_D(uint8_t _ui_buttons) {return ((_ui_buttons & BIT4) >> 4);}
uint8_t b_player2_L(uint8_t _ui_buttons) {return ((_ui_buttons & BIT3) >> 3);}
uint8_t b_player2_R(uint8_t _ui_buttons) {return ((_ui_buttons & BIT2) >> 2);}
uint8_t b_player2_U(uint8_t _ui_buttons) {return ((_ui_buttons & BIT1) >> 1);}
uint8_t b_player2_D(uint8_t _ui_buttons) {return (_ui_buttons & BIT0);}

void resetPlayer1_L(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT7);}
void resetPlayer1_R(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT6);}
void resetPlayer1_U(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT5);}
void resetPlayer1_D(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT4);}
void resetPlayer2_L(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT3);}
void resetPlayer2_R(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT2);}
void resetPlayer2_U(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT1);}
void resetPlayer2_D(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT0);}




/**************************************************************************
* NAME:			ui_eingabe
* Description:		Auslesen der  Eingabetasten (PortB und  PortF).
*                     	Man geht davon aus, dass die Tasten AKTIVE LOW sind.
*                     	Es wurden Funktionen definiert, um direkt die Richtungen abzufragen
*
* Subroutines Called:	keine
*
* Returns:		uint8_t ui_buttons;
*                      	Bit 0-3 -> player 1
*                     		Bit 4-7 -> player 2
*                         	Bit 0/4 -> Left
*                         	Bit 1/5 -> Right
*                         	Bit 2/6 -> Up
*                         	Bit 3/7 -> Down
*
* Globals:		keine
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:	
* 	Vergabe der  Pins:
*        Spieler 1:  Richtung - Port - Pin (Anschluss)
*                    Left     - PF4  - A3
*                    Right    - PF5  - A2
*                    Up       - PF6  - A1
*                    Down     - PF7  - A0
*                    (A6 bis A9 sind als analoge Eing�nge verf�gbar)
*        Spieler 2:
*                    Left     - PB1  - 15
*                    Right    - PB3  - 14
*                    Up       - PB2  - 16
*                    Down     - PB6  - 10
*    	Die Pins liegen alle in dieser Reihenfolge untereinander
*
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
uint8_t ui_eingabe(){
    uint8_t ui_bufferPF = 0x00, ui_bufferPB = 0x00, ui_buttons = 0x00;
    ui_bufferPF = ~PINF;
    ui_bufferPB = ~PINB;

    ui_buttons |= ((ui_bufferPF & BIT4) << 3);     // Bit 4 -> Bit 7 in ui_buttons
    ui_buttons |= ((ui_bufferPF & BIT5) << 1);     // Bit 5 -> Bit 6 in ui_buttons
    ui_buttons |= ((ui_bufferPF & BIT6) >> 1);     // Bit 6 -> Bit 5 in ui_buttons
    ui_buttons |= ((ui_bufferPF & BIT7) >> 3);     // Bit 7 -> Bit 4 in ui_buttons

    ui_buttons |= ((ui_bufferPB & BIT1) << 2);     // Bit 1 -> Bit 3 in ui_buttons
    ui_buttons |= ((ui_bufferPB & BIT3) >> 1);     // Bit 3 -> Bit 2 in ui_buttons
    ui_buttons |= ((ui_bufferPB & BIT2) >> 1);     // Bit 2 -> Bit 1 in ui_buttons
    ui_buttons |= ((ui_bufferPB & BIT6) >> 6);     // Bit 6 -> Bit 0 in ui_buttons

	return ui_buttons;
}


 /**************************************************************************
* NAME:			ui_eingabe
* Description:		Die Funktionen fragen beim Aufruf die zugehörigen Pins ab.
* 			Sie geben eine 0x01 zurück, falls die Taste gedrückt ist. ansonten = 0x00
* 			Es findet bisher kein Entprellen statt.
* 			Auslesen der  Eingabetasten (PortB und  PortF).
*                     	Man geht davon aus, dass die Tasten AKTIVE LOW sind.
*
* Subroutines Called:	keine
*
* Returns:		uint8_t ui_buttons;
*                      	Bit 0-3 -> player 1
*                     		Bit 4-7 -> player 2
*                         	Bit 0/4 -> Left
*                         	Bit 1/5 -> Right
*                         	Bit 2/6 -> Up
*                         	Bit 3/7 -> Down
*
* Globals:		keine
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:	
* 	Vergabe der  Pins:
*        Spieler 1:  Richtung - Port - Pin (Anschluss)
*                    Left     - PF4  - A3
*                    Right    - PF5  - A2
*                    Up       - PF6  - A1
*                    Down     - PF7  - A0
*                    (A6 bis A9 sind als analoge Eing�nge verf�gbar)
*        Spieler 2:
*                    Left     - PB1  - 15
*                    Right    - PB3  - 14
*                    Up       - PB2  - 16
*                    Down     - PB6  - 10
*    	Die Pins liegen alle in dieser Reihenfolge untereinander
*
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
uint8_t ui_player1_L() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & BIT4) >0) return TRUE;
	else return FALSE;
}
uint8_t ui_player1_R() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & BIT5) >0) return TRUE;
	else return FALSE;
}
uint8_t ui_player1_U() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & BIT6) >0) return TRUE;
	else return FALSE;
}
uint8_t ui_player1_D() {
    	uint8_t ui_bufferPF = 0x00;
    	ui_bufferPF = ~PINF;
	if((ui_bufferPF & BIT7) >0) return TRUE;
	else return FALSE;
}

uint8_t ui_player2_L() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & BIT1) >0) return TRUE;
	else return FALSE;
}
uint8_t ui_player2_R() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & BIT3) >0) return TRUE;
	else return FALSE;
}
uint8_t ui_player2_U() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & BIT2) >0) return TRUE;
	else return FALSE;
}
uint8_t ui_player2_D() {
	uint8_t  ui_bufferPB = 0x00;
	ui_bufferPB = ~PINB;
	if((ui_bufferPB & BIT6) >0) return TRUE;
	else return FALSE;
}
