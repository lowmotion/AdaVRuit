

/* Beschreibung:	Initialisierung des I2C
 *			Einstellung des SCL = (CPU_CLOCK)/(16+2*(TWBR)*4^(TWSR))
 *			Bustakt wurde auf rund 100kHz gesetzt.
 * Gloable Variablen:	Keine
 */
void initI2C(){
	TWBR |=	0x12;	// -> sollte bei einem Master > 10 sein -> wurde auf = 18 gesetzt
	TWSR |= 0x01;	// Prescale = 4^TWSR = 4
	TWCR = (1 << TWEN);
}



/* Beschreibung:  	Start (Aufbau) der I2C verbindung
 * Globale Variablen:	Keine
 */
void startTWI(){
	// Startbedingung
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);		// Startbedingung
	while(!(TWCR & (1 << TWINT))){};				// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig
}


/* Beschreibung:  	Senden der Daten
 * Globale Variablen:	Keine
 */
void sendTWI(uint8_t ui_data){
	// Senden der Daten
	TWDR = ui_data;							// Adresse
	TWCR = (1 << TWINT) | (1 << TWEN);				// Senden
	while(!(TWCR & (1 << TWINT))){};				// Warten bis TWINT-Bit (des Registers TWCR) == 1 -> fertig
}


/* Beschreibung:  	Beenden der I2C verbindung
 * Globale Variablen:	Keine
 */
void stopTWI(){
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);		// Stoppbedingung
}
