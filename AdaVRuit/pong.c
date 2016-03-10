
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
	uint8_t posX, posY, prevX, prevY, width, score;
};


/* Globale Variablen */

struct Ball ball;
struct Player playerL, playerR;
volatile uint8_t ui_timerFlag;
uint16_t timerOffset;

void initTimer() {
	/* Timer/Counter1 Overflow*/

	/* Clock Prescaler auf clk/1024
	 * incrementiert 15625 mal pro Sekunde */
	TCCR1B |= (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |= (1 << CS12);

	/* Overflow Interrupt aktivieren */
	TIMSK1 |= (1 << TOIE1);

	/* Startwert des Timers setzen */
	timerOffset = 50000;
	TCNT1 = timerOffset;

	/* Global Interrupts aktivieren */
	//SREG |= (1 << 7);
	SREG|=0x80;
	sei();
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
ISR(TIMER1_OVF_vect) {
	/* Disable Interrupts */
	cli();
	ui_timerFlag = 1;
	if(timerOffset < 60000) {
		timerOffset += 100;
	}
	TCNT1 = timerOffset;
	sei();
}

ISR(__vector_default) {

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
	return;

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
	int8_t movX, movY;				// kein unsigned, da +/-
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
    if(b_player1_U(ui_buttons) == 1){                         // Bewegung nach oben
        playerL.prevY = playerL.posY;
        if(playerL.posY > 0) {
			playerL.posY -= 1;
		}
    }
    if(b_player1_D(ui_buttons) == 1){                         // Bewegung nach unten
        playerL.prevY = playerL.posY;
        if(playerL.posY < (ROWS-1)) {
			playerL.posY += 1;
		}
    }

    // Bewegung des rechten Schl�gers
    if(b_player2_U(ui_buttons) == 1){                         // Bewegung nach oben
        playerR.prevY = playerR.posY;
        if(playerR.posY > 0) {
        	playerR.posY -= 1;
        }
    }
    if(b_player2_D(ui_buttons) == 1){                         // Bewegung nach unten
        playerR.prevY = playerR.posY;
        if(playerR.posY < (ROWS-1)) {
        	playerR.posY += 1;
        }
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
//	if(ball.posX != ball.prevX){                    // Immer, wenn es eine Ballbewegung gibt, findet diese auch in X-Richtung statt. Eine senkrechte  Bewegung nach oben ist unm�glich
//	        printBit(ball.posY, ball.posX, LED_ON);
//	        printBit(ball.prevY, ball.prevX, LED_OFF);
//	    }
//
//	    // Ausgabe der Schl�ger
//	    // Schl�ger Links
//	    if (playerL.posY != playerL.prevY){
//	        if(playerL.posY > playerL.prevY){           // Bewegung nach unten
//	            printBit(playerL.posY+1, 0, LED_ON);
//	            printBit(playerL.prevY-1, 0, LED_OFF);
//	        }
//	        else{                                       // Bewegung nach oben
//	            printBit(playerL.posY-1, 0, LED_ON);
//	            printBit(playerL.prevY+1, 0, LED_OFF);
//	        }
//	    }
//
//	    // Schl�ger Rechts
//	    if (playerR.posY != playerR.prevY){
//	        if(playerR.posY > playerR.prevY){           // Bewegung  nach unten
//	            printBit(playerR.posY+1, 15, LED_ON);
//	            printBit(playerR.prevY-1, 15, LED_OFF);
//	        }
//	        else {                                        // Bewegung nach oben
//	            printBit(playerR.posY-1, 15, LED_ON);
//	            printBit(playerR.prevY+1, 15,  LED_OFF);
//	        }
//	    }
    // Ausgabe des Balls
    if(ball.posX != ball.prevX){                    // Immer, wenn es eine Ballbewegung gibt, findet diese auch in X-Richtung statt. Eine senkrechte  Bewegung nach oben ist unm�glich
        printBit(ball.posY, ball.posX, LED_ON);
        printBit(ball.prevY, ball.prevX, LED_OFF);
    } else {
    	printBit(ball.posY, ball.posX, LED_ON);
    }

    /* Ausgabe der Schläger */
    /* Schläger Links */
    if(playerL.posY > playerL.prevY) {
    	/* Nach unten verschieben */
    	if((playerL.prevY - (playerL.width/2)) >= 0) {
			printBit(playerL.prevY - (playerL.width/2), playerL.posX, LED_OFF);
		}
		if((playerL.posY + (playerL.width/2)) < ROWS) {
			printBit(playerL.posY + (playerL.width/2), playerL.posX, LED_ON);
		}
    } else if(playerL.posY < playerL.prevY) {
    	/* Nach oben verschieben */
    	if((playerL.posY - (playerL.width/2)) >= 0) {
    		printBit(playerL.posY - (playerL.width/2), playerL.posX, LED_ON);
    	}
    	if((playerL.prevY + (playerL.width/2)) < ROWS) {
    		printBit(playerL.prevY + (playerL.width/2), playerL.posX, LED_OFF);
    	}
    } else {
    	/* Spieler an aktueller Position zeichnen */
    	printBit(playerL.posY, playerL.posX, LED_ON);
    	for(short width = playerL.width; width > 1; width-=2) {
    		if((playerL.posY - (width/2)) >= 0) {
    			printBit(playerL.posY - (width/2), playerL.posX, LED_ON);
    		}
    		if((playerL.posY + (width/2)) < ROWS) {
    			printBit(playerL.posY + (width/2), playerL.posX, LED_ON);
    		}
    	}
    }


    /* Schläger Rechts */
    if(playerR.posY > playerR.prevY) {
		/* Nach unten verschieben */
		if((playerR.prevY - (playerR.width/2)) >= 0) {
			printBit(playerR.prevY - (playerR.width/2), playerR.posX, LED_OFF);
		}
		if((playerR.posY + (playerR.width/2)) < ROWS) {
			printBit(playerR.posY + (playerR.width/2), playerR.posX, LED_ON);
		}
	} else if(playerR.posY < playerR.prevY) {
		/* Nach oben verschieben */
		if((playerR.posY - (playerR.width/2)) >= 0) {
			printBit(playerR.posY - (playerR.width/2), playerR.posX, LED_ON);
		}
		if((playerR.prevY + (playerR.width/2)) < ROWS) {
			printBit(playerR.prevY + (playerR.width/2), playerR.posX, LED_OFF);
		}
	} else {
		/* Spieler an aktueller Position zeichnen */
		printBit(playerR.posY, playerR.posX, LED_ON);
		for(short width = playerR.width; width > 1; width -= 2) {
			if((playerR.posY - (width/2)) >= 0) {
				printBit(playerR.posY - (width/2), playerR.posX, LED_ON);
			}
			if((playerR.posY + (width/2)) < ROWS) {
				printBit(playerR.posY + (width/2), playerR.posX, LED_ON);
			}
		}
	}
}

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
	/* Ball initialisieren */
	ball.posX = 7;
	ball.posY = 4;
	ball.prevX = 8;
	ball.prevY = 4;

	/* Player Links */
	playerL.posX = 0;
	playerL.posY = 3;
	playerL.prevX = 0;
	playerL.prevY = 3;
	playerL.width = BAT_WIDTH;

	/* Player Links */
	playerR.posX = 15;
	playerR.posY = 3;
	playerR.prevX = 15;
	playerR.prevY = 3;
	playerR.width = BAT_WIDTH;

	/*printBit(playerL.posY, playerL.posX, 1);
	printBit(playerL.posY+1, playerL.posX, 1);
	printBit(playerL.posY-1, playerL.posX, 1);
	printBit(playerR.posY, playerR.posX, 1);
	printBit(playerR.posY+1, playerR.posX, 1);
	printBit(playerR.posY-1, playerR.posX, 1);*/

	printPong();
	initTimer();


	cli();
	/* Watchdog deaktivieren */
	MCUSR &= ~(1<<WDRF);
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	WDTCSR = 0x00;

	sei();
	SREG|=0x80;
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
	uint8_t ui_buttons = 0;
	initPong();

	//printPong();
	sei();
	while(1) {
        ui_buttons |= ui_eingabe();
		if(ui_timerFlag){
			calcBallPosition();
			processInput(ui_buttons);
			ui_buttons = 0;
			printPong();
			ui_timerFlag = 0;
		}
	}
}


