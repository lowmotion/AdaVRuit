 /*****************************************************************************
*
* FILE: 		      twi.h
* PROJECT:	      Spielekonsole
* MODULE:		      ???
*
* Description:		Header zu twi.c
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date:   02.03.2016
* BY:	    Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/

#ifndef TWI_H_
#define TWI_H_

#include <inttypes.h>
#include <util/twi.h>

#define F_CPU 16000000UL

/*  TWI_Adresse der LED-Matrix*/
#define LED_ADRESS_TWI              ???

/* TWI/I2C clock in Hz */
#define SCL_CLOCK  100000L

void twi_init();

uint8_t twi_start(uint8_t address);

void twi_stop(void);

uint8_t twi_write(uint8_t data);

void TWI_sendByte(uint8_t offset, uint8_t byte);

void TWI_sendArray(int8_t ui_matrix[8][2]);


#endif /* TWI_H_ */
