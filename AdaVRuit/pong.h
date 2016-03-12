 /*****************************************************************************
*
* FILE: 		      pong.h
* PROJECT:	      Spielekonsole
* MODULE:		      ???
*
* Description:		Header zu pong.c
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date:   11.02.2016
* BY:	    Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/

#ifndef PONG_H_
#define PONG_H_

#include "main.h"

#include <avr/interrupt.h>

/* Konstanten */
#define ROWS 		8	// Anzahl der Zeilen des Spielfelds in Pixeln
#define COLUMNS 	16	// Anzahl der Spalten ders Spielfelds in Pixeln
#define BAT_WIDTH 	3	// Breite der Schläger der Spieler in Pixeln

#define FIRST_LINE		0			// Index der ersten Zeile
#define LAST_LINE		ROWS - 1	// Index der letzten Zeile
#define FIRST_COLUMN	0			// Index der ersten Spalte
#define LAST_COLUMN		COLUMNS - 1	// Index der letzten Spalte

#define TIMER_START		53000
#define TIMER_MAX		63000
#define TIMER_STEPSIZE	100

#define MAX_SCORE	9

/* Funktionen */
void playPong();


#endif /* PONG_H_ */
