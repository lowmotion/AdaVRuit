/*****************************************************************************
*
* Datei: 		twi.h
* Kurs:			TEN14
* Projekt:		Spielekonsole
* Modul:		Zentrale Einheit
*
* Beschreibung:	Dieses Modul lagert wichtige Funktionen aus, die für die
* 				Verwendung von TWi (I²C) benötigt werden.
*
* Autor:		Michel Denniger, Marco Jedzig, Michael Karp, Christian Wagner,
* 				Tobias Mages
*
* Datum: 		26.04.2016
*
*****************************************************************************/

#ifndef TWI_H_
#define TWI_H_

#include <inttypes.h>
#include <util/twi.h>

/* Taktfrequenz der CPU */
#ifndef F_CPU
#warning "Warning F_CPU not defined for twi.h"
#define F_CPU 16000000UL
#endif

/* TWI/I2C clock in Hz */
#ifndef SCL_CLOCK
#warning "Warning SCL_CLOCK not defined for twi.h. Default is 100 kHz"
#define SCL_CLOCK  100000L
#endif

/*****************************************************************************
* Name:			twi_init
* Beschreibung:	Initialisiert die TWI Schnittstelle, welche zu I2C kompatibel
* 				ist. Dazu wird die Clock (SCL) eingerichtet. Der Prescaler
* 				(TWPS) wird immer auf "0 0" gesetzt. Der Faktor TWBR wird
* 				anhand der Formel aus dem Datenblatt über die Precompiler
* 				Definitionen ausgerechnet.
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void twi_init();

/*****************************************************************************
* Name:			twi_start
* Beschreibung:	Sendet das Startbit und danach die mitgegebene Adresse auf
* 				den TWI/I2C-Bus. Prüft ob das Gerät erreichbar ist.
*
* Subroutinen:	keine
*
* Rückgabewert:	uint8_t:
* 				0 = Gerät erfolgreich erreicht
* 				1 = Fehler, Gerät antwortet nicht
*
* Globale Var.:	keine
******************************************************************************/
uint8_t ui_twi_start(uint8_t address);

/*****************************************************************************
* Name:			twi_stop
* Beschreibung:	Schließt die aktulle Übertragung ab und gibt den TWI/I²C-Bus
* 				wieder frei.
*
* Subroutinen:	keine
*
* Rückgabewert:	keine
*
* Globale Var.:	keine
******************************************************************************/
void twi_stop(void);

/*****************************************************************************
* Name:			twi_write
* Beschreibung:	Sendet ein Byte über den TWI/I2C-Bus und prüft, ob das Byte
* 				angekommen ist. Die Funktion twi_start muss vorher aufgerufen
* 				werden.
*
* Subroutinen:	keine
*
* Rückgabewert:	uint8_t:
* 				0 = Byte erfolgreich übertragen
* 				1 = kein ACK vom Empfänger erhalten
*
* Globale Var.:	keine
******************************************************************************/
uint8_t ui_twi_write(uint8_t data);

#endif /* TWI_H_ */
