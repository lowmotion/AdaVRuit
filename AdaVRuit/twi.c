/*****************************************************************************
*
* FILE: 		twi.c
* PROJECT:		Spielekonsole
* MODULE:		???
*
* Description:		Diese Datei enthällt sllr Funktionen zur Verwendung es TWI
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date: 02.03.2016
* BY:	Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/
#include "twi.h"

/**************************************************************************
* NAME:			twi_init
* Description:		DInitialisiert die TWI Schnittstelle, welche zu I2C kompatibel ist.
* 			Dazu wird die Clock (SCL) eingerichtet. Der Prescaler (TWPS) wird immer auf "0 0" gesetzt.
* 			Der Faktor TWBR wird anhand der Formel aus dem Datenblatt über die Precompiler Definitionen
* 			ausgerechnet.
*
* Subroutines Called:	keine
*
* Returns:		keine
*
* Globals:		keine
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
void twi_init(void)
{
	/* Prescaler = 1 */
	TWSR = 0;
	/* Faktor wird anhand der Formel aus dem Datenblatt berechnet. Muss > 10 sein. */
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;

}


/**************************************************************************
* NAME:			twi_start
* Description:		Sendet das Startbit und danach die mitgegebene Adresse auf den TWI/I2C-Bus.
* 			Prüft ob das Gerät erreichbar ist.
*
* Subroutines Called:	keine
*
* Returns:		uint8_t:
 * 				0 = Gerät erreicht
 * 				1 = Gerät nicht erreicht
*
* Globals:		keine
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
uint8_t twi_start(uint8_t address)
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


 /**************************************************************************
* NAME:			twi_stop
* Description:		Schließt die Aktulle Übertragung ab und gibt den TWI/I2C-Bus wieder frei.
*
* Subroutines Called:	keine
*
* Returns:		keine
* 
* Globals:		keine
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
void twi_stop(void)
{
	/* Sende Stop Bit */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

	/* Warten bis Übertragung abgeschlossen ist */
	while(TWCR & (1<<TWSTO));

	/* Bus wieder freigegeben */
}


  /**************************************************************************
* NAME:			twi_write
* Description:		Sendet ein Byte über den TWI/I2C-Bus und prüft, ob das Byte angekommen ist.
* 			Die Funktion twi_start muss vorher aufgerufen werden.
*
* Subroutines Called:	keine
*
* Returns:		Uint8_t:
 * 				0 = Byte erfolgreich übertragen
 * 				1 = Kein vom Empfänger ACK erhalten
* 
* Globals:		keine
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
uint8_t twi_write(uint8_t data)
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

/**************************************************************************
* NAME:			TWI_sendByte
* Description:		schlatet die gewünschte LED an oder aus
*
* Subroutines Called:	twi_start();
* 			twi_write();
*			twi_stop()
*
* Returns:		keine
*
* Globals:		keine
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
void twi_sendByte(uint8_t offset, uint8_t byte){
	twi_start(LED_ADRESS_TWI);
	twi_write(offset);
	twi_write(byte);
	twi_stop();
}

/**************************************************************************
* NAME:			TWI_sendArray
* Description:		Überträgt die gesamte Matrix auf die Anzeige
*
* Subroutines Called:	twi_start();
* 			twi_write();
*			twi_stop()
*
* Returns:		keine
*
* Globals:		uint8_t matrix[8][2]
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
void twi_sendArray(int8_t ui_matrix[8][2]){
	twi_start(LED_ADRESS_TWI);
	twi_write(0x00);		// Senden des Offsets
	for(uint8_t row = 0; row < 8; row++){
		for(uint8_t leftRight = 0; leftRight < 2; leftRight++){
			twi_write(ui_matrix[row][leftRight]);
		}
	}
	twi_stop();
}
