
#include "tetris.h"

struct  figure
{
	uint8_t bottomRow;      //die relative Position des untersten Steins der Figur innerhalb der Objektmatrix (von unten gez�hlt) [0-3]
	uint8_t posBottomRow;   //die absolute Position des untersten Steins der Figur auf dem Spielfeld [0-15]
	uint8_t left;           //die Position des linkesten Blocks [0-7]
	uint8_t right;          //die Position des rechtesten Blocks [0-7]
	uint8_t matrix[4];      //die Objektmatrix innerhalb welcher das Objekt liegt, wo genau ist durch bottomRow, left und right definiert
	uint8_t rotState;       //in welcher Orientierung befindet sich die aktuelle Figur relativ zur Ausgangsfigur [1-4]
	uint8_t ID;             //welchem Figurtypus die aktuelle Figur besitzt [1-7]
};

/*/
//Initialisierungen der verschiedenen Objekte, Rückgabewert ist ein Objekt vom Typ struct figure.
/*/

struct figure init_Quad(uint8_t newRotState)
{
	struct figure obj;
	obj.rotState = newRotState;
	obj.matrix[3] = 0b00011000;
	obj.matrix[2] = 0b00011000;
	obj.matrix[1] = 0;
	obj.matrix[0] = 0;

	obj.bottomRow = 2;
	obj.posBottomRow = 14;

	obj.left = 3;
	obj.right = 4;

	obj.ID = 1;

	return obj;
}

struct figure init_L(uint8_t newRotState)
{
	struct figure obj;
	obj.ID = 2;

	switch (newRotState)
	{
	case 1:
		obj.matrix[3] = 0b00010000;
		obj.matrix[2] = 0b00011100;
		obj.matrix[1] = 0;		
		obj.matrix[0] = 0;

		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 1;
		break;

	case 2:
		obj.matrix[3] = 0b00001000;
		obj.matrix[2] = 0b00001000;
		obj.matrix[1] = 0b00011000;
		obj.matrix[0] = 0;
		
		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 5;
		obj.right = 6;
		obj.rotState = 2;
		break;

	case 3:
		obj.matrix[3] = 0b00011100;
		obj.matrix[2] = 0b00000100;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;
		
		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 3;
		break;

	case 4:
		obj.matrix[3] = 0b00011000;
		obj.matrix[2] = 0b00010000;
		obj.matrix[1] = 0b00010000;
		obj.matrix[0] = 0;
		
		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 3;
		obj.right = 4;
		obj.rotState = 4;
		break;
	}

	return obj;
}

struct figure init_L_inv(uint8_t newRotState)
{
	struct figure obj;
	obj.ID = 3;

	switch (newRotState)
	{
	case 1:
		obj.matrix[3] = 0b00011100;
		obj.matrix[2] = 0b00010000;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;	

		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 1;
		break;

	case 2:
		obj.matrix[3] = 0b00010000;
		obj.matrix[2] = 0b00010000;
		obj.matrix[1] = 0b00011000;
		obj.matrix[0] = 0;	

		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 3;
		obj.right = 4;
		obj.rotState = 2;
		break;

	case 3:
		obj.matrix[3] = 0b00000100;
		obj.matrix[2] = 0b00011100;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;
		
		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 3;
		break;

	case 4:
		obj.matrix[3] = 0b00011000;
		obj.matrix[2] = 0b00001000;
		obj.matrix[1] = 0b00001000;
		obj.matrix[0] = 0;	

		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 3;
		obj.right = 4;
		obj.rotState = 4;
		break;
	}

	return obj;
}

struct figure init_I(uint8_t newRotState)
{
	struct figure obj;
	obj.ID = 4;
	if (newRotState == 4) newRotState = 2;
	if (newRotState == 3) newRotState = 1;
	switch (newRotState)
	{
	case 1:

		obj.matrix[3] = 0b00111100;
		obj.matrix[2] = 0;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;

		obj.bottomRow = 3;
		obj.posBottomRow = 15;

		obj.left = 2;
		obj.right = 5;
		obj.rotState = 1;
		break;

	case 2:
		obj.matrix[3] = 0b00001000;
		obj.matrix[2] = 0b00001000;
		obj.matrix[1] = 0b00001000;
		obj.matrix[0] = 0b00001000;

		obj.bottomRow = 0;
		obj.posBottomRow = 12;

		obj.left = 4;
		obj.right = 4;
		obj.rotState = 2;
		break;
	}
	return obj;
}

struct figure init_Z(uint8_t newRotState)
{
	struct figure obj;
	obj.ID = 5;
	if (newRotState == 4) newRotState = 2;
	if (newRotState == 3) newRotState = 1;

	switch (newRotState)
	{
	case 1:
		obj.matrix[3] = 0b00001100;
		obj.matrix[2] = 0b00011000;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;
		
		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 1;
		break;

	case 2:
		obj.matrix[3] = 0b00010000;
		obj.matrix[2] = 0b00011000;
		obj.matrix[1] = 0b00001000;
		obj.matrix[0] = 0;

		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 3;
		obj.right = 4;
		obj.rotState = 2;
		break;
	}
	return obj;
}

struct figure init_Z_inv(uint8_t newRotState)
{
	struct figure obj;
	obj.ID = 6;

	if (newRotState == 4) newRotState = 2;
	if (newRotState == 3) newRotState = 1;

	switch (newRotState)
	{
	case 1:
		obj.matrix[3] = 0b00011000;
		obj.matrix[2] = 0b00001100;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;

		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 1;
		break;

	case 2:
		obj.matrix[3] = 0b00001000;
		obj.matrix[2] = 0b00011000;
		obj.matrix[1] = 0b00010000;
		obj.matrix[0] = 0;

		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 2;
		break;
	}

	return obj;
}

struct figure init_T(uint8_t newRotState)
{
	struct figure obj;
	obj.ID = 7;

	switch (newRotState)
	{
	case 1:
		obj.matrix[3] = 0b00011100;
		obj.matrix[2] = 0b00001000;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;

		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 1;
		break;

	case 2:
		obj.matrix[3] = 0b00010000;
		obj.matrix[2] = 0b00011000;
		obj.matrix[1] = 0b00010000;
		obj.matrix[0] = 0;

		obj.bottomRow = 1;
		obj.posBottomRow = 13;

		obj.left = 3;
		obj.right = 4;
		obj.rotState = 2;
		break;

	case 3:
		obj.matrix[3] = 0b00001000;
		obj.matrix[2] = 0b00011100;
		obj.matrix[1] = 0;
		obj.matrix[0] = 0;

		obj.bottomRow = 2;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 5;
		obj.rotState = 3;
		break;

	case 4:
		obj.matrix[3] = 0b00001000;
		obj.matrix[2] = 0b00011000;
		obj.matrix[1] = 0b00001000;
		obj.matrix[0] = 0;

		obj.bottomRow = 1;
		obj.posBottomRow = 14;

		obj.left = 3;
		obj.right = 4;
		obj.rotState = 4;
		break;
	}

	return obj;
}

struct figure newObj(uint16_t rand)
{
	struct figure obj;

	rand += TCNT1;

	switch ((rand % 7) + 1)
	{
	case 1:
		obj = init_Quad((rand % 4) + 1);
		break;
	case 2:
		obj = init_L((rand % 4) + 1);
		break;
	case 3:
		obj = init_L_inv((rand % 4) + 1);
		break;
	case 4:
		obj = init_I((rand % 4) + 1);
		break;
	case 5:
		obj = init_Z((rand % 4) + 1);
		break;
	case 6:
		obj = init_Z_inv((rand % 4) + 1);
		break;
	case 7:
		obj = init_T((rand % 4) + 1);
		break;
	default:
		break;
	}

	return obj;
}

/*
* Funktion:         moveLeft()
* Beschreibung:     Schiebt die Figur um einen Block nach links
*/
struct figure moveLeft(struct figure obj, uint8_t board[16])
{
	uint8_t moveAllowed = 1;
	for (uint8_t i = 0; i < (4-obj.bottomRow); i++)
	{
		if ((board[i + obj.posBottomRow] & (obj.matrix[i + obj.bottomRow] << 1)) != 0) moveAllowed = 0;
	}

	if ((obj.left > 0) && (moveAllowed == 1))
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			obj.matrix[i] = obj.matrix[i] << 1;
		}
		obj.left--;
		obj.right--;
	}
	return obj;
}

/*
* Funktion:         moveRight()
* Beschreibung:     Schiebt die Figur um einen Block nach rechts
*/
struct figure moveRight(struct figure obj, uint8_t board[16])
{
	uint8_t moveAllowed = 1;
	for (uint8_t i = 0; i < (4-obj.bottomRow); i++)
	{
		if ((board[i + obj.posBottomRow] & (obj.matrix[i + obj.bottomRow] >> 1)) != 0) moveAllowed = 0;
	}

	if ((obj.right < 7) && (moveAllowed == 1))
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			obj.matrix[i] = obj.matrix[i] >> 1;
		}
		obj.left++;
		obj.right++;
	}
	return obj;
}

/*
* Funktion:         rotate()
* Beschreibung:     Dreht die aktuelle Figur um 90°.
					Bzgl. der Links-Rechts-Ausrichtung wird dabei versucht den kleineren Wert beizubehalten,
					d.h. wenn die Figur vor der Drehung n�her am linken als am rechten Rand war, wird sie nach
					der Drehung wieder den gleichen Abstand zum linken Rand haben wie zuvor. Der Abstand zum
					rechten Rand kann sich je nach Figur drastisch �ndern.
*/
struct figure rotate(struct figure obj, uint8_t board[16])
{
	uint8_t ID = obj.ID, rotState = obj.rotState, left = obj.left,
		right = obj.right, posBottomRow = obj.posBottomRow,
		topRow = (obj.posBottomRow + obj.bottomRow);
	struct figure oldObj = obj;
	struct figure newObj;

	rotState++;
	if (rotState > 4) rotState = 1;

	switch (ID)
	{
	case 1:
		newObj = init_Quad(rotState);
		break;

	case 2:
		newObj = init_L(rotState);
		break;

	case 3:
		newObj = init_L_inv(rotState);
		break;

	case 4:
		newObj = init_I(rotState);
		break;

	case 5:
		newObj = init_Z(rotState);
		break;

	case 6:
		newObj = init_Z_inv(rotState);
		break;

	case 7:
		newObj = init_T(rotState);
		break;
	}

	if (right >= left)
	{
		while (obj.right > right)
		{
			newObj = moveLeft(obj, board);
		}
	}
	if (left > right)
	{
		while (obj.left > left)
		{
			newObj = moveRight(obj, board);
		}
	}

	newObj.posBottomRow = (topRow - obj.bottomRow);

	uint8_t moveAllowed = 1;

	for (uint8_t i = 0; i < (4 - obj.bottomRow); i++)
	{
		if ((board[obj.posBottomRow + i] & newObj.matrix[obj.bottomRow + i]) != 0) moveAllowed = 0;
	}

	if (obj.posBottomRow == 0) moveAllowed = 0;
	if (moveAllowed == 1) obj = newObj;
	else obj = oldObj;

	return obj;
}

/*
* Funktion:         checkRow()
* Beschreibung:     �berpr�ft jede einzelne Zeile ob sie "voll" ist, wenn dem so ist wird sie gel�scht,
					der Punktestand hochgez�hlt und das gesamte Spielfeld entsprechend nach unten ger�ckt.
					R�ckgabewert ist der aktualisierte Punktestand.
					Der Funktion muss das aktuelle Spielfeld �bergeben werden.
*/
uint16_t checkRows(uint8_t board[16], uint16_t score)
{
	uint8_t topEmptyRow = 0;
	uint8_t oldBoard[16];
	for (uint8_t i = 0; i < 16; i++) oldBoard[i] = board[i];

	//L�scht alle vollst�ndig gef�llten Zeilen und erh�ht den score
	for (uint8_t i = 0; i < 16; i++)
	{
		if (board[i] == 255)
		{
			board[i] = 0;
			score++;
			topEmptyRow = i;
		}
	}

	//Hebt die verschwindenden Zeilen kurz optisch hervor
	for (uint8_t i = 0; i < 4; i++)
	{
		printVerticalArray(board);
		_delay_ms(FADE_OUT_SPEED);
		printVerticalArray(oldBoard);
		_delay_ms(FADE_OUT_SPEED);
		printVerticalArray(board);
	}

	//L�sst, sofern eine Reihe frei wurde, das gesamte Spielfeld oberhalb "herunterrutschen"
	for (uint8_t t = 0; t <= topEmptyRow; t++)
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			if (board[i] == 0)
			{
				if (i != 15)
				{
					board[i] = board[i + 1];
					board[i + 1] = 0;
				}
				else board[i] = 0;
			}
		}
	}
	return score;
}

/*
* Funktion:         lockObj()
* Beschreibung:    Überträgt die bis dahin bewegliche Figur ins Spielfeld und erzeugt eine neue Figur.
*/
void lockObj(uint8_t board[16], struct figure obj)
{
	for (uint8_t i = 0; i < (4 - obj.bottomRow); i++)
	{
		board[obj.posBottomRow + i] = board[obj.posBottomRow + i] ^ obj.matrix[obj.bottomRow + i];
	}
}


/*
* Funktion:         output()
* Beschreibung:     Gibt die Figur und das Spielbrett zusammen auf dem Bilschirm aus
*/
void output(struct figure obj, uint8_t board[16])
{
	uint8_t newBoard[16] = { 0 };
	for (uint8_t k = 0; k < 16; k++)
	{
		newBoard[k] = board[k];
	}
	for (uint8_t i = 0; i < (4-obj.bottomRow); i++)
	{
		newBoard[i + obj.posBottomRow] = board[i + obj.posBottomRow] ^ obj.matrix[i + obj.bottomRow];
	}

	printVerticalArray(newBoard);
}

/*
* Funktion:         printScore()
* Beschreibung:     Gibt den erreichten Score auf dem Bildschirm aus und wartet auf eine Tasteneingabe von Player 1
*/
void printScore(uint8_t score)
{
	clearDisplay();

	uint8_t hundreds = 48, tens = 48, ones = 48;
	while (score >= 100) { score -= 100; hundreds++; }
	while (score >= 10) { score -= 10; tens++; }
	ones += score;

	printCharacters((char)hundreds, (char)tens, (char)ones);

	 _delay_ms(5000);
}


void playTetris()
{
	uint16_t score = 0, rand = 0;
	uint8_t cancel = 0, counter = 0;
	uint8_t board[16] = {0};
	struct figure obj = newObj(rand);
	ui_timerOffset = 63500;
	
	while (cancel == 0)
	{
		//Abbruchbedingungen: entweder alle vier Tasten von Player 1 gedr�ckt und/oder die oberste Reihe des Bildschirms ist blockiert
		if (ui_player1_U() && ui_player1_L() && ui_player1_R() && ui_player1_D()) cancel = 1;
		if (board[15] != 0) cancel = 1;

		//Erzeugung einer Zufallszahl durch Messung der 
		if (ui_player1_U() || ui_player1_L() || ui_player1_R() || ui_player1_D()) rand++;

				
		output(obj, board);

		//Geschwindigkeit der Abw�rtsbewegung �ber timer gesteuert
		if (ui_timerFlag)
		{
			ui_timerFlag = 0;
			counter++;

			//Auswertung der Tasteneingaben
			if (ui_player1_L()) obj = moveLeft(obj, board);
			if (ui_player1_R()) obj = moveRight(obj, board);
			if (ui_player1_U()) obj = rotate(obj, board);
			
			if (counter > GAME_SPEED)
			{
				uint8_t moveAllowed = 1;

				for (uint8_t i = 0; i < (4-obj.bottomRow); i++)
				{
					if ((board[obj.posBottomRow - 1 + i] & obj.matrix[obj.bottomRow + i]) != 0) moveAllowed = 0;
				}
				if (obj.posBottomRow == 0) moveAllowed = 0;

				if (moveAllowed == 0)
				{
					lockObj(board, obj);
					obj = newObj(rand);
					
					uint8_t tmpBoard[16] = { 0 };
					for (uint8_t i = 0; i < (4 - obj.bottomRow); i++)
					{
						tmpBoard[i + obj.posBottomRow] = board[i + obj.posBottomRow] & obj.matrix[i + obj.bottomRow];
					}
					if (tmpBoard[15] != 0) cancel = 1;

					score = checkRows(board, score);	

					moveAllowed = 1;
				}
				else
				{
					obj.posBottomRow--;
				}
				counter = 0;
			}
		}		
	}


	//Fade Out
	for (uint8_t i = 0; i < (4 - obj.bottomRow); i++)
	{
		board[i + obj.posBottomRow] = board[i + obj.posBottomRow] & obj.matrix[i];
	}

	printVerticalArray(board);
	_delay_ms(10*FADE_OUT_SPEED);

	for (uint8_t i = 15; i >= 1; i--)
	{
		_delay_ms(FADE_OUT_SPEED);
		board[i] = 0;
		printVerticalArray(board);
	}
	printScore(score);
} //zurück zum Menü

