/*****************************************************************************
*
* Datei: 		pong.c
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
#include "pong.h"


 /*****************************************************************************
 * Name:			Ball
 * Beschreibung:	Diese Struktur stellt den Spielball dar und beinhaltet
 * 					sowohl seine aktuelle, als auch seine vorherige Position
 *****************************************************************************/
struct Ball {
	uint8_t posX, posY, prevX, prevY;
};


 /*****************************************************************************
 * Name:			Player
 * Beschreibung:	Diese Struktur stellt einen Spieler dar.
 * 					Sie enthällt die Informationen über die derzeitige und
 * 					vorherige Schlägerposition, sowie dessen Breite.
 * 					Zusätzlich wird darin gespeichter, ob der Bot aktiv ist
 * 					und die erzielten Punkte des Spielers gezählt.
 *****************************************************************************/
struct Player {
	uint8_t posX, posY, prevX, prevY, width, score, bot;
};


/**************************
 * GLOBALE VARIABLEN
 **************************/
 
struct Ball s_ball;
struct Player s_playerL, s_playerR;



/*****************************************************************************
* Name:				Goal
* Beschreibung:		Diese Funktion incrementiert den Spielstand (Variable
* 					score im struct) des übergebenen Spielers. Die Ballposition
* 					wird zurückgesetzt und die vorherige Position wird so
* 					gesetzt, dass Ball sich als erstes wieder in die Richtung
* 					des Spielers bewegt, der keinen Punkt gemacht hat.
* 					Somit Aufschlag hat.
*
* Subroutinen:		clearDisplay() aus AdaVRuit_Font.h;
*					printCharacters() aus AdaVRuit_Font.h
*					_delay_ms() aus <util/delay.h>
*
* Rückgabewert:		uint8_t: 1 oder 0
*
* Globale Var.:		struct Ball ball;
*					struct Player playerL, playerR;
* 					uint8_t ui_timerOffset, ui_timerFlag  aus AdaVRuit.h
******************************************************************************/
uint8_t ui_Goal(uint8_t player){
	clearDisplay();
	printCharacters('T', 'O', 'R');
	_delay_ms(1500);

	/* Score für player erhöhen und Spielball zurücksetzen.
	 * Der Spieler der kein Tor gemacht hat hat nun Aufschlag
	 */
	switch(player) {
		case 0:
			s_playerL.score++;
			if(s_playerL.score == MAX_SCORE) {
				printCharacters(s_playerL.score + 48, ':', s_playerR.score +48);
				_delay_ms(1500);
				printCharacters('W', 'I', 'N');
				_delay_ms(2000);
				return 0;
			}
			/* Ball zurücksetzen */
			s_ball.posX = 8;
			s_ball.posY = 4;
			s_ball.prevX = 7;
			ball.prevY = 4;
			/* Spielerpositionen zurücksetzen */
			s_playerL.prevX = s_playerL.posX;
			s_playerL.prevY = s_playerL.posY;
			s_playerR.prevX = s_playerR.posX;
			s_playerR.prevY = s_playerR.posY;
			break;
		case 1:
			s_playerR.score++;
			if(s_playerR.score == MAX_SCORE) {
				printCharacters(s_playerL.score + 48, ':', s_playerR.score +48);
				_delay_ms(1500);
				printCharacters('W', 'I', 'N');
				_delay_ms(2000);
				return 0;
			}
			/* Ball zurücksetzen */
			s_ball.posX = 7;
			s_ball.posY = 4;
			s_ball.prevX = 8;
			ball.prevY = 4;
			/* Spielerpositionen zurücksetzen */
			s_playerL.prevX = s_playerL.posX;
			s_playerL.prevY = s_playerL.posY;
			s_playerR.prevX = s_playerR.posX;
			s_playerR.prevY = s_playerR.posY;
			break;
	}

	printCharacters(s_playerL.score + 48, ':', playerR.score +48);
	_delay_ms(1500);
	clearDisplay();
	/* Timer für die Spielgeschwindigkeit zurücksetzen */
	ui_timerOffset = TIMER_START;
	ui_timerFlag = FALSE;
	return 1;

};



/*****************************************************************************
* Name:				calcBallPosition
* Beschreibung:		Berechnet die Position des Balls neu. Hierbei werden 
* 					die derzeitige Bewegungsrichtung des Balls, Wände und
* 					Schläger der Spieler berücksichtigt. Falls der Ball eine der
* 					Seitenwände erreicht, wird die Funktion Goal() aufgerufen,
* 					da ein Tor gefallen ist.
*
*
* Subroutinen:		ui_Goal();
*
* Rückgabewert:		uint8_t: 1 oder 0
*
* Globale Var.:		struct Ball ball;
*					struct Player playerL, playerR;
******************************************************************************/
uint8_t ui_calcBallPosition() {
	// Derzeitige Bewegungsrichtung
	int8_t movX, movY;				// kein unsigned, da +/-
	movX = s_ball.posX - s_ball.prevX;
	movY = s_ball.posY - ball.prevY;

	// Überschreiben der alten Positionswerte
	s_ball.prevX = s_ball.posX;
	s_ball.prevY = ball.posY;


	// Testen des linken Randes
	if(s_ball.prevX == FIRST_COLUMN+1){
		if(s_playerL.posY == s_ball.prevY - 1) {movX = +1; movY = +1;}
		else if(s_playerL.posY == s_ball.prevY) {movX = +1; movY = 0;}
		else if(s_playerL.posY == s_ball.prevY + 1) {movX = +1; movY = -1;}
		else {
			return Goal(1);	// Beendet die Funktion calcBallPosition, da in ui_Goal() neu initialisiert wird
		}
	}

	// Testen des rechten Randes
	if(s_ball.prevX == LAST_COLUMN-1){
		if(s_playerR.posY == s_ball.prevY - 1) {movX = -1; movY = +1;}
		else if(s_playerR.posY == s_ball.prevY) {movX = -1; movY = 0;}
		else if(playerR.posY == s_ball.prevY + 1) {movX = -1; movY = -1;}
		else {
			return Goal(0);		// Beendet die Funktion calcBallPosition, da in Goal() neu initialisiert wird
		}
	}

	/*	ALLE Eckpunkte werden Abgedeckt, da dort die R�nder dominierend sind und movY im folgenden �berschreiben k�nnen. */

	// Testen des oberen Randes
	if(s_ball.prevY == FIRST_LINE){
		movY = +1;
	}

	// Testen des unteren Randes
	if(s_ball.prevY == LAST_LINE){
		movY = -1;
	}

	// Berechnung der neuen Position
	s_ball.posX = s_ball.prevX + movX;
	s_ball.posY = s_ball.prevY + movY;
	if(s_playerL.bot) {
		//if(!s_playerL.posY == s_ball.posY) {
		if(s_ball.posY < ROWS && s_ball.posY > 0){
			s_playerL.prevY = playerL.posY;
			playerL.posY = ball.posY-1;
		}
		//}
	}
	if(s_playerR.bot) {
		//if(!s_playerR.posY == s_ball.posY) {
		if(s_ball.posY < ROWS-1 && s_ball.posY >= 0){
			playerR.prevY = playerR.posY;
			playerR.posY = ball.posY+1;
		}
		//}
	}
	return 1;
};



/*****************************************************************************
* Name:				processInput
* Beschreibung:		Verarbeitet die Eingabe der Taster der Spieler und 
* 					bewegt die Schläger nach oben bzw. unten
*
* Subroutinen:		b_player1_U() aus AdaVRuit.h
* 					b_player1_D() aus AdaVRuit.h
* 					b_player1_L() aus AdaVRuit.h
* 					b_player1_R() aus AdaVRuit.h
* 					b_player2_U() aus AdaVRuit.h
* 					b_player2_D() aus AdaVRuit.h
*
* Rückgabewert:		uint8_t: 1 oder 0
*
* Globale Var.:		struct Player playerL, s_playerR;
******************************************************************************/

uint8_t ui_processInput(uint8_t ui_buttons){
	/* Abbruchbedingung */
	if(b_player1_U(ui_buttons) && b_player1_D(ui_buttons) && b_player1_L(ui_buttons) && b_player1_R(ui_buttons)) {
		return 0;
	}

    // Bewegung des linken Schl�gers
    if(b_player1_U(ui_buttons) == 1){                         // Bewegung nach oben
        s_playerL.bot = 0;
    	s_playerL.prevY = s_playerL.posY;
        if(s_playerL.posY > 0) {
			s_playerL.posY -= 1;
		}
    }
    if(b_player1_D(ui_buttons) == 1){                         // Bewegung nach unten
    	s_playerL.bot = 0;
    	s_playerL.prevY = s_playerL.posY;
        if(playerL.posY < (ROWS-1)) {
			s_playerL.posY += 1;
		}
    }

    // Bewegung des rechten Schl�gers
    if(b_player2_U(ui_buttons) == 1){                         // Bewegung nach oben
    	s_playerR.bot = 0;
    	s_playerR.prevY = s_playerR.posY;
        if(s_playerR.posY > 0) {
        	s_playerR.posY -= 1;
        }
    }
    if(b_player2_D(ui_buttons) == 1){                         // Bewegung nach unten
    	s_playerR.bot = 0;
    	playerR.prevY = playerR.posY;
        if(playerR.posY < (ROWS-1)) {
        	playerR.posY += 1;
        }
    }
    return 1;
}



/*****************************************************************************
* Name:				printPong
* Beschreibung:		Diese Funktion gibt die Bewebung des Balles und 
* 					der beiden Schlaeger auf der LED Matrix aus.
*
* Subroutinen:		printBit(); aus AdaVRuit.h
*
* Rückgabewert:		keine
*
* Globale Var.:		struct Ball ball;
*					struct Player playerL, s_playerR;
******************************************************************************/
void printPong(){
    // Ausgabe des Balls
    if(s_ball.posX != s_ball.prevX){                    // Immer, wenn es eine Ballbewegung gibt, findet diese auch in X-Richtung statt. Eine senkrechte  Bewegung nach oben ist unm�glich
        printBit(s_ball.posY, s_ball.posX, LED_ON);
        printBit(s_ball.prevY, s_ball.prevX, LED_OFF);
    } else {
    	printBit(s_ball.posY, s_ball.posX, LED_ON);
    }

    /* Ausgabe der Schläger */
    /* Schläger Links */
    if(s_playerL.posY > s_playerL.prevY) {
    	/* Nach unten verschieben */
    	if((s_playerL.prevY - (s_playerL.width/2)) >= 0) {
			printBit(s_playerL.prevY - (s_playerL.width/2), s_playerL.posX, LED_OFF);
		}
		if((s_playerL.posY + (s_playerL.width/2)) < ROWS) {
			printBit(s_playerL.posY + (playerL.width/2), s_playerL.posX, LED_ON);
		}
    } else if(s_playerL.posY < s_playerL.prevY) {
    	/* Nach oben verschieben */
    	if((s_playerL.posY - (s_playerL.width/2)) >= 0) {
    		printBit(s_playerL.posY - (s_playerL.width/2), s_playerL.posX, LED_ON);
    	}
    	if((s_playerL.prevY + (s_playerL.width/2)) < ROWS) {
    		printBit(playerL.prevY + (playerL.width/2), s_playerL.posX, LED_OFF);
    	}
    } else {
    	/* Spieler an aktueller Position zeichnen */
    	printBit(s_playerL.posY, s_playerL.posX, LED_ON);
    	for(short width = s_playerL.width; width > 1; width-=2) {
    		if((s_playerL.posY - (width/2)) >= 0) {
    			printBit(s_playerL.posY - (width/2), s_playerL.posX, LED_ON);
    		}
    		if((s_playerL.posY + (width/2)) < ROWS) {
    			printBit(s_playerL.posY + (width/2), s_playerL.posX, LED_ON);
    		}
    	}
    }


    /* Schläger Rechts */
    if(s_playerR.posY > s_playerR.prevY) {
		/* Nach unten verschieben */
		if((s_playerR.prevY - (s_playerR.width/2)) >= 0) {
			printBit(s_playerR.prevY - (playerR.width/2), s_playerR.posX, LED_OFF);
		}
		if((s_playerR.posY + (s_playerR.width/2)) < ROWS) {
			printBit(s_playerR.posY + (s_playerR.width/2), s_playerR.posX, LED_ON);
		}
	} else if(s_playerR.posY < s_playerR.prevY) {
		/* Nach oben verschieben */
		if((s_playerR.posY - (s_playerR.width/2)) >= 0) {
			printBit(playerR.posY - (playerR.width/2), s_playerR.posX, LED_ON);
		}
		if((s_playerR.prevY + (s_playerR.width/2)) < ROWS) {
			printBit(s_playerR.prevY + (s_playerR.width/2), s_playerR.posX, LED_OFF);
		}
	} else {
		/* Spieler an aktueller Position zeichnen */
		printBit(s_playerR.posY, s_playerR.posX, LED_ON);
		for(short width = s_playerR.width; width > 1; width -= 2) {
			if((s_playerR.posY - (width/2)) >= 0) {
				printBit(playerR.posY - (width/2), playerR.posX, LED_ON);
			}
			if((playerR.posY + (width/2)) < ROWS) {
				printBit(playerR.posY + (width/2), playerR.posX, LED_ON);
			}
		}
	}
}



/*****************************************************************************
* Name:				initPong
* Beschreibung:		Diese Funktion initialisiert das Spiel Pong. Es 
* 					werden zwei Spieler initialisiert und auf dem Spielfeld
* 					positioniert. Jeweils links und rechts oben in den Ecken.
* 					Außerdem wird der Spielball so positioniert, dass der
* 			l		inke Spieler anfängt. (Zeile 4 Spalte 8)
*
* Subroutinen:		clearDisplay()
*					printPong() aus AdaVRuit.h
*
* Rückgabewert:		keine
*
* Globale Var.:		SREG: aus <avr/io.h>
* 					struct Ball ball
*					struct Player playerL, s_playerR
* 					uint8_t ui_timerOffset:  aus AdaVRuit.h
******************************************************************************/
void initPong() {
	/* Ball initialisieren */
	s_ball.posX = 7;
	s_ball.posY = 4;
	s_ball.prevX = 8;
	ball.prevY = 5;

	/* Player Links */
	s_playerL.posX = 0;
	s_playerL.posY = 3;
	playerL.prevX = 0;
	s_playerL.prevY = 3;
	s_playerL.width = BAT_WIDTH;
	s_playerL.score = 0;
	s_playerL.bot =1;

	/* Player Links */
	playerR.posX = 15;
	playerR.posY = 5;
	playerR.prevX = 15;
	playerR.prevY = 5;
	playerR.width = BAT_WIDTH;
	playerR.score = 0;
	playerR.bot = 1;

	ui_timerOffset = TIMER_START;

	clearDisplay();
	printPong();

	SREG|=0x80;
}



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
void playPong() {
	_delay_ms(500);
	short play = 1;
	uint8_t ui_buttons = 0;
	initPong();

	//printPong();
	sei();
	while(play) {
        ui_buttons |= ui_input();
		if(ui_timerFlag){
			if(ui_timerOffset < TIMER_MAX) {
				ui_timerOffset += TIMER_STEPSIZE;
			}
			play = ui_processInput(ui_buttons);
			if(!play) {
				_delay_ms(500);
				return;
			}
			play = ui_calcBallPosition();
			ui_buttons = 0;
			printPong();
			ui_timerFlag = 0;
		}
	}
	_delay_ms(500);
}


