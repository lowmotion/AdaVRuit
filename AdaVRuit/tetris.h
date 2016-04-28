/*****************************************************************************
*
* Datei: 		tetris.h
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Spiel
*
* Beschreibung:	Enthält für das Spiel Tetris erforderlichen Funktionen
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/
#ifndef TETRIS_H_
#define TETRIS_H_

#include "main.h"

/****************
* Defines
****************/
#define GAME_SPEED 2
#define FADE_OUT_SPEED 60

/*****************
* Funktionen
*****************/

/*****************************************************************************
* Name:			playTetris
* Beschreibung: Die Hauptfunktion des Spiels Tetris
*
* Subroutinen:	s_newObj
*				s_moveLeft
*				s_moveRight
*				s_rotate
*				ui_player1_R aus AdaVRuit.h
*				ui_player1_L aus AdaVRuit.h
*				ui_player1_U aus AdaVRuit.h
*				ui_player1_D aus AdaVRuit.h
*				lockObj
*				ui_checkRows
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void playTetris();


#endif /* TETRIS_H_*/

