/*
 * pong.h
 *
 *  Created on: Feb 11, 2016
 *      Author: marco
 */

#ifndef PONG_H_
#define PONG_H_

#include "main.h"

/* Konstanten */
#define ROWS 		8	// Anzahl der Zeilen des Spielfelds in Pixeln
#define COLUMNS 	16	// Anzahl der Spalten ders Spielfelds in Pixeln
#define BAT_WIDTH 	3	// Breite der Schläger der Spieler in Pixeln

#define FIRST_LINE		0			// Index der ersten Zeile
#define LAST_LINE		ROWS - 1	// Index der letzten Zeile
#define FIRST_COLUMN	0			// Index der ersten Spalte
#define LAST_COLUMN		COLUMNS - 1	// Index der letzten Spalte

/* Funktionen */
void playPong();


#endif /* PONG_H_ */
