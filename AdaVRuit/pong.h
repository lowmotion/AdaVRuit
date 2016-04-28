/*****************************************************************************
*
* Datei: 		pong.h
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Spiel Pong
*
* Beschreibung:	Diese Datei enthällt die Hauptroutine und alle Funktionen des
* 				Spiels "Pong"
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/

#ifndef PONG_H_
#define PONG_H_

/***************
 * INCLUDES
 ***************/
#include "main.h"
#include <avr/interrupt.h>
#include <avr/delay.h>

/*******************
 * DEFINES
 *******************/
#ifndef ROWS
#warning "ROWS is not defined. Default = 8"
#define ROWS 		8	// Anzahl der Zeilen des Spielfelds in Pixeln
#endif

#ifndef COLUMNS
#warning "COLUMNS is not defined. Default = 16"
#define COLUMNS 	16	// Anzahl der Spalten ders Spielfelds in Pixeln
#endif

#define BAT_WIDTH 	3	// Breite der Schläger der Spieler in Pixeln

#define FIRST_LINE		0			// Index der ersten Zeile
#define LAST_LINE		ROWS - 1	// Index der letzten Zeile
#define FIRST_COLUMN	0			// Index der ersten Spalte
#define LAST_COLUMN		COLUMNS - 1	// Index der letzten Spalte

#define TIMER_START		53000
#define TIMER_MAX		63000
#define TIMER_STEPSIZE	100

#define MAX_SCORE	3

/*****************************************************************************
* Name:				playPong
* Beschreibung:		Hauptroutine des Spiels Pong
*
* Subroutinen:		_delay_ms() aus <util/delay.h>	
* 					initPong()
* 					ui_input() aus AdaVRuit.h
* 					processInput()
* 					calcBallPosition()
* 					printPong()
* 					sei() aus <avr/io.h>
*
* Rückgabewert:		keine
*
* Globale Var.:		int8_t ui_timerFlag:  aus AdaVRuit.h
* 
******************************************************************************/
void playPong();


#endif /* PONG_H_ */
