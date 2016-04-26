/*****************************************************************************
*
* Datei: 		AdaVRuit.c
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Zentrale Einheit
*
* Beschreibung:	Dieses Modul stellt die Zentrale Einheit der Spielekonsole dar.
* 				Es liefert Funktionen zur Ein- und Ausgabe und einen Timer, um
* 				Anwendungen und Spiele zu Takten.
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/

#include "AdaVRuit.h"

/*****************************************************************************
 * Name:			matrix
 * Beschreibung:	Diese Matrix representiert die derzeitige Ausgabe auf den
 * 					LEDs. Sie besitzt acht Zeilen und zwei Spalten mit jeweils
 * 					16 Bit. Jedes einzelne Bit ist also eine LED.
 * 					16 Spalten x 8 Reihen
 *****************************************************************************/
uint16_t matrix[8] = {};

/*****************************************************************************
 * Name:			ui_timerFlag
 * Beschreibung:	Diese Variable wird gesetzt, wenn ein Timerüberlauf
 * 					eintritt. Sie muss von der Anwendung selbst, nach
 * 					Abarbeitung, zurückgesetzt werden.
 *****************************************************************************/
volatile uint8_t ui_timerFlag = 0;
/*****************************************************************************
 * Name:			ui_timerOffset
 * Beschreibung:	Diese Variable bestimmt wie lange der Timer läuft. Der
 * 					maximale Wert und damit die kürzeste Zeit ist
 * 					UINT16_MAX = 65536. Um eine bestimmte Zeit zu erzeugen,
 * 					kann folgende Formel verwendet werden:
 * 						ui_timerOffset = UINT16_MAX-(X*(F_CPU/1024))
 * 					X ist dabei die Anzahl der Sekunden (kann auch z.B. 2,4
 * 					sein).
 * 					X kann maximal = UINT16_MAX/(F_CPU/1024)= 4,19 s sein
 *****************************************************************************/
volatile uint16_t ui_timerOffset = 0;

/*****************************************************************************
* Name:			initATMega
* Beschreibung:	Initialisierung der Ein- und Ausgänge des ATmega32U4
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void initATmega() {
	/* Taster */
    DDRB = 0b00000000;       // Eingänge PortB 1 3 2 6
    DDRF = 0b00000000;       // Eingänge PortF 4 5 6 7

    /* Pullup aktivieren */
    PORTB = 0xFF;
    PORTF = 0xFF;
}


/*****************************************************************************
* Name:			initTWI
* Beschreibung:	Initialisierung des Two-Wire-Interface (I²C)
*
* Subroutinen:	twi_init() aus twi.h
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void initTWI() {
	twi_init();
}

/*****************************************************************************
* Name:			clearDisplay
* Beschreibung:	Setzt das Display zurück und schreibt 0 in die matrix.
*
* Subroutinen:	twi_start() aus twi.h
* 				twi_write() aus twi.h
* 				twi_stop() aus twi.h
*
* Rückgabewert:	keine
*
* Globale Var.:	matrix
******************************************************************************/
void clearDisplay() {
	cli();
	twi_start(SLAVE_ADRESS);
	twi_write(0x00);	// Startadresse des Displayspeichers
	for(short row = 0; row < 8; row++) {
		for(short column = 0; column < 2; column++) {
			matrix[row] = 0;
			twi_write(0);
		}
	}
	twi_stop();
	sei();
}


/*****************************************************************************
* Name:			initDisplay
* Beschreibung:	Initialisiert den LED Treiber HT16K33 und stellt die
* 				Helligkeit des ein.
*
* Subroutinen:	twi_start() aus twi.h
* 				twi_write() aus twi.h
* 				twi_stop() aus twi.h
* 				clearDisplay()
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void initDisplay(uint8_t brightness) {
	/* LED Treiber anschalten */
	twi_start(SLAVE_ADRESS);
	twi_write(0x21);
	twi_stop();

	/* Helligkeit des Displays einstellen */
	if(brightness > 15) {
		twi_start(SLAVE_ADRESS);
		twi_write(0xEF);
		twi_stop();
	} else {
		twi_start(SLAVE_ADRESS);
		twi_write(0xE0+brightness);
		twi_stop();
	}

	clearDisplay();

	/* Display anschalten */
	twi_start(SLAVE_ADRESS);
	twi_write(0x81);
	twi_stop();
}

/*****************************************************************************
* Name:			initTimer
* Beschreibung:	Initialisiert den Timer1 des ATmegas auf Interrupt bei
* 				Überlauf des Timers. Anfangswert ist eine Sekunde
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	Interrupt-Flag
* 				ui_timerOffset
******************************************************************************/
void initTimer() {
	/* Timer/Counter1 Overflow*/

	/* Global Interrupts aktivieren */
	ENABLE_GLOBAL_INT();

	/* Overflow Interrupt aktivieren */
	TIMER1_OVERFLOW_INT_ENABLE();

	/* Startwert des Timers setzen */
	ui_timerOffset = UINT16_MAX-(F_CPU/1024); // 1 Sekunde
	TCNT1 = ui_timerOffset;

	/* Clock Prescaler auf clk/1024
	 * incrementiert 15625 mal pro Sekunde */
	TIMER1_CPU_DIV_1024();
}

/*****************************************************************************
* Name:			ISR(TIMER1_OVF_vect)
* Beschreibung:	Läuft der Timer1 über und Globale Interrupts sind erlaubt,
* 				wird die Timerflag gesetzt und der Timer zurückgesetzt auf
* 				den Wert vom Timeroffset. Um diesen Timer zu nutzen: Auf das
* 				Timerflag prüfen und danach auf 0 setzen. Die Länge des TImers
* 				kann über den Timeroffset bestimmt werden.
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	ui_timerFlag
* 				ui_timerOffset
******************************************************************************/
ISR(TIMER1_OVF_vect) {
	/* Disable Interrupts */
	cli();
	ui_timerFlag = 1;
	TCNT1 = ui_timerOffset;
	sei();
}

/*****************************************************************************
* Name:			ISR(_vector_default)
* Beschreibung:	Interupt Service Routine für nicht bestimmte Interrupts.
* 				Hat nur die Funktion nicht gewollte Interrupts abzufangen.
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
ISR(__vector_default) {

}

/*****************************************************************************
* Name:			initSystem
* Beschreibung:	Initialisiert das gesamte System
*
* Subroutinen:	initATmega()
*				initTWI()
*				initDisplay()
*				initTimer()
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void initSystem() {
	initATmega();
	initTWI();
	initDisplay(LED_BRIGHTNESS);
	DISABLE_WATCHDOG();
	initTimer();
}

/*****************************************************************************
* Name:			printBit
* Beschreibung:	Ändert ein bestimmtes Bit in der LED Matrix.
* 				Adressierung:
* 					Zeilen: 	0 bis 7
* 					Spalten: 	0 bis 15
*
* Subroutinen:	twi_start() aus twi.h
* 				twi_write() aus twi.h
* 				twi_stop() aus twi.h
*
* Rückgabewert:	keine
*
* Globale Var.:	matrix
******************************************************************************/
void printBit(uint8_t ui_row, uint8_t ui_column, uint8_t ui_ledState) {
	cli();
	uint8_t highByte = 0;
	switch(ui_ledState) {
	case LED_OFF:
		if(ui_column > 7) {
			matrix[ui_row] &= ~(1 << (ui_column));
			highByte = TRUE;
		} else {
			matrix[ui_row] &= ~(1 << ui_column);
			highByte = FALSE;
		}
		twi_start(SLAVE_ADRESS);
		twi_write((ui_row*2)+highByte);
		twi_write(matrix[ui_row] >> (highByte * 8));
		twi_stop();
		break;
	case LED_ON:
		if(ui_column > 7) {
			matrix[ui_row] |= (1 << (ui_column));
			highByte = 1;
		} else {
			matrix[ui_row] |= (1 << ui_column);
			highByte = 0;
		}
		twi_start(SLAVE_ADRESS);
		twi_write((ui_row*2)+highByte);
		twi_write(matrix[ui_row] >> (highByte * 8));
		twi_stop();
		break;
	}
	sei();

}

/*****************************************************************************
* Name:			printArray
* Beschreibung:	Gibt ein ganzes Array vom Format 8 Zeilen x 16 Bit pro Zeile
* 				auf dem Display aus.
*
* Subroutinen:	twi_start() aus twi.h
* 				twi_write() aus twi.h
* 				twi_stop() aus twi.h
*
* Rückgabewert:	keine
*
* Globale Var.:	matrix
******************************************************************************/
void printArray(uint16_t ui_matrix[8]) {
	cli();
	uint16_t bitSwappedByte[8];
	for(short row =0; row < 8; row++) {
		matrix[row] = ui_matrix[row];
		uint16_t inputByte = ui_matrix[row];
		bitSwappedByte[row] = 0;
		for (short i = 0; i < 16; i++ ) {
		  bitSwappedByte[row] >>= 1;
		  bitSwappedByte[row] |= ( inputByte & 0x8000 );
		  inputByte <<= 1;
		}
	}

	twi_start(SLAVE_ADRESS);
	twi_write(0x00);	// Startadresse des Displayspeichers
	for(short row = 0; row < 8; row++) {
		twi_write(bitSwappedByte[row]);
		twi_write(bitSwappedByte[row] >> 8);
	}
	twi_stop();
	sei();
}

/*****************************************************************************
* Name:			printVerticalArray
* Beschreibung:	Gibt ein ganzes Array vom Format 16 Spalten x 8 Bit pro Zeile
* 				auf dem Display aus. Diese Funktion wandelt das Array erst um
* 				und nutzt dann die printArray Funktion.
*
* Subroutinen:	twi_start() aus twi.h
* 				twi_write() aus twi.h
* 				twi_stop() aus twi.h
* 				printArray()
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void printVerticalArray(uint8_t board[16]) {
	uint16_t newBoard[8] = {0};
	for (uint8_t k = 0; k < 8; k++)
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			newBoard[k] |= (((board[i] >> (7-k)) & 1) << (15-i));
		}
	}
	printArray(newBoard);
}

/*****************************************************************************
* Name:			ui_getBit
* Beschreibung:	Diese Funktion gibt den Werte des Bits an der gefragten Stelle
* 				in der Matrix wieder.
*
* Subroutinen: 	keine
*
* Rückgabewert:	uint8_t: 1 oder 0
*
* Globale Var.:	keine
******************************************************************************/
uint8_t ui_getBit(uint8_t ui_row, uint8_t ui_column) {
	return (uint8_t)((matrix[ui_row] >> (15 - ui_column) ) & 1);
}

/*****************************************************************************
* Name:			b_playerX_Y
* Beschreibung:	Diese Funktionen geben zurück, ob ein bestimmter Spieler eine
* 				bestimmte Taste in der übergebenen Variable gedrückt hat.
*
* Subroutinen: 	keine
*
* Rückgabewert:	uint8_t: 1 wenn gedrückt oder 0 wenn nicht gedrückt
*
* Globale Var.:	keine
******************************************************************************/
uint8_t b_player1_L(uint8_t _ui_buttons) {return ((_ui_buttons & BIT7) >> 7);}
uint8_t b_player1_R(uint8_t _ui_buttons) {return ((_ui_buttons & BIT6) >> 6);}
uint8_t b_player1_U(uint8_t _ui_buttons) {return ((_ui_buttons & BIT5) >> 5);}
uint8_t b_player1_D(uint8_t _ui_buttons) {return ((_ui_buttons & BIT4) >> 4);}
uint8_t b_player2_L(uint8_t _ui_buttons) {return ((_ui_buttons & BIT3) >> 3);}
uint8_t b_player2_R(uint8_t _ui_buttons) {return ((_ui_buttons & BIT2) >> 2);}
uint8_t b_player2_U(uint8_t _ui_buttons) {return ((_ui_buttons & BIT1) >> 1);}
uint8_t b_player2_D(uint8_t _ui_buttons) {return (_ui_buttons & BIT0);}

/*****************************************************************************
* Name:			resetplayerX_Y
* Beschreibung:	Diese Funktionen setzt das jeweilige Bit für die gedrückte
* 				Taste in der übergebenen Variable zurück.
*
* Subroutinen: 	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void resetPlayer1_L(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT7);}
void resetPlayer1_R(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT6);}
void resetPlayer1_U(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT5);}
void resetPlayer1_D(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT4);}
void resetPlayer2_L(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT3);}
void resetPlayer2_R(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT2);}
void resetPlayer2_U(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT1);}
void resetPlayer2_D(uint8_t *_ui_buttons) {(*_ui_buttons &= ~BIT0);}

/*****************************************************************************
* Name:			ui_input
* Beschreibung:	Auslesen der  Eingabetasten (PortB und  PortF).
*               Man geht davon aus, dass die Tasten AKTIVE LOW sind.
*               Es wurden Funktionen definiert, um direkt die Richtungen
*               abzufragen.
*               Vergabe der  Pins:
*        			Spieler 1:  Richtung - Port - Pin (Anschluss)
*                    		Left     - PF4  - A3
*                    		Right    - PF5  - A2
*                    		Up       - PF6  - A1
*                    		Down     - PF7  - A0
*                    		(A6 bis A9 sind als analoge Eing�nge verf�gbar)
*        			Spieler 2:
*                   		Left     - PB1  - 15
*                    		Right    - PB3  - 14
*                    		Up       - PB2  - 16
*                    		Down     - PB6  - 10
*    			Die Pins liegen alle in dieser Reihenfolge untereinander
*
* Subroutinen: 	keine
*
* Rückgabewert:	uint8_t: ui_buttons;
*                      		Bit 0-3 -> player 1
*                     		Bit 4-7 -> player 2
*                         	Bit 0/4 -> Left
*                         	Bit 1/5 -> Right
*                         	Bit 2/6 -> Up
*                         	Bit 3/7 -> Down
*
* Globale Var.:	keine
******************************************************************************/
uint8_t ui_input(){
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

/*****************************************************************************
* Name:			ui_playerX_Y
* Beschreibung:	Die Funktionen fragen beim Aufruf die zugehörigen Pins ab.
* 				Sie geben eine 0x01 zurück, falls die Taste gedrückt ist.
* 				ansonten = 0x00. Es findet bisher kein Entprellen statt.
* 				Auslesen der  Eingabetasten (PortB und  PortF).
*           	Man geht davon aus, dass die Tasten AKTIVE LOW sind.
*               Vergabe der  Pins:
*        			Spieler 1:  Richtung - Port - Pin (Anschluss)
*                    		Left     - PF4  - A3
*                    		Right    - PF5  - A2
*                    		Up       - PF6  - A1
*                    		Down     - PF7  - A0
*                    		(A6 bis A9 sind als analoge Eing�nge verf�gbar)
*        			Spieler 2:
*                   		Left     - PB1  - 15
*                    		Right    - PB3  - 14
*                    		Up       - PB2  - 16
*                    		Down     - PB6  - 10
*    			Die Pins liegen alle in dieser Reihenfolge untereinander
*
* Subroutinen: 	keine
*
* Rückgabewert:	uint8_t: ui_buttons;
*                      		Bit 0-3 -> player 1
*                     		Bit 4-7 -> player 2
*                         	Bit 0/4 -> Left
*                         	Bit 1/5 -> Right
*                         	Bit 2/6 -> Up
*                         	Bit 3/7 -> Down
*
* Globale Var.:	keine
******************************************************************************/
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
