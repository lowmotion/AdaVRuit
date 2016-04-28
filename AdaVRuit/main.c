/*****************************************************************************
*
* Datei: 		main.c
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Zentrale Einheit
*
* Beschreibung:	Diese Datei enthält den Startpunkt des Programms und führt
* 				alle Module zusammen.
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/

#include "main.h"

/*****************************************************************************
* Name:			main
* Beschreibung:	Startpunkt des Programmes. Startet das System und sorgt dafür,
* 				dass den Mikrokontroller nicht abschaltet, falls ein Fehler
* 				auftritt und das Menü verlassen wird.
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
int main() {
	initSystem();
	menu();
	while(1) {
		;
	}
	return 0;
}
