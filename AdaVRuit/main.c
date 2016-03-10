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
	uint16_t feld[8] = { 0x8421, 0x8421, 0x8421, 0x8421, 0x8421, 0x8421, 0x8421, 0x8421 };
	printArray(feld);
	//clearDisplay();
	//printBit(0, 0, 1);
	while(1) {
		;
	}
	return 0;
}
