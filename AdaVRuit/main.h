/*****************************************************************************
*
* Datei: 		main.h
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Zentrale Einheit
*
* Beschreibung:	Diese Datei enthält den Startpunkt des Programms und führt
* 				alle Module zusammen.
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU			16000000UL
#define SCL_CLOCK 		100000L
#define SLAVE_ADRESS 	0xE0
#define LED_BRIGHTNESS	5


#include "AdaVRuit.h"
#include "AdaVRuit_Font.h"
#include "menu.h"
#include "pong.h"
#include "tetris.h"
#include "snake.h"

#endif /* MAIN_H_ */
