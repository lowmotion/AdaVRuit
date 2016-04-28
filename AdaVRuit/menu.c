/*****************************************************************************
*
* Datei: 		menu.c
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Menü
*
* Beschreibung:	Enthält alle für das Menü erforderlichen Funktionen und
* 				Datenstrukturen
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/


#include "menu.h"

/*****************************************************************************
* Name:			twinkel[Left/Right]Cursor
* Beschreibung:	Schaltet die LEDs des linken/rechten Cursors aus
*
* Subroutinen:	printBit
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void twinkelLeftCursor()
{
	printBit(1, 2, LED_OFF);
	printBit(2, 1, LED_OFF); printBit(2, 2, LED_OFF);
	printBit(3, 0, LED_OFF); printBit(3, 1, LED_OFF);
	printBit(4, 0, LED_OFF); printBit(4, 1, LED_OFF);
	printBit(5, 1, LED_OFF); printBit(5, 2, LED_OFF);
	printBit(6, 2, LED_OFF);
}

void twinkelRightCursor()
{
	printBit(1, 13, LED_OFF);
	printBit(2, 13, LED_OFF); printBit(2, 14, LED_OFF);
	printBit(3, 14, LED_OFF); printBit(3, 15, LED_OFF);
	printBit(4, 14, LED_OFF); printBit(4, 15, LED_OFF);
	printBit(5, 13, LED_OFF); printBit(5, 14, LED_OFF);
	printBit(6, 13, LED_OFF);
}


/*****************************************************************************
* Name:			menu
* Beschreibung:	Gibt ein Menü aus. Mit den "left"- und "right"-Tastern von
* 				Player 1 lässt sich durch verschiedene Menüpunkte blättern.
* 				Die Menüpunkte sind animiert und stellen das zu erwartende
* 				Spiel dar. Durch Drücken des "up"-Tasters von Player 1 wird
* 				der aktuelle Menüpunkt gestartet.
*
* Subroutinen:	printArray aus AdaVRuit.h
*				ui_player1_L aus AdaVRuit.h
*				ui_player1_R aus AdaVRuit.h
*				ui_player1_U aus AdaVRuit.h
*				playPong aus pong.h
*				playTetris aus tetris.h
*				playSnake aus snake.h
*				twinkelLeftCursor
*				twinkelRightCursor
*				clearDisplay aus AdaVRuit.h
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void menu()
{
	//Initialisierung aller Variablen

	uint8_t ui_currentSelection = 1, ui_counter = 0;

	uint8_t ui_maxAnimationSteps[MENU_ENTRIES] = { 6, 14, 11 };

	struct animationData
	{
		uint16_t ui_matrix[8];
	};


	/*/
	//Die struct-Arrays enthalten jeweils alle Einzelbilder der Animation,
	//eine Zeile entspricht einem Bild.
	/*/

	struct animationData s_pong[6] =
	{
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100011000100011,
			0b1100010000100011,
			0b0110000000100110,
			0b0010000000000100,
			0b0000000000000000

		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100010100100011,
			0b1100010000100011,
			0b0110000000100110,
			0b0010000000000100,
			0b0000000000000000

		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100010010100011,
			0b1100010000100011,
			0b0110000000100110,
			0b0010000000000100,
			0b0000000000000000

		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100010001100011,
			0b1100010000100011,
			0b0110000000100110,
			0b0010000000000100,
			0b0000000000000000

		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100010010100011,
			0b1100010000100011,
			0b0110000000100110,
			0b0010000000000100,
			0b0000000000000000

		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100010100100011,
			0b1100010000100011,
			0b0110000000100110,
			0b0010000000000100,
			0b0000000000000000
		}
	};

	struct animationData s_snake[14] =
	{
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110011100000110,
			0b1100000000000011,
			0b1100000000000011,
			0b0110000010000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110011000000110,
			0b1100010000000011,
			0b1100000000000011,
			0b0110000010000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110010000000110,
			0b1100010000000011,
			0b1100010000000011,
			0b0110000010000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100010000000011,
			0b1100010000000011,
			0b0110010010000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011010000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100000000000011,
			0b0110011110000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100000000000011,
			0b0110001110000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100000000000011,
			0b0110000111000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100000001000011,
			0b0110000011000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000001000011,
			0b1100000001000011,
			0b0110000001000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000001000110,
			0b1100000001000011,
			0b1100000001000011,
			0b0110000000000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000011000110,
			0b1100000001000011,
			0b1100000000000011,
			0b0110000000000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000111000110,
			0b1100000000000011,
			0b1100000000000011,
			0b0110000000000110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110001110000110,
			0b1100000000000011,
			0b1100000000000011,
			0b0110000000000110,
			0b0010000000000100,
			0b0000000000000000
		}
	};

	struct animationData s_tetris[11] =
	{
		{
			0b0000000010000000,
			0b0010000010000100,
			0b0110000110000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011000110110,
			0b0010111110110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000010000100,
			0b0110000010000110,
			0b1100000110000011,
			0b1100010000000011,
			0b0110011000110110,
			0b0010111110110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110001110000110,
			0b1100000010000011,
			0b1100010000000011,
			0b0110011000110110,
			0b0010111110110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100001110000011,
			0b1100010010000011,
			0b0110011000110110,
			0b0010111110110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000111000011,
			0b1100010001000011,
			0b0110011000110110,
			0b0010111110110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010111000011,
			0b0110011001110110,
			0b0010111110110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011111110110,
			0b0010111111110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011111110110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011111110110,
			0b0010111111110100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011111110110,
			0b0010000000000100,
			0b0000000000000000
		},
		{
			0b0000000000000000,
			0b0010000000000100,
			0b0110000000000110,
			0b1100000000000011,
			0b1100010000000011,
			0b0110011111110110,
			0b0010111111110100,
			0b0000000000000000
		}
	};

	clearDisplay();      //Bildschirm komplett l?schen

	while (1)
	{
		switch (ui_currentSelection)
		{
		case 1:
			printArray(s_pong[ui_counter].ui_matrix);
			if (b_getPlayer1_U()) playPong();
			break;
		case 2:
			printArray(s_snake[ui_counter].ui_matrix);
			if (b_getPlayer1_U()) playSnake();
			break;
		case 3:
			printArray(s_tetris[ui_counter].ui_matrix);
			if (b_getPlayer1_U()) playTetris();
			break;
		default:
			clearDisplay();      //TODO: sinnvollen default-Wert ?berlegen
			break;
		}

		/*/
		// Abfrage ob links- oder rechts-Taste gedr?ckt wurde und
		// entsprechend der aktuell angezeigt Men?punkt gewechselt werden muss
		/*/
		if (b_getPlayer1_L() == 1)
		{
			ui_currentSelection--;
			twinkelLeftCursor();
			if (ui_currentSelection == 0) ui_currentSelection = MENU_ENTRIES;
		}
		if (b_getPlayer1_R() == 1)
		{
			ui_currentSelection++;
			twinkelRightCursor();
			if (ui_currentSelection > MENU_ENTRIES) ui_currentSelection = 1;
		}

		ui_counter++;              //Counter wird erh?ht um das n?chste Bild der Animation auszuw?hlen
		if (ui_counter >= ui_maxAnimationSteps[ui_currentSelection - 1]) ui_counter = 0;

		_delay_ms(300);
	}
}


