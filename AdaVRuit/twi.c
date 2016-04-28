/*****************************************************************************
*
* Datei: 		twi.c
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
#include "twi.h"

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
void twi_init(void)
{
	/* Prescaler = 1 */
	TWSR = 0;
	/* Faktor wird anhand der Formel aus dem Datenblatt berechnet. Muss > 10 sein. */
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;

}

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
uint8_t ui_twi_start(uint8_t address)
{
	uint8_t   twst;

	/* Startbit senden */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	/* Warten bis Übertragung abgeschlossen ist */
	while(!(TWCR & (1<<TWINT)));

	/* Prüft das TWI Status Register. Prescaler Bits werden maskiert */
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

	/* Geräteadresse senden */
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Warten bis Übertragung abgeschlossen ist */
	while(!(TWCR & (1<<TWINT)));

	/* Prüft das TWI Status Register. Prescaler Bits werden maskiert
	 * Es wird auf das ACK vom Gegenüber geprüft */
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	/* Gerät erfolgreich erreicht */
	return 0;
}

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
void twi_stop(void)
{
	/* Sende Stop Bit */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

	/* Warten bis Übertragung abgeschlossen ist */
	while(TWCR & (1<<TWSTO));

	/* Bus wieder freigegeben */
}

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
uint8_t ui_twi_write(uint8_t data)
{
	uint8_t   twst;

	/* Byte an den vorher Adressierten senden */
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Warten bis Übertragung abgeschlossen ist */
	while(!(TWCR & (1<<TWINT)));

	/* Prüft das TWI Status Register. Prescaler Bits werden maskiert
	 * Es wird auf das ACK vom Gegenüber geprüft */
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;

}
