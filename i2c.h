// #include<avr/io.h>


/* Makros und Defines */

 
/* Funktionen */
void initI2C();
void sendOneByteI2C(uint8_t ui_adres, uint8_t ui_data);
void sendTwoByteI2C(uint8_t ui_adres, uint8_t ui_data1, uint8_t ui_data2);
void sendLedDataI2C(uint8_t ui_adres, uint8_t ui_data[16], uint8_t ui_numberOfData, uint_8 u
