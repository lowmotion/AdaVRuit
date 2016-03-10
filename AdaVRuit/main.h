 /*****************************************************************************
*
* FILE: 		      main.h
* PROJECT:	      Spielekonsole
* MODULE:		      ???
*
* Description:		Header zu main.c
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date:   11.02.2016
* BY:	    Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU			16000000UL
#define SCL_CLOCK 		100000L
#define SLAVE_ADRESS 	0xE0
#define LED_BRIGHTNESS	5

#include <avr/io.h>
#include <avr/interrupt.h>

#include "AdaVRuit.h"
#include "menu.h"
#include "pong.h"

#endif /* MAIN_H_ */
