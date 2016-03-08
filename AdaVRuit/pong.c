
/*****************************************************************************
*
* FILE: 		pong.c
* PROJECT:		Spielekonsole
* MODULE:		???
*
* Description:		Diese Datei enthällt die Hauptroutine und alle Funktionen des Speiels "Pong"
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date: 07.03.2016
* BY:	Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/
 
 

#include "pong.h"


/*	Struktur: 	Ball
 * 	Beschreibung: 	Diese Struktur stellt den Spielball dar.
 */
struct Ball {
	uint8_t posX, posY, prevX, prevY;
};

/*	Struktur: 	Player (Spieler)
 * 	Beschreibung: 	Diese Struktur stellt einen Spieler dar.
 */
struct Player {
	uint8_t posX, posY, prevX, prevY, width, goals;
};


/* Globale Variablen */

struct Ball ball;
struct Player playerL, playerR;
uint8_t ui_timerFlag;


 /**************************************************************************
* NAME:			initPong
* Description:		Diese Funktion initialisiert das Spiel Pong. Es werden zwei Spieler initialisiert
* 			und auf dem Spielfeld positioniert. Jeweils links und rechts oben in den Ecken.
* 			Außerdem wird der Spielball so positioniert, dass der linke Spieler anfängt. (Zeile 4 Spalte 8)
*
* Subroutines Called:	???
*
* Returns:		keine
*
* Globals:		Ball ball; Player playerL, playerR; uint8_t ui_timerFlag;
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void initPong() {

}



/**************************************************************************
* NAME:			Timer Interrupt Service Routine
* Description:		Der Timer zählt eine gewisse Zeit X hoch. Wenn der Interrupt ??? auftritt wird
* 			diese Funktion aufgerufen, die die neue Position von dem Spielball berechnet.
*
* Subroutines Called:	kein
*
* Returns:		keine
*
* Globals:		int8_t ui_timerFlag;
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
ISR(TIMER0_COMP_vect) {
	ui_timerFlag = 1;
}


 /**************************************************************************
* NAME:			Goal
* Description:		Diese Funktion incrementiert den Spielstand (Variable goal im struct)
* 			des übergebenen Spielers. Der Ball wird zurückgesetzt und die vorherige
* 			Position wird so gesetzt, dass Ball sich als erstes wieder in die Richtung
* 			des Spielers bewegt, der keinen Punkt gemacht hat. Somit Aufschlag hat.
*
* Subroutines Called:	???
*
* Returns:		keine
*
* Globals:		???
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void Goal(struct Player player){
	// Punkt z�hlen f�r Spieler player

	// verr�ckte Ausgabe machen, dass ein Punkt gefallen ist

	// Spielball neu Initialisieren

};


/**************************************************************************
* NAME:			calcBallPosition
* Description:		Berechnet die Position des Balls neu. Hierbei werden die derzeitige Bewegungsrichtung
* 			des Balls, Wände und Schläger der Spieler berücksichtigt. Falls der Ball eine der
* 			Seitenwände erreicht, wird die Funktion Goal() aufgerufen, da ein Tor gefallen ist.
*
* Subroutines Called:	keine
*
* Returns:		keine
*
* Globals:		Ball ball; Player playerL, playerR;
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
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




/**************************************************************************
* NAME:			processInput
* Description:		Verarbeitet die Eingabe der Taster der Spieler und bewegt die Schläger nach oben bzw. unten
*
* Subroutines Called:	keine
*
* Returns:		keine
*
* Globals:		Player playerL, playerR;
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void processInput(uint8_t ui_buttons){
    // Bewegung des linken Schl�gers
    if(ui_player1_L(ui_buttons) == 1){                         // Bewegung nach oben
        playerL.prevY = playerL.posY;
        playerL.posY -= 1;
    }
    if(ui_player1_D(ui_buttons) == 1){                         // Bewegung nach unten
        playerL.prevY = playerL.posY;
        playerL.posY += 1;
    }

    // Bewegung des rechten Schl�gers
    if(ui_player2_U(ui_buttons) == 1){                         // Bewegung nach oben
        playerR.prevY = playerR.posY;
        playerR.posY -= 1;
    }
    if(ui_player2_D(ui_buttons) == 1){                         // Bewegung nach unten
        playerR.prevY = playerR.posY;
        playerR.posY += 1;
    }
}


/**************************************************************************
* NAME:			printPong
* Description:		Diese Funktion gibt die Bewebung des Balles und der beiden Schlaeger auf der LED Matrix aus
*
* Subroutines Called:	printBit()
*
* Returns:		keine
*
* Globals:		Ball ball; Player playerL, playerR;
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void printPong(){
    // Ausgabe des Balls
    if(ball.posX != ball.prevX){                    // Immer, wenn es eine Ballbewegung gibt, findet diese auch in X-Richtung statt. Eine senkrechte  Bewegung nach oben ist unm�glich
        printBit(ball.posX, ball.posY, LED_ON);
        printBit(ball.prevX, ball.prevY, LED_OFF);
    }

    // Ausgabe der Schl�ger
    // Schl�ger Links
    if (playerL.posY != playerL.prevY){
        if(playerL.posY > playerL.prevY){           // Bewegung nach unten
            printBit(0, playerL.posY+1, LED_ON);
            printBit(0, playerL.prevY-1, LED_OFF);
        }
        else{                                       // Bewegung nach oben
            printBit(0, playerL.posY-1, LED_ON);
            printBit(0, playerL.prevY+1, LED_OFF);
        }
    }

    // Schl�ger Rechts
    if (playerR.posY != playerR.prevY){
        if(playerR.posY > playerR.prevY){           // Bewegung  nach unten
            printBit(15, playerR.posY+1, LED_ON);
            printBit(15, playerR.prevY-1, LED_OFF);
        }
        else {                                        // Bewegung nach oben
            printBit(15, playerR.posY-1, LED_ON);
            printBit(15, playerR.prevY+1, LED_OFF);
        }
    }
}


 /**************************************************************************
* NAME:			playPong
* Description:		Hauptroutine
*
* Subroutines Called:	calcBallPosition();
*			movecurer();
*			printPong();
*			eingabe();
*			initPong();
* 
* Returns:		keine
*
* Globals:		int8_t ui_timerFlag;
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:
*
* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
void playPong() {
	short play = 1;
	uint8_t ui_buttons;
	initPong();

	while(play) {
        //ui_buttons = eingabe();
		if(ui_timerFlag == 1){
			calcBallPosition();
			//movecurer(ui_buttons);
			ui_buttons = 0;
			printPong();
			ui_timerFlag = 0;
		}
	}
}


