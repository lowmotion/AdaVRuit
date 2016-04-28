/*****************************************************************************
*
* Datei: 		AdaVRuit_Font.c
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Zentrale Einheit
*
* Beschreibung:	Dieses Zusatzmodul ermöglicht es ASCII-Zeichen auf dem Display
* 				darzustellen. Hierbei hat jedes Zeichen eine Breite von vier
* 				Spalten zur Verfügung. Somit können gleichzeitig drei Zeichen
* 				auf dem 16x8 Display dargestellt werden.
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/
#include "AdaVRuit_Font.h"


/*****************************************************************************
 * Name:			character
 * Beschreibung:	Dieses Struktur stellt das Format eines jeden ASCII Zeichens
 * 					dar. Es beinhaltet den ASCII-Code des Zeichens in Dezimal
 * 					und eine grafische Darstellung in 4x8 Bit.
 *****************************************************************************/
struct character
{
	uint8_t matrix[4];		//Matrix welche das ASCII-Zeichen enth�lt
	uint8_t dez;			//Dezimalwert des in .matrix[4] enthaltenen ASCII-Zeichens
};

/*****************************************************************************
* Name:			getCharacter
* Beschreibung:	Ordnet der Dezimalzahl vom Parameter ein entsprechendes
* 				ASCII-Zeichen zu und gibt dieses in vor eines oben definierten
* 				characters zurück.
*
* Subroutinen:	keine
*
* Rückgabewert:	struct character: Enthält das ASCII-Zeichen als 4x8 Matrix
*
* Globale Var.:	keine
******************************************************************************/
struct character s_getCharacter(uint8_t dez)
{
	struct character dig;
	dig.dez = dez;
	switch (dez)
	{
	case 48: // 0
		dig.matrix[0] = 0b01111110;
		dig.matrix[1] = 0b10001001;
		dig.matrix[2] = 0b10010001;
		dig.matrix[3] = 0b01111110;
		break;

	case 49: // 1
		dig.matrix[0] = 0b00010000;
		dig.matrix[1] = 0b00100000;
		dig.matrix[2] = 0b01000000;
		dig.matrix[3] = 0b11111111;
		break;

	case 50: // 2
		dig.matrix[0] = 0b01000011;
		dig.matrix[1] = 0b10000101;
		dig.matrix[2] = 0b10001001;
		dig.matrix[3] = 0b01110001;
		break;

	case 51: // 3
		dig.matrix[0] = 0b01000010;
		dig.matrix[1] = 0b10010001;
		dig.matrix[2] = 0b10011001;
		dig.matrix[3] = 0b01100110;
		break;

	case 52: // 4
		dig.matrix[0] = 0b00011100;
		dig.matrix[1] = 0b00100100;
		dig.matrix[2] = 0b01001111;
		dig.matrix[3] = 0b10000100;
		break;

	case 53: // 5
		dig.matrix[0] = 0b11110010;
		dig.matrix[1] = 0b10010001;
		dig.matrix[2] = 0b10010001;
		dig.matrix[3] = 0b10001110;
		break;

	case 54: // 6
		dig.matrix[0] = 0b00111110;
		dig.matrix[1] = 0b01010001;
		dig.matrix[2] = 0b10010001;
		dig.matrix[3] = 0b10001110;
		break;

	case 55: // 7
		dig.matrix[0] = 0b10000011;
		dig.matrix[1] = 0b10001100;
		dig.matrix[2] = 0b10110000;
		dig.matrix[3] = 0b11000000;
		break;

	case 56: // 8
		dig.matrix[0] = 0b01101110;
		dig.matrix[1] = 0b10010001;
		dig.matrix[2] = 0b10010001;
		dig.matrix[3] = 0b01101110;
		break;

	case 57: // 9
		dig.matrix[0] = 0b01100010;
		dig.matrix[1] = 0b10010001;
		dig.matrix[2] = 0b10010001;
		dig.matrix[3] = 0b01101110;
		break;
	case 58: // : aka Doppelpunkt
		dig.matrix[0] = 0b00000000;
		dig.matrix[1] = 0b01100110;
		dig.matrix[2] = 0b01100110;
		dig.matrix[3] = 0b00000000;
		break;
	case 73: // I aka Das große IHHH
		dig.matrix[0] = 0b00000000;
		dig.matrix[1] = 0b11111111;
		dig.matrix[2] = 0b11111111;
		dig.matrix[3] = 0b00000000;
		break;
	case 78: // n aka Das große N
		dig.matrix[0] = 0b11111111;
		dig.matrix[1] = 0b00010000;
		dig.matrix[2] = 0b00001000;
		dig.matrix[3] = 0b11111111;
		break;
	case 79: // O aka Das große Ohhh
		dig.matrix[0] = 0b01111110;
		dig.matrix[1] = 0b10000001;
		dig.matrix[2] = 0b10000001;
		dig.matrix[3] = 0b01111110;
		break;
	case 82: // R aka Das große ER
		dig.matrix[0] = 0b11111111;
		dig.matrix[1] = 0b10001100;
		dig.matrix[2] = 0b10001010;
		dig.matrix[3] = 0b01110001;
		break;
	case 84: // T aka Das große Tee
		dig.matrix[0] = 0b11000000;
		dig.matrix[1] = 0b11111111;
		dig.matrix[2] = 0b11111111;
		dig.matrix[3] = 0b11000000;
		break;
	case 87: // W aka Das große Weehh
		dig.matrix[0] = 0b11111111;
		dig.matrix[1] = 0b00000110;
		dig.matrix[2] = 0b00000110;
		dig.matrix[3] = 0b11111111;
		break;

	default:
		dig.matrix[0] = 0;
		dig.matrix[1] = 0;
		dig.matrix[2] = 0;
		dig.matrix[3] = 0;
		break;
	}
	return dig;
}

/*****************************************************************************
* Name:			printCharacters
* Beschreibung:	Gibt drei ASCII-Zeichen auf dem Bildschirm aus.
*				Als Parameter werden die Dezimalwerte der auszugebenden
*				Zeichen erwartet, bei einer "0" wird ein Leerzeichen ausgegeben.
*
* Subroutinen:	s_getCharacter()
* 				printVerticalArray() aus AdaVRuit.h
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void printCharacters(char dez1, char dez2, char dez3)
{
	uint8_t board[16] = {};

	for (int i = 0; i < 4; i++) board[i + 1] = s_getCharacter(dez1).matrix[i];
	for (int i = 0; i < 4; i++) board[i + 6] = s_getCharacter(dez2).matrix[i];
	for (int i = 0; i < 4; i++) board[i + 11] = s_getCharacter(dez3).matrix[i];
	
	printVerticalArray(board);
}

