/*
 * pong.c
 *
 *      Author: marco
 *      File:
 *      Project:
 *      Module:
 *
 *      Description:
 *
 *      Created on: Feb 11, 2016
 */

#include "pong.h"


#define ROWS 8
#define COLUMNS 16
#define BAT_WIDTH 3


/*	Struktur: Ball
 * 	Beschreibung: Diese Struktur stellt den Spielball dar.
 */
struct Ball {
	uint8_t posX, posY, prevX, prevY;
};

/*	Struktur: Player (Spieler)
 * 	Beschreibung: Diese Struktur stellt einen Spieler dar.
 */
struct Player {
	uint8_t posX, posY, prevX, prevY, width;
};



/** Funktion: initPong
 * 	Beschreibung: Diese Funktion initialisiert das Spiel Pong. Es werden zwei Spieler erstellt
 * 		und auf dem Spielfeld positioniert. Jeweils links und rechts oben in den Ecken. Außerdem
 * 		wird der Spielball so positioniert, dass der linke Spieler anfängt. (Zeile 4 Spalte 8)
 */
void initPong() {
	struct Ball ball = { 4, 8};
	struct Player player1 = {0, 0, BAT_WIDTH};
	struct Player player2 = {0, 7, BAT_WIDTH};
}

/*
 *
 */
void printGameBoard() {

}

/*
 *
 */
void inputUserControls() {

}

/*	Funktion: Timer Interrupt Service Routine
 * 	Beschreibung: Der Timer zählt eine gewisse Zeit X hoch. Wenn der Interrupt ??? auftritt wird
 * 		diese Funktion aufgerufen, die die neue Position von dem Spielball berechnet.
 *
 */
ISR(TIMER0_COMP_vect) {
	calcBallPosition();
}

/*
 *
 */
void calcBallPosition() {

}


void playPong() {
	short play = 1;

	initPong();

	while(play) {
		printGameBoard();
		inputUserControls();


		//play = 0;
	}
}


