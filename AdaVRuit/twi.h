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

void twi_init();

uint8_t twi_start(uint8_t address);

void twi_stop(void);

uint8_t twi_write(uint8_t data);

#endif /* TWI_H_ */
