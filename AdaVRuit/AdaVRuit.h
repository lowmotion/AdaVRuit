/*****************************************************************************
*
* Datei: 		AdaVRuit.c
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

#ifndef ADAVRUIT_H_
#define ADAVRUIT_H_

/***************
 * INCLUDES
 ***************/
#include "main.h"
#include <avr/io.h>
#include "twi.h"

/****************
 * MAKROS
 ****************/
#define DISABLE_WATCHDOG()  MCUSR &= ~(1<<WDRF); WDTCSR |= (1<<WDCE) | (1<<WDE); WDTCSR = 0x00
#define TIMER1_CPU_DIV_8() 		TCCR1B|=2
#define TIMER1_CPU_DIV_64() 	TCCR1B|=3
#define TIMER1_CPU_DIV_256() 	TCCR1B|=4
#define TIMER1_CPU_DIV_1024() 	TCCR1B|=5
#define TIMER1_OVERFLOW_INT_ENABLE() TIMSK1 |= (1<<TOIE0)
#define ENABLE_GLOBAL_INT() 	SREG|=0x80
#define DISABLE_GLOBAL_INT() 	SREG&=~(0x80)

/*******************
 * DEFINES
 *******************/
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

#define ROWS 	8
#define COLUMNS 16

/* Helligkeit der LEDs des Displays. Zwischen 0 und 15 */
#ifndef LED_BRIGHTNESS
#warning "LED_BRIGHTNESS was not set for AdaVRuit.h. Default is '7'. Possible between '0' and '15'!"
#endif

/**************************
 * EXTERNE VARIABLEN
 **************************/

/*****************************************************************************
 * Name:			ui_timerFlag
 * Beschreibung:	Diese Variable wird gesetzt, wenn ein Timerüberlauf
 * 					eintritt. Sie muss von der Anwendung selbst, nach
 * 					Abarbeitung, zurückgesetzt werden.
 *****************************************************************************/
extern volatile uint8_t ui_timerFlag;

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
extern volatile uint16_t ui_timerOffset;


/**************************
 * FUNKTIONEN
 **************************/

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
void clearDisplay();

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
void initSystem();

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
void printBit(uint8_t ui_row, uint8_t ui_column, uint8_t ui_ledState);

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
void printArray(uint16_t ui_matrix[8]);

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
void printVerticalArray(uint8_t board[16]);

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
uint8_t ui_getBit(uint8_t ui_row, uint8_t ui_column);

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
uint8_t ui_input();

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
uint8_t ui_player1_L();
uint8_t ui_player1_R();
uint8_t ui_player1_U();
uint8_t ui_player1_D();
uint8_t ui_player2_L();
uint8_t ui_player2_R();
uint8_t ui_player2_U();
uint8_t ui_player2_D();

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
uint8_t b_player1_L(uint8_t _ui_buttons);
uint8_t b_player1_R(uint8_t _ui_buttons);
uint8_t b_player1_U(uint8_t _ui_buttons);
uint8_t b_player1_D(uint8_t _ui_buttons);
uint8_t b_player2_L(uint8_t _ui_buttons);
uint8_t b_player2_R(uint8_t _ui_buttons);
uint8_t b_player2_U(uint8_t _ui_buttons);
uint8_t b_player2_D(uint8_t _ui_buttons);

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
void resetPlayer1_L(uint8_t *_ui_buttons);
void resetPlayer1_R(uint8_t *_ui_buttons);
void resetPlayer1_U(uint8_t *_ui_buttons);
void resetPlayer1_D(uint8_t *_ui_buttons);
void resetPlayer2_L(uint8_t *_ui_buttons);
void resetPlayer2_R(uint8_t *_ui_buttons);
void resetPlayer2_U(uint8_t *_ui_buttons);
void resetPlayer2_D(uint8_t *_ui_buttons);

#endif /* ADAVRUIT_H_ */
