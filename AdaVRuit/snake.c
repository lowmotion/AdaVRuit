/***************************************************************************** 
* 
* Datei: 		snake.c 
* Kurs:			TEN14 
* Projekt:		Spielekonsole 
* Modul:		Spiel Snake
* 
* Beschreibung:	Diese Datei enthällt die Hauptroutine und alle Funktionen des 
* 				Spiels "Snake" 
* 
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Tobias Mages,
* 				Christian Wagner
* 
* Datum: 		28.04.2016 
* 
*****************************************************************************/ 

#include "snake.h"

/***************************************************************************** 
* Name:			Snake 
* Beschreibung:	Diese Struktur stellt die vom Spieler gesteuerte Schlange dar. 
* 				Sie beinhaltet Informationen über die derzeitige und 
* 				vorherige(eraseX/Y) Position, sowie die momentane Länge 
*****************************************************************************/ 
struct Snake	{
	uint8_t snakeX[MAX_LENGTH];	//X-Koordinaten
	uint8_t snakeY[MAX_LENGTH];	//Y-Koordinaten
	uint8_t snakeLength;	//Laenge der Schlange
	uint8_t eraseX, eraseY;		//"Spur" l�schen
	} snake;


/***************************************************************************** 
* Name:			Food 
* Beschreibung:	Diese Struktur stellt das Futter dar und beinhaltet seine 
* 				aktuelle Position und eine Variable für die Anzeige-LED, um
* 				eventuelle Anzeigeeffekte, wie Blinken beim Erscheinen umzusetzen
37  *****************************************************************************/ 
struct Food		{
	uint8_t foodX, foodY;
	uint8_t foodLED;		//f�r eventuelle Anzeigeeffekte
	} food;
	
/************************** 
* GLOBALE VARIABLEN 
**************************/ 

/*Bewegungsrichtung*/
uint8_t ui_direction = UP;

/*fuer Button-Abfrage*/
uint8_t ui_buttonRead = FALSE;

/*fuer delay in mainloop*/
/*unsigned long prevTime = 0;
unsigned long delayTime = 500;
*/

/***************************************************************************** 
* Name:			random 
* Beschreibung:	Diese Funktion erstellt einen Zufallswert und gibt diesen zurück
* 
* Subroutinen:	keine
* 
* Rückgabewert:	uint8_t: zwischen 0 und Parameter des Ausrufs 
* 
* Globale Var.:	keine
******************************************************************************/ 
uint8_t ui_random(uint8_t max)
{
	return TCNT1L % max;
}

/***************************************************************************** 
* Name:			partOfSnake*
* Beschreibung:	Diese Funktion ueberprueft, ob die Kombination ihrer zwei
* 				Eingabeparameter einem der aktuellen Koordinatenpaare der
* 				Snake-Struktur entspricht
* 
* Subroutinen:	keine 
* 
* Rückgabewert:	uint8_t: TRUE/1 oder FALSE/0 
* 
* Globale Var.:	struct Snake snake; 
******************************************************************************/ 
uint8_t ui_partOfSnake(uint8_t x, uint8_t y)
{
	for (int i=0; i<snake.snakeLength; i++)
	{
		if(x==snake.snakeX[i] && y==snake.snakeY[i]) return TRUE;
	}
	return FALSE;
}

/***************************************************************************** 
* Name:			makeFood 
* Beschreibung:	Diese Funktion erzeugt ein zufaelliges x-y-Koordinatenpaar,
* 				gleicht dieses mit der Schlange ab und erzeugt bei
* 				Übereinstimmung eine neue Position. Anschließend werden die
* 				Werte in den Positionsspeicher der Futter-Struktur geschrieben
* 
* Subroutinen:	printBit() aus AdaVRuit.h 
*				random()
* 				PartOfSnake() 
*				_delay_ms() aus <util/delay.h> 
* 
* Rückgabewert:	keine
* 
* Globale Var.:	struct Food food; 
******************************************************************************/ 
void makeFood(uint8_t playInit)
{
	/* letztes Futter loeschen */
	if (playInit == 1)	printBit(food.foodX, food.foodY, LED_OFF);
	
	uint8_t x = ui_random(ROWS-1);
	uint8_t y = ui_random(COLUMNS-1);
	/* Schlange bereits an neuer Futterposition? */
	while(ui_partOfSnake(x,y))
	{
		x = ui_random(ROWS-1);
		y = ui_random(COLUMNS-1);
	}
	food.foodX = x;
	food.foodY = y;
	for (int i=0; i<4; i++)
	{
		//if(food.foodX>=0 && food.foodX<16 && food.foodY>=0 && food.foodY<8)
		 printBit(food.foodX, food.foodY, LED_OFF);
		 _delay_ms(100);
		  printBit(food.foodX, food.foodY, food.foodLED);
		 _delay_ms(100);
	}
}

/***************************************************************************** 
* Name:			checkButtons
* Beschreibung:	Ueberprueft, ob bereits eine Eingabe im aktuellen Spielzyklus
* 				registriert wurde.
* 				Wenn nein:
* 				Wertet Buttons "links" und "rechts" aus und in- bzw.
* 				dekrementiert die Richtungsvariable entsprechend um 1, was
* 				einer 90 Grad-Drehung entspricht. Setzt anschließend das zu
* 				Beginn abgefragte Tastenauswertungsflag
* 
* Subroutinen:	b_player1_U() aus AdaVRuit.h 
* 				b_player1_D() aus AdaVRuit.h 
* 				b_player1_L() aus AdaVRuit.h 
* 				b_player1_R() aus AdaVRuit.h 
* 
* Rückgabewert:	uint8_t: 1 oder 0 
* 
* Globale Var.:	uint8_t buttonRead, direction; 
******************************************************************************/ 
uint8_t ui_checkButtons(uint8_t ui_buttons)
{
	/* Abbruchbedingung */
	if(b_checkPlayer1_U(ui_buttons) && b_checkPlayer1_D(ui_buttons) && b_checkPlayer1_L(ui_buttons) && b_checkPlayer1_R(ui_buttons)) {
		return 0;
	}
	if(!ui_buttonRead)	//Buttoneingabe bereits geschehen?
	{
		int currentDirection = ui_direction;
		if(b_player_L(ui_buttons) == 1)		
		{
			ui_direction--;
			if(ui_direction < 0) ui_direction = LEFT;
		}
		else if(b_player_R(ui_buttons) == 1)	
		{
			ui_direction++;
			if(ui_direction > 3) ui_direction = UP;
		}
		/* setze Flag "Buttoneingabe registriert" */
		ui_buttonRead = (currentDirection != ui_direction);
	}
	return 1;
}

/***************************************************************************** 
* Name:			nextstep 
* Beschreibung:	Bewegt zuerst den Schlangenkoerper um eine Position und
* 				anschließend den Kopf (erste Position) entsprechend der
* 				aktuellen Bewegungsrichtung weiter. Falls der Kopf dabei auf
* 				das Futter trifft, wird die Laenge der Schlange um 1
* 				inkrementiert. Hat die Schlange danach noch nicht ihre maximale
* 				Laenge erreicht, wird die Funktion zur Erstellung einer neuen
* 				Futter-Struktur aufgerufen.
* 
* Subroutinen:	makeFood(); 
* 
* Rückgabewert:	keine
* 
* Globale Var.:	struct Snake snake; 
*				uint8_t direction; 
******************************************************************************/ 
void nextstep()
{
	uint8_t play1 = 1;
	/* Bewegung Schlangenkoerper */
	for(int i=snake.snakeLength-1; i>0; i--)
	{
		/* eventuelles Loeschbit fuer Ausgabe vorbereiten */
		/*if (snake.snakeX[i+1] == -1)	
		{
			snake.eraseX = snake.snakeX[i];
			snake.eraseY = snake.snakeY[i];
		}*/
		snake.snakeX[i] = snake.snakeX[i-1];
		snake.snakeY[i] = snake.snakeY[i-1];
	}
	/* Bewegung Kopf */
	switch(ui_direction)
	{
		case UP:
			snake.snakeY[0] = snake.snakeY[0]+1;
			if (snake.snakeY[0]>=COLUMNS)	snake.snakeY[0]=0;	
			break;
		case RIGHT:
			snake.snakeX[0] = snake.snakeX[0]+1;
			if (snake.snakeX[0]>=ROWS)	snake.snakeX[0]=0;
			break;
		case DOWN:
			snake.snakeY[0] = snake.snakeY[0]-1;
			if (snake.snakeY[0]<0)		snake.snakeY[0]=ROWS-1;
			break;
		case LEFT:
			snake.snakeX[0] = snake.snakeX[0]-1;
			if (snake.snakeX[0]<0)		snake.snakeX[0]=COLUMNS-1;
			break;
	}
	/* Futter erreicht? */
	if((snake.snakeX[0] == food.foodX) && (snake.snakeY[0] == food.foodY))
	{
		snake.snakeLength++;
		if (snake.snakeLength < MAX_LENGTH) makeFood(play1);
		/* maximales Wachstum erreicht */
		else food.foodX = food.foodY = -1;					
	}
}

/***************************************************************************** 
* Name:			drawSnake
* Beschreibung:	Diese Funktion gibt die aktuelle Position des Futters und nach
* 				Überpruefung auch die Bewebung der Schlange auf der LED Matrix
* 				aus.
* 
* Subroutinen:	clearDisplay() aus AdaVRuit.h
* 				printBit() aus AdaVRuit.h 
* 
* Rückgabewert:	keine
* 
* Globale Var.:	struct Food food; 
*				struct Snake snake;
******************************************************************************/ 
void drawSnake()
{	
	clearDisplay();
	/* Futter */
	if(food.foodX>=0 && food.foodX<ROWS && food.foodY>=0 && food.foodY<COLUMNS) printBit(food.foodX, food.foodY, food.foodLED);
	/* Snake */
	for(int i=0; i<snake.snakeLength; i++)
	{
		/* Pruefung, ob bereits aktuelles Ende der Schlange erreicht */
		if (snake.snakeX[i] == -1) break;		
		printBit(snake.snakeX[i], snake.snakeY[i], LED_ON);
	}
	/* Loeschen der "Spur" der Schlange */
	//printBit(snake.eraseX, snake.eraseY, LED_OFF);
}

/***************************************************************************** 
* Name:			initSnake
* Beschreibung:	Diese Funktion initialisiert das Spiel Snake. Es wird die
* 				Schlange Snake initialisiert und  relativ mittig (Zeile 4
* 				Spalte 4) auf dem Spielfeld positioniert.
* 				Anschließend wird an zufaelliger Position das erste Futter
* 				positioniert
* 
* Subroutinen:	makeFood()
* 				clearDisplay()  aus AdaVRuit.h
*				
* 
* Rückgabewert:	keine 
* 
* Globale Var.:	struct Snake snake 
*				struct Food food 
******************************************************************************/ 
void initSnake(uint8_t play0)
{
	clearDisplay();
	snake.snakeLength=1;
	/* Startposition */
	snake.snakeX[0] = 4;	
	snake.snakeY[0] = 4;
	/* restliche Glieder "abschalten" */
	for(int i=1; i<MAX_LENGTH; i++)	
	{
		snake.snakeX[i] = snake.snakeY[i] = -1;
	}
	food.foodLED=LED_ON;
	makeFood(play0);
}

/***************************************************************************** 
* Name:			playSnake
* Beschreibung:	Hauptroutine des Spiels Snake 
* 
* Subroutinen:	_delay_ms() aus <util/delay.h>	 
* 				initSnake() 
* 				ui_input() aus AdaVRuit.h 
* 				checkButtons() 
* 				nextstep() 
* 				drawSnake() 
* 
* Rückgabewert:	keine
* 
* Globale Var.:	int8_t ui_timerFlag  aus AdaVRuit.h *  
******************************************************************************/ 
void playSnake()
{
	uint8_t play = 0;
	initSnake(play);

	uint8_t ui_buttons;

	play = 1;

	while (play)
	{
		/* Eingangspins aufnehmen */
		ui_buttons = ui_input();	
		play = ui_checkButtons(ui_buttons);
		if (ui_timerFlag==1)
		{
			nextstep();
			ui_buttonRead = FALSE;
			ui_timerFlag = 0;
			drawSnake();
		}
		ui_buttons = 0;
	}
	_delay_ms(500);
}

