/*****************************************************************************
*
* Datei: 		tetris.c
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Spiel
*
* Beschreibung:	Enthält für das Spiel Tetris erforderlichen Funktionen
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/

#include "tetris.h"

struct  figure
{
	uint8_t ui_bottomRow;      //die relative Position des untersten Steins der Figur innerhalb der Objektmatrix (von unten gez�hlt) [0-3]
	uint8_t ui_posBottomRow;   //die absolute Position des untersten Steins der Figur auf dem Spielfeld [0-15]
	uint8_t ui_left;           //die Position des linkesten Blocks [0-7]
	uint8_t ui_right;          //die Position des rechtesten Blocks [0-7]
	uint8_t ui_matrix[4];      //die Objektmatrix innerhalb welcher das Objekt liegt, wo genau ist durch bottomRow, left und right definiert
	uint8_t ui_rotState;       //in welcher Orientierung befindet sich die aktuelle Figur relativ zur Ausgangsfigur [1-4]
	uint8_t ui_ID;             //welchem Figurtypus die aktuelle Figur besitzt [1-7]
};

/*****************************************************************************
* Name:			s_init_[Figur]
* Beschreibung:	Initialisiert die Figur entsprechend dem gewünschten Grad der
* 				Drehung (ui_newRotState [1-4])
*
* Subroutinen:	keine
*
* Rückgabewert:	struct figure
*
* Globale Var.:	keine
******************************************************************************/
struct figure s_init_Quad(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_rotState = ui_newRotState;
	s_obj.ui_matrix[3] = 0b00011000;
	s_obj.ui_matrix[2] = 0b00011000;
	s_obj.ui_matrix[1] = 0;
	s_obj.ui_matrix[0] = 0;

	s_obj.ui_bottomRow = 2;
	s_obj.ui_posBottomRow = 14;

	s_obj.ui_left = 3;
	s_obj.ui_right = 4;

	s_obj.ui_ID = 1;

	return s_obj;
}

struct figure s_init_L(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_ID = 2;

	switch (ui_newRotState)
	{
	case 1:
		s_obj.ui_matrix[3] = 0b00010000;
		s_obj.ui_matrix[2] = 0b00011100;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 1;
		break;

	case 2:
		s_obj.ui_matrix[3] = 0b00001000;
		s_obj.ui_matrix[2] = 0b00001000;
		s_obj.ui_matrix[1] = 0b00011000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 5;
		s_obj.ui_right = 6;
		s_obj.ui_rotState = 2;
		break;

	case 3:
		s_obj.ui_matrix[3] = 0b00011100;
		s_obj.ui_matrix[2] = 0b00000100;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 3;
		break;

	case 4:
		s_obj.ui_matrix[3] = 0b00011000;
		s_obj.ui_matrix[2] = 0b00010000;
		s_obj.ui_matrix[1] = 0b00010000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 4;
		break;
	}

	return s_obj;
}

struct figure s_init_L_inv(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_ID = 3;

	switch (ui_newRotState)
	{
	case 1:
		s_obj.ui_matrix[3] = 0b00011100;
		s_obj.ui_matrix[2] = 0b00010000;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 1;
		break;

	case 2:
		s_obj.ui_matrix[3] = 0b00010000;
		s_obj.ui_matrix[2] = 0b00010000;
		s_obj.ui_matrix[1] = 0b00011000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 2;
		break;

	case 3:
		s_obj.ui_matrix[3] = 0b00000100;
		s_obj.ui_matrix[2] = 0b00011100;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 3;
		break;

	case 4:
		s_obj.ui_matrix[3] = 0b00011000;
		s_obj.ui_matrix[2] = 0b00001000;
		s_obj.ui_matrix[1] = 0b00001000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 4;
		break;
	}

	return s_obj;
}

struct figure s_init_I(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_ID = 4;
	if (ui_newRotState == 4) ui_newRotState = 2;
	if (ui_newRotState == 3) ui_newRotState = 1;
	switch (ui_newRotState)
	{
	case 1:

		s_obj.ui_matrix[3] = 0b00111100;
		s_obj.ui_matrix[2] = 0;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 3;
		s_obj.ui_posBottomRow = 15;

		s_obj.ui_left = 2;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 1;
		break;

	case 2:
		s_obj.ui_matrix[3] = 0b00001000;
		s_obj.ui_matrix[2] = 0b00001000;
		s_obj.ui_matrix[1] = 0b00001000;
		s_obj.ui_matrix[0] = 0b00001000;

		s_obj.ui_bottomRow = 0;
		s_obj.ui_posBottomRow = 12;

		s_obj.ui_left = 4;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 2;
		break;
	}
	return s_obj;
}

struct figure s_init_Z(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_ID = 5;
	if (ui_newRotState == 4) ui_newRotState = 2;
	if (ui_newRotState == 3) ui_newRotState = 1;

	switch (ui_newRotState)
	{
	case 1:
		s_obj.ui_matrix[3] = 0b00001100;
		s_obj.ui_matrix[2] = 0b00011000;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 1;
		break;

	case 2:
		s_obj.ui_matrix[3] = 0b00010000;
		s_obj.ui_matrix[2] = 0b00011000;
		s_obj.ui_matrix[1] = 0b00001000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 2;
		break;
	}
	return s_obj;
}

struct figure s_init_S(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_ID = 6;

	if (ui_newRotState == 4) ui_newRotState = 2;
	if (ui_newRotState == 3) ui_newRotState = 1;

	switch (ui_newRotState)
	{
	case 1:
		s_obj.ui_matrix[3] = 0b00011000;
		s_obj.ui_matrix[2] = 0b00001100;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 1;
		break;

	case 2:
		s_obj.ui_matrix[3] = 0b00001000;
		s_obj.ui_matrix[2] = 0b00011000;
		s_obj.ui_matrix[1] = 0b00010000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 2;
		break;
	}

	return s_obj;
}

struct figure s_init_T(uint8_t ui_newRotState)
{
	struct figure s_obj;
	s_obj.ui_ID = 7;

	switch (ui_newRotState)
	{
	case 1:
		s_obj.ui_matrix[3] = 0b00011100;
		s_obj.ui_matrix[2] = 0b00001000;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 1;
		break;

	case 2:
		s_obj.ui_matrix[3] = 0b00010000;
		s_obj.ui_matrix[2] = 0b00011000;
		s_obj.ui_matrix[1] = 0b00010000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 13;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 2;
		break;

	case 3:
		s_obj.ui_matrix[3] = 0b00001000;
		s_obj.ui_matrix[2] = 0b00011100;
		s_obj.ui_matrix[1] = 0;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 2;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 5;
		s_obj.ui_rotState = 3;
		break;

	case 4:
		s_obj.ui_matrix[3] = 0b00001000;
		s_obj.ui_matrix[2] = 0b00011000;
		s_obj.ui_matrix[1] = 0b00001000;
		s_obj.ui_matrix[0] = 0;

		s_obj.ui_bottomRow = 1;
		s_obj.ui_posBottomRow = 14;

		s_obj.ui_left = 3;
		s_obj.ui_right = 4;
		s_obj.ui_rotState = 4;
		break;
	}

	return s_obj;
}

/*****************************************************************************
* Name:			s_newObj
* Beschreibung:	Erstellt anhand des übergebenen Zufallswerts eine neue Figur
*
* Subroutinen:	s_init_[Figure]
*
* Rückgabewert:	struct figure
*
* Globale Var.:	keine
******************************************************************************/
struct figure s_newObj(uint16_t ui_rand)
{
	struct figure s_obj;

	ui_rand += TCNT1;

	switch ((ui_rand % 7) + 1)
	{
	case 1:
		s_obj = s_init_Quad((ui_rand % 4) + 1);
		break;
	case 2:
		s_obj = s_init_L((ui_rand % 4) + 1);
		break;
	case 3:
		s_obj = s_init_L_inv((ui_rand % 4) + 1);
		break;
	case 4:
		s_obj = s_init_I((ui_rand % 4) + 1);
		break;
	case 5:
		s_obj = s_init_Z((ui_rand % 4) + 1);
		break;
	case 6:
		s_obj = s_init_S((ui_rand % 4) + 1);
		break;
	case 7:
		s_obj = s_init_T((ui_rand % 4) + 1);
		break;
	default:
		break;
	}

	return s_obj;
}

/*****************************************************************************
* Name:			s_moveLeft
* Beschreibung:	verschiebt die Figur, sofern möglich, um einen Pixel nach links
*
* Subroutinen:	keine
*
* Rückgabewert:	struct figure
*
* Globale Var.:	keine
******************************************************************************/
struct figure s_moveLeft(struct figure s_obj, uint8_t ui_board[16])
{
	uint8_t ui_moveAllowed = 1;
	for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
	{
		if ((ui_board[i + s_obj.ui_posBottomRow] & (s_obj.ui_matrix[i + s_obj.ui_bottomRow] << 1)) != 0) ui_moveAllowed = 0;
	}

	if ((s_obj.ui_left > 0) && (ui_moveAllowed == 1))
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			s_obj.ui_matrix[i] = s_obj.ui_matrix[i] << 1;
		}
		s_obj.ui_left--;
		s_obj.ui_right--;
	}
	return s_obj;
}

/*****************************************************************************
* Name:			s_moveRight
* Beschreibung:	verschiebt die Figur, sofern möglich, um einen Pixel nach rechts
*
* Subroutinen:	keine
*
* Rückgabewert:	struct figure
*
* Globale Var.:	keine
******************************************************************************/
struct figure s_moveRight(struct figure s_obj, uint8_t ui_board[16])
{
	uint8_t moveAllowed = 1;
	for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
	{
		if ((ui_board[i + s_obj.ui_posBottomRow] & (s_obj.ui_matrix[i + s_obj.ui_bottomRow] >> 1)) != 0) moveAllowed = 0;
	}

	if ((s_obj.ui_right < 7) && (moveAllowed == 1))
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			s_obj.ui_matrix[i] = s_obj.ui_matrix[i] >> 1;
		}
		s_obj.ui_left++;
		s_obj.ui_right++;
	}
	return s_obj;
}


/*****************************************************************************
* Name:			s_rotate
* Beschreibung:	Dreht die aktuelle Figur um 90°.
*				Bzgl. der Links-Rechts-Ausrichtung wird dabei versucht den
*				kleineren Wert beizubehalten, d.h. wenn die Figur vor der
*				Drehung näher am linken als am rechten Rand war, wird sie nach
*				der Drehung wieder den gleichen Abstand zum linken Rand haben
*				wie zuvor. Der Abstand zum rechten Rand kann sich je nach
*				Figur drastisch ändern.
*
* Subroutinen:	s_init_[Figure]
*
* Rückgabewert:	struct figure
*
* Globale Var.:	keine
******************************************************************************/
struct figure s_rotate(struct figure s_obj, uint8_t ui_board[16])
{
	uint8_t ui_ID = s_obj.ui_ID, ui_rotState = s_obj.ui_rotState, ui_left = s_obj.ui_left,
		ui_right = s_obj.ui_right, ui_posBottomRow = s_obj.ui_posBottomRow,
		ui_topRow = (s_obj.ui_posBottomRow + s_obj.ui_bottomRow);
	struct figure s_oldObj = s_obj;
	struct figure s_newObj;

	ui_rotState++;
	if (ui_rotState > 4) ui_rotState = 1;

	switch (ui_ID)
	{
	case 1:
		s_newObj = s_init_Quad(ui_rotState);
		break;

	case 2:
		s_newObj = s_init_L(ui_rotState);
		break;

	case 3:
		s_newObj = s_init_L_inv(ui_rotState);
		break;

	case 4:
		s_newObj = s_init_I(ui_rotState);
		break;

	case 5:
		s_newObj = s_init_Z(ui_rotState);
		break;

	case 6:
		s_newObj = s_init_S(ui_rotState);
		break;

	case 7:
		s_newObj = s_init_T(ui_rotState);
		break;
	}

	if (ui_right >= ui_left)
	{
		while (s_obj.ui_right > ui_right)
		{
			s_newObj = s_moveLeft(s_obj, ui_board);
		}
	}
	if (ui_left > ui_right)
	{
		while (s_obj.ui_left > ui_left)
		{
			s_newObj = s_moveRight(s_obj, ui_board);
		}
	}

	s_newObj.ui_posBottomRow = (ui_topRow - s_obj.ui_bottomRow);

	uint8_t ui_moveAllowed = 1;

	for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
	{
		if ((ui_board[s_obj.ui_posBottomRow + i] & s_newObj.ui_matrix[s_obj.ui_bottomRow + i]) != 0) ui_moveAllowed = 0;
	}

	if (s_obj.ui_posBottomRow == 0) ui_moveAllowed = 0;
	if (ui_moveAllowed == 1) s_obj = s_newObj;
	else s_obj = s_oldObj;

	return s_obj;
}


/*****************************************************************************
* Name:			ui_checkRows
* Beschreibung: Überprüft jede einzelne Zeile ob sie "voll" ist, wenn dem so
* 				ist wird sie gelöscht, der Punktestand hochgezählt und das
* 				gesamte Spielfeld entsprechend nach unten gerückt.
*				Rückgabewert ist der aktualisierte Punktestand.
*				Der Funktion muss das aktuelle Spielfeld übergeben werden.
*
* Subroutinen:	printVerticalArray aus AdaVRuit.h
*
* Rückgabewert:	uint16_t
*
* Globale Var.:	keine
******************************************************************************/
uint16_t ui_checkRows(uint8_t ui_board[16], uint16_t ui_score)
{
	uint8_t ui_topEmptyRow = 0;
	uint8_t ui_oldBoard[16];
	for (uint8_t i = 0; i < 16; i++) ui_oldBoard[i] = ui_board[i];

	//L�scht alle vollst�ndig gef�llten Zeilen und erh�ht den score
	for (uint8_t i = 0; i < 16; i++)
	{
		if (ui_board[i] == 255)
		{
			ui_board[i] = 0;
			ui_score++;
			ui_topEmptyRow = i;
		}
	}

	//Hebt die verschwindenden Zeilen kurz optisch hervor
	for (uint8_t i = 0; i < 4; i++)
	{
		printVerticalArray(ui_board);
		_delay_ms(FADE_OUT_SPEED);
		printVerticalArray(ui_oldBoard);
		_delay_ms(FADE_OUT_SPEED);
		printVerticalArray(ui_board);
	}

	//L�sst, sofern eine Reihe frei wurde, das gesamte Spielfeld oberhalb "herunterrutschen"
	for (uint8_t t = 0; t <= ui_topEmptyRow; t++)
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			if (ui_board[i] == 0)
			{
				if (i != 15)
				{
					ui_board[i] = ui_board[i + 1];
					ui_board[i + 1] = 0;
				}
				else ui_board[i] = 0;
			}
		}
	}
	return ui_score;
}


/*****************************************************************************
* Name:			lockObj
* Beschreibung: Überträgt die bis dahin bewegliche Figur ins Spielfeld und
* 				erzeugt eine neue Figur.
*
* Subroutinen:	keine
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void lockObj(uint8_t ui_board[16], struct figure s_obj)
{
	for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
	{
		ui_board[s_obj.ui_posBottomRow + i] = ui_board[s_obj.ui_posBottomRow + i] ^ s_obj.ui_matrix[s_obj.ui_bottomRow + i];
	}
}



/*****************************************************************************
* Name:			output
* Beschreibung: Gibt die Figur und das Spielbrett zusammen auf dem Bilschirm aus
*
* Subroutinen:	printVerticalArray
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void output(struct figure s_obj, uint8_t ui_board[16])
{
	uint8_t ui_newBoard[16] = { 0 };
	for (uint8_t k = 0; k < 16; k++)
	{
		ui_newBoard[k] = ui_board[k];
	}
	for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
	{
		ui_newBoard[i + s_obj.ui_posBottomRow] = ui_board[i + s_obj.ui_posBottomRow] ^ s_obj.ui_matrix[i + s_obj.ui_bottomRow];
	}

	printVerticalArray(ui_newBoard);
}


/*****************************************************************************
* Name:			printScore
* Beschreibung: Gibt den erreichten Score auf dem Bildschirm aus
*
* Subroutinen:	printCharacters
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void printScore(uint8_t ui_score)
{
	clearDisplay();

	uint8_t ui_hundreds = 48, ui_tens = 48, ui_ones = 48;
	while (ui_score >= 100) { ui_score -= 100; ui_hundreds++; }
	while (ui_score >= 10) { ui_score -= 10; ui_tens++; }
	ui_ones += ui_score;

	printCharacters((char)ui_hundreds, (char)ui_tens, (char)ui_ones);

	_delay_ms(5000);
}

/*****************************************************************************
* Name:			playTetris
* Beschreibung: Die Hauptfunktion des Spiels Tetris
*
* Subroutinen:	s_newObj
*				s_moveLeft
*				s_moveRight
*				s_rotate
*				ui_player1_R aus AdaVRuit.h
*				ui_player1_L aus AdaVRuit.h
*				ui_player1_U aus AdaVRuit.h
*				ui_player1_D aus AdaVRuit.h
*				lockObj
*				ui_checkRows
*
* Rückgabewert:	kein
*
* Globale Var.:	keine
******************************************************************************/
void playTetris()
{
	uint16_t ui_score = 0, ui_rand = 0;
	uint8_t ui_cancel = 0, ui_counter = 0;
	uint8_t ui_board[16] = { 0 };
	struct figure s_obj = s_newObj(ui_rand);
	ui_timerOffset = 63500;

	while (ui_cancel == 0)
	{
		//Abbruchbedingungen: entweder alle vier Tasten von Player 1 gedr�ckt und/oder die oberste Reihe des Bildschirms ist blockiert
		if (ui_player1_U() && ui_player1_L() && ui_player1_R() && ui_player1_D()) ui_cancel = 1;
		if (ui_board[15] != 0) ui_cancel = 1;

		//Erzeugung einer Zufallszahl durch Messung der 
		if (ui_player1_U() || ui_player1_L() || ui_player1_R() || ui_player1_D()) ui_rand++;


		output(s_obj, ui_board);

		//Geschwindigkeit der Abw�rtsbewegung �ber timer gesteuert
		if (ui_timerFlag)
		{
			ui_timerFlag = 0;
			ui_counter++;

			//Auswertung der Tasteneingaben
			if (ui_player1_L()) s_obj = s_moveLeft(s_obj, ui_board);
			if (ui_player1_R()) s_obj = s_moveRight(s_obj, ui_board);
			if (ui_player1_U()) s_obj = s_rotate(s_obj, ui_board);

			if (ui_counter > GAME_SPEED)
			{
				uint8_t ui_moveAllowed = 1;

				for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
				{
					if ((ui_board[s_obj.ui_posBottomRow - 1 + i] & s_obj.ui_matrix[s_obj.ui_bottomRow + i]) != 0) ui_moveAllowed = 0;
				}
				if (s_obj.ui_posBottomRow == 0) ui_moveAllowed = 0;

				if (ui_moveAllowed == 0)
				{
					lockObj(ui_board, s_obj);
					s_obj = s_newObj(ui_rand);

					uint8_t tmpBoard[16] = { 0 };
					for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
					{
						tmpBoard[i + s_obj.ui_posBottomRow] = ui_board[i + s_obj.ui_posBottomRow] & s_obj.ui_matrix[i + s_obj.ui_bottomRow];
					}
					if (tmpBoard[15] != 0) ui_cancel = 1;

					ui_score = ui_checkRows(ui_board, ui_score);

					ui_moveAllowed = 1;
				}
				else
				{
					s_obj.ui_posBottomRow--;
				}
				ui_counter = 0;
			}
		}
	}


	//Fade Out
	for (uint8_t i = 0; i < (4 - s_obj.ui_bottomRow); i++)
	{
		ui_board[i + s_obj.ui_posBottomRow] = ui_board[i + s_obj.ui_posBottomRow] & s_obj.ui_matrix[i];
	}

	printVerticalArray(ui_board);
	_delay_ms(10 * FADE_OUT_SPEED);

	for (uint8_t i = 15; i >= 1; i--)
	{
		_delay_ms(FADE_OUT_SPEED);
		ui_board[i] = 0;
		printVerticalArray(ui_board);
	}
	printScore(ui_score);
} //zurück zum Menü


