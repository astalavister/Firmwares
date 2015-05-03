#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "lcd.h"
#include "lcd_hal.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */

extern uint8_t slowFlag;

void putch(char c){

   write_com_4bit(LCD_WRITEDATA|c);
   while (write_com_4bit(LCD_BUSYCHECK) != 0);
   if (slowFlag == 1){
       __delay_ms(15);
       __delay_ms(15);
       __delay_ms(15);
       __delay_ms(15);
       __delay_ms(15);

   }
//    while(!PIR1bits.TX1IF);
//    TXREG1 = c;

}

void lcd_gen_char(uint8_t address, char newChar[]){
    write_com_4bit(LCD_SETDDRAMADDR | address);
    while (write_com_4bit(LCD_BUSYCHECK) != 0);
    write_com_4bit(LCD_SETCGRAMADDR | (uint16_t)(address<<3));
    for (uint8_t i = 0; i < 8; i++){
        write_com_4bit(LCD_WRITEDATA|newChar[i]);
    }
}


void lcd_adx(uint8_t address){
	write_com_4bit(LCD_SETDDRAMADDR | address);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_clear(){
	write_com_4bit(LCD_CLEARDISPLAY);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_home_1(){
	write_com_4bit(LCD_RETURNHOME);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_home_2(){
	write_com_4bit(LCD_SETDDRAMADDR | 0x40);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void cursor_shift_L(){
	write_com_4bit(LCD_CURSORSHIFT);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void cursor_shift_R(){
	write_com_4bit(LCD_CURSORSHIFT | 0x04);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void disp_shift_L(){
	write_com_4bit(LCD_CURSORSHIFT | 0x08);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void disp_shift_R(){
	write_com_4bit(LCD_CURSORSHIFT | 0x0c);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_shift(){
	write_com_4bit(LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTINCREMENT);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_normal(){
	write_com_4bit(LCD_ENTRYMODESET|LCD_ENTRYLEFT);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_reverse(){
	write_com_4bit(LCD_ENTRYMODESET|LCD_ENTRYRIGHT);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_shift_reverse(){
	write_com_4bit(LCD_ENTRYMODESET|LCD_ENTRYRIGHT|LCD_ENTRYSHIFTINCREMENT);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
}

void lcd_cursor(uint8_t opt)
{
	if (opt==0){
		write_com_4bit(LCD_DISPLAYCONTROL | LCD_DISPLAYON| LCD_CURSOROFF | LCD_BLINKOFF);
		while (write_com_4bit(LCD_BUSYCHECK) != 0);
	}
	else if (opt==1){
		write_com_4bit(LCD_DISPLAYCONTROL | LCD_DISPLAYON| LCD_CURSOROFF | LCD_BLINKON);
		while (write_com_4bit(LCD_BUSYCHECK) != 0);
	}
	else if (opt == 2){
		write_com_4bit(LCD_DISPLAYCONTROL | LCD_DISPLAYON| LCD_CURSORON | LCD_BLINKOFF);
		while (write_com_4bit(LCD_BUSYCHECK) != 0);
	}
	else if (opt == 3) {
		write_com_4bit(LCD_DISPLAYCONTROL | LCD_DISPLAYON| LCD_CURSORON | LCD_BLINKON);
		while (write_com_4bit(LCD_BUSYCHECK) != 0);
	}
}

void pulse(){

        enPort(0);
	__delay_us(1);   // 1us enable cycle time
	enPort(1);
	__delay_us(1);
	enPort(0);
	__delay_us(100);
}


bool write_com(uint16_t comando){
	if (comando == LCD_BUSYCHECK)
	{
		bool flag = 1;
		TRISD = 0xFF; //8 bit data
		rsPort(0);
		rwPort(1);
		enPort(1);
		__delay_us(1);
		flag = PORTD & (1 << 7);
                enPort(0);
		__delay_us(100);
		TRISD = 0x00; //8 bit data

		return flag; // for checking purposes, ready flag
	}
	pPort_4bit(comando);
	rsPort(comando >> 9);
	rwPort(comando >> 8);  // R/W
	pulse();
	return 0; // scarta
}

bool write_com_4bit(uint16_t comando){
	if (comando == LCD_BUSYCHECK)
	{
		bool flag = 1;
		init_pPort_4bit(1);  //8 bit data
		rsPort(comando >> 9);
		rwPort(comando >> 8);  // R/W
                enPort(1);
		__delay_us(1);
		flag = pPort_4bit(0) & (1 << 3);
		enPort(0);
		__delay_us(100);
		pulse(); // secondo pulse
		init_pPort_4bit(0); //8 bit data in output
		return flag; // for checking purposes, ready flag
	}
	pPort_4bit((comando>>4) & 0x0f); // msb
	//uint8_t p = comando;
	rsPort(comando >> 9);
	rwPort(comando >> 8);  // R/W
	pulse();
	pPort_4bit(comando & 0x0f);
	rsPort(comando >> 9);
	rwPort(comando >> 8);  // R/W
	pulse();
	return 0; // scarta
}

bool lcd_init(){
      // LCD
  init_pPort_4bit(0); //4 bit data 0-3
  init_rsPort(); // RS
  init_rwPort();// R/#W
  init_enPort(); // E
  rsPort(0);
  rwPort(0);
  enPort(0);
	int i;
	for (i=0; i<100; i++) __delay_ms(1);
	pPort_4bit(0b00000011);
	rsPort(0);
        rwPort(0);
	pulse();
	__delay_ms(5);
	pPort_4bit(0b00000011);
	rsPort(0);
        rwPort(0);
	pulse();
	__delay_ms(5);
	pPort_4bit(0b00000011);
	rsPort(0);
        rwPort(0);
	pulse();
	__delay_us(200);
	pPort_4bit(0b00000010);
        rsPort(0);
        rwPort(0);
	pulse();

	write_com_4bit(LCD_FUNCTIONSET|LCD_4BITMODE|LCD_2LINE|LCD_5x8DOTS);
	__delay_ms(5);
	write_com_4bit(LCD_DISPLAYCONTROL | LCD_DISPLAYOFF);
	__delay_ms(5);
	write_com_4bit(LCD_CLEARDISPLAY);
	__delay_ms(5);
	write_com_4bit(LCD_ENTRYMODESET|LCD_ENTRYLEFT);
	__delay_ms(5);
	write_com_4bit(LCD_DISPLAYCONTROL | LCD_DISPLAYON| LCD_CURSOROFF | LCD_BLINKON);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
	write_com_4bit(LCD_RETURNHOME);
	while (write_com_4bit(LCD_BUSYCHECK) != 0);
	return 0; // scarta
}
