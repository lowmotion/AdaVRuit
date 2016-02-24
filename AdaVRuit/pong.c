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


/*	Struktur: 		Ball
 * 	Beschreibung: 	Diese Struktur stellt den Spielball dar.
 */
struct Ball {
	uint8_t posX, posY, prevX, prevY;
};

/*	Struktur: 		Player (Spieler)
 * 	Beschreibung: 	Diese Struktur stellt einen Spieler dar.
 */
struct Player {
	uint8_t posX, posY, prevX, prevY, width, goals;
};

/* Globale Variablen */

struct Ball ball;
struct Player playerL, playerR;


/* Funktion: 		initPong
 * Beschreibung: 	Diese Funktion initialisiert das Spiel Pong. Es werden zwei Spieler initialisiert
 * 					und auf dem Spielfeld positioniert. Jeweils links und rechts oben in den Ecken.
 * 					Außerdem wird der Spielball so positioniert, dass der linke Spieler anfängt. (Zeile 4 Spalte 8)
 */
void initPong() {

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

/*	Funktion: 		Timer Interrupt Service Routine
 * 	Beschreibung: 	Der Timer zählt eine gewisse Zeit X hoch. Wenn der Interrupt ??? auftritt wird
 * 					diese Funktion aufgerufen, die die neue Position von dem Spielball berechnet.
 *
 */
ISR(TIMER0_COMP_vect) {
	calcBallPosition();
}

/* Funktion:		calcBallPosition
 * Beschreibung:	Berechnet die Position des Balls neu. Hierbei werden die derzeitige Bewegungsrichtung
 * 					des Balls, Wände und Schläger der Spieler berücksichtigt. Falls der Ball eine der
 * 					Seitenwände erreicht, wird die Funktion Goal() aufgerufen, da ein Tor gefallen ist.
 *
 */
void calcBallPosition() {
	// Derzeitige Bewegungsrichtung
	uint8_t movX, movY;				// kein unsigned, da +/-
	movX = ball.posX - ball.prevX;
	movY = ball.posY - ball.prevY;

	// Überschreiben der alten Positionswerte
	ball.prevX = ball.posX;
	ball.prevY = ball.posY;


	// Testen des linken Randes
	if(ball.prevX == FIRST_COLUMN+1){
		if(playerL.posY == ball.prevY - 1) {movX = +1; movY = +1;}
		else if(playerL.posY == ball.prevY) {movX = +1; movY = 0;}
		else if(playerL.posY == ball.prevY + 1) {movX = +1; movY = -1;}
		else {
			Goal(playerR);
			return;		// Beendet die Funktion calcBallPosition, da in Goal() neu initialisiert wird
		}
	}

	// Testen des rechten Randes
	if(ball.prevX == LAST_COLUMN-1){
		if(playerR.posY == ball.prevY - 1) {movX = -1; movY = +1;}
		else if(playerR.posY == ball.prevY) {movX = -1; movY = 0;}
		else if(playerR.posY == ball.prevY + 1) {movX = -1; movY = -1;}
		else {
			Goal(playerL);
			return;		// Beendet die Funktion calcBallPosition, da in Goal() neu initialisiert wird
		}
	}

	/*	ALLE Eckpunkte werden Abgedeckt, da dort die R�nder dominierend sind und movY im folgenden �berschreiben k�nnen. */

	// Testen des oberen Randes
	if(ball.prevY == FIRST_LINE){
		movY = +1;
	}

	// Testen des unteren Randes
	if(ball.prevY == LAST_LINE){
		movY = -1;
	}

	// Berechnung der neuen Position
	ball.posX = ball.prevX + movX;
	ball.posY = ball.prevY + movY;
};

/*
 * Funktion:		Goal
 * Beschreibung:	Diese Funktion incrementiert den Spielstand (Variable goal im struct)
 * 					des übergebenen Spielers. Der Ball wird zurückgesetzt und die vorherige
 * 					Position wird so gesetzt, dass Ball sich als erstes wieder in die Richtung
 * 					des Spielers bewegt, der keinen Punkt gemacht hat. Somit Aufschlag hat.
 */
void Goal(struct Player player){
	// Punkt z�hlen f�r Spieler player

	// verr�ckte Ausgabe machen, dass ein Punkt gefallen ist

	// Spielball neu Initialisieren

};


void playPong() {
	short play = 1;

	initPong();

	while(play) {
		printGameBoard();
		inputUserControls();


		//play = 0;
	}
}


