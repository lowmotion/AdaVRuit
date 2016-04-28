/*****************************************************************************
*
* Datei: 		menu.h
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Menü
*
* Beschreibung:	Enthält alle für das Menü erforderlichen Funktionen und
* 				Datenstrukturen
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/
#ifndef MENU_H_
#define MENU_H_

#include "main.h"
#include <avr/delay.h>

/* Konstanten */

#define MENU_ENTRIES 3

/* Funktionen */

/*****************************************************************************
* Name:			menu
* Beschreibung:	Gibt ein Menü aus. Mit den "left"- und "right"-Tastern von
* 				Player 1 lässt sich durch verschiedene Menüpunkte blättern.
* 				Die Menüpunkte sind animiert und stellen das zu erwartende
* 				Spiel dar. Durch Drücken des "up"-Tasters von Player 1 wird
* 				der aktuelle Menüpunkt gestartet.
*
* Subroutinen:	printArray aus AdaVRuit.h
*				ui_player1_L aus AdaVRuit.h
*				ui_player1_R aus AdaVRuit.h
*				ui_player1_U aus AdaVRuit.h
*				playPong aus pong.h
*				playTetris aus tetris.h
*				playSnake aus snake.h
*				twinkelLeftCursor
*				twinkelRightCursor
*				clearDisplay aus AdaVRuit.h
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void menu();

#endif /* MENU_H_*/

