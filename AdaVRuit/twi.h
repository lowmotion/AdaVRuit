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

/* TWI/I2C clock in Hz */
#define SCL_CLOCK  100000L

void twi_init();

uint8_t twi_start(uint8_t address);

void twi_stop(void);

uint8_t twi_write(uint8_t data);

#endif /* TWI_H_ */
