 /*****************************************************************************
*
* FILE: 	 	main.c
* PROJECT:	      	Spielekonsole
* MODULE:		???
*
* Description:		Hauptprogramm
*
* Notes:		-
*
* Compiler dependencies or special instructions:
*
* REVISION HISTORY
* Date:   11.02.2016
* BY:	  Michel, Marco, Michael, Christian, Tobias
*
*****************************************************************************/

#include "main.h"
#include <util/delay.h>

 /**************************************************************************
* NAME:			main
* Description:		????? Wir haben schon eine main	?????
*
* Subroutines Called:	???
*
* Returns:		int = 0;
*
* Globals:		???
*
* Programmer(s):	Michel, Marco, Michael, Christian, Tobias
* Tested By: Date:

* NOTES:		-
*
* REVISION HISTORY
* Date: By: Description:
*
**************************************************************************/
int main() {
	initSystem();
	while(1) {
		for(short row = 0; row < 8; row++) {
			for(short column = 0; column < 16; column++) {
				printBit(row, column, 1);
				_delay_ms(100);
			}
		}
		for(short row = 0; row < 8; row++) {
			for(short column = 0; column < 16; column++) {
				printBit(row, column, 0);
				_delay_ms(100);
			}
		}
	}
	return 0;
}
