#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "main.h"

#include <avr/interrupt.h>

/***********************
 * Defines und Makros
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
 * Funktionen
 ****************/
void playSnake();

#endif
