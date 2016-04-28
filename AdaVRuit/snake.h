/***************************************************************************** 
* 
* Datei: 		snake.h 
* Kurs:			TEN14 
* Projekt:		Spielekonsole 
* Modul:		Zentrale Einheit 
* 
* Beschreibung:	Diese Datei enthält die Hauptroutine und alle Funktionen des Spiels "Snake"
* 
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Tobias Mages, Christian Wagner 
* 				 
* 
* Datum: 		28.04.2016 
* 
*****************************************************************************/ 
#ifndef _SNAKE_H_
#define _SNAKE_H_

/*************** 
* INCLUDES 
***************/
#include "main.h"

#include <avr/interrupt.h>

/***********************
 * DEFINES UND MAKROS
 ***********************/
//Richtungen der Schlange
#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

/* Verknüpfung mit Eingabefunktionen aus AdaVRuit.h */
#define b_player_L	b_player1_L
#define b_player_R	b_player1_R

#define MAX_LENGTH 20

/****************
 * FUNKTIONEN
 ****************/
 
/*****************************************************************************  
* Name:			playSnake  
* Beschreibung:		Hauptroutine des Spiels Snake  
*  
* Subroutinen:		_delay_ms() aus <util/delay.h>	  
* 			initSnake() 
*       random()
*       PartOfSnake()
*       makeFood()
* 			ui_input() aus AdaVRuit.h  
* 			checkButtons()  
* 			nextstep()  
* 			drawSnake()  
* 			  
* Rückgabewert:		keine  
*  
* Globale Var.:		int8_t ui_timerFlag:  aus AdaVRuit.h  
*   
******************************************************************************/  
void playSnake();

#endif
