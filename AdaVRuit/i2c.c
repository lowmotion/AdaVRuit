

/* Beschreibung:		  Initialisierung des I2C
 *						        Einstellung des SCL = (CPU_CLOCK)/(16+2*(TWBR)*4^(TWSR))
 *						        Bustakt wurde auf rund 15,4kHz gesetzt.
 * Gloable Variablen:	Keine
 */
void initI2C(){
	TWBR |=	0x04;	// -> sollte bei einem Master > 10 sein -> wurde auf = 32 gesetzt
	TWSR |= 0x02;	// Prescale = 4^TWSR = 16
}



/* Beschreibung:		  Senden eines Bytes (ui_data) über I2C an ui_adres
 * Globale Variablen:	Keine
 */
void sendOneByteI2C(uint8_t ui_adres, uint8_t ui_data){
	// Startbedingung
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);		// Startbedingung
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Senden der Adresse
	TWDR = ui_adres;										// Adresse
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	//Senden von Daten
	TWDR = ui_data;											// Daten
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Stoppbedingung
	TWCR = (1 << TWINT) | (1 << TWST) | (1 << TWEN);		// Stoppbedingung
}



/* Beschreibung:		  Senden von zwei Bytes (ui_data1/2) über I2C an ui_adres
 *						        Grundgedanken -> nutze ui_data1 als Offset im Zielspeicher und ui_data2 zur Überschreibung dieses einen Ziel-Bytes
 * Globale Variablen:	Keine
 */
void sendTwoByteI2C(uint8_t ui_adres, uint8_t ui_data1, uint8_t ui_data2){
	// Startbedingung
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);		// Startbedingung
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Senden der Adresse
	TWDR = ui_adres;										// Adresse
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	//Senden von Daten
	TWDR = ui_data1;										// Daten 1
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	//Senden von Daten
	TWDR = ui_data2;										// Daten 2
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Stoppbedingung
	TWCR = (1 << TWINT) | (1 << TWST) | (1 << TWEN);		// Stoppbedingung
}



/* Beschreibung:	  	Senden von bis zu 16 Byte an ui_adress mit vorgestelltem versenden des Offsets im Zielspeicher
 * Parameter:			    ui_adres = Adresse des Slave
 *						        ui_data = Daten die gesendet werden sollen
 *						        ui_numberOfData = Anzahl der zu versendenden Daten
 *						        ui_memoryOffset = Offset im Speicher der LED-Ausgane -> dieses Byte wird als erstes Datenbyte versendet
 * Ablauf:				    Senden der Adresse - Senden des ui_memoryOffset als erstes Datenbyte - senden der Datenbytes aus ui_data[] von 0 bis ui_dataNumber-1!
 *						        Bsp. senden von 8 Byte -> ui_memoryOffset = 8; ui_data[0 bis 7]
 * Globale Variablen:	Keine
 */
void sendLedDataI2C(uint8_t ui_adres, uint8_t ui_data[16], uint8_t ui_numberOfData, uint_8 ui_memoryOffset){
	// Startbedingung
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);		// Startbedingung
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Senden der Adresse
	TWDR = ui_adres;										// Adresse
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Senden des ersten Datenbytes (= ui_memoryOffset)
	TWDR = ui_memoryOffset;									// Speicheroffset
	TWCR = (1 << TWINT) | (1 << TWEN);						// Senden
	while((TWCR & (1 << TWINT)) == 0){};					// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig

	// Senden der Datenbytes von [0] bis [ui_numberOfData-1]
	for(uint8_t ui_count = 0; ui_count < ui_numberOfData; ui_count++){
		//Senden von Daten
		TWDR = ui_data[ui_count];							// Daten[ui_count]
		TWCR = (1 << TWINT) | (1 << TWEN);					// Senden
		while((TWCR & (1 << TWINT)) == 0){};				// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig
	}

	// Stoppbedingung
	TWCR = (1 << TWINT) | (1 << TWST) | (1 << TWEN);		// Stoppbedingung
}
