/*****************************************************************************
*
* Datei: 		AdaVRuit_Font.h
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

#ifndef ADAVRUIT_FONT_H_
#define ADAVRUIT_FONT_H_

#include "main.h"

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
void printCharacters(char dez1, char dez2, char dez3);

#endif /* ADAVRUIT_FONT_H_ */
