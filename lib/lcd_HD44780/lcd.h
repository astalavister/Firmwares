/* 
 * File:   lcd.h
 * Author: thexeno
 *
 * Created on 23 luglio 2014, 19.28
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

 #define LCD_CLEARDISPLAY 0x0001
#define LCD_RETURNHOME 0x0002
#define LCD_ENTRYMODESET 0x0004
#define LCD_DISPLAYCONTROL 0x0008
#define LCD_CURSORSHIFT 0x0010
#define LCD_FUNCTIONSET 0x0020
#define LCD_SETCGRAMADDR 0x0040
#define LCD_SETDDRAMADDR 0x0080
#define LCD_BUSYCHECK 0x0100
#define LCD_WRITEDATA 0x0200

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x0000
#define LCD_ENTRYLEFT 0x0002
#define LCD_ENTRYSHIFTINCREMENT 0x0001
#define LCD_ENTRYSHIFTDECREMENT 0x0000

// flags for display on/off control
#define LCD_DISPLAYON 0x0004
#define LCD_DISPLAYOFF 0x0000
#define LCD_CURSORON 0x0002
#define LCD_CURSOROFF 0x0000
#define LCD_BLINKON 0x0001
#define LCD_BLINKOFF 0x0000

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x0008
#define LCD_CURSORMOVE 0x0000
#define LCD_MOVERIGHT 0x0004
#define LCD_MOVELEFT 0x0000

// flags for function set
#define LCD_8BITMODE 0x010
#define LCD_4BITMODE 0x000
#define LCD_2LINE 0x008
#define LCD_1LINE 0x000
#define LCD_5x10DOTS 0x004
#define LCD_5x8DOTS 0x000


void pulse();
bool write_com(uint16_t comando);
bool write_com_4bit(uint16_t comando);
void lcd_gen_char(uint8_t address, char newChar[]);
bool lcd_init();
void lcd_clear();
void lcd_home_1();
void lcd_home_2();
void cursor_shift_L();
void cursor_shift_R();
void disp_shift_L();
void disp_shift_R();
void lcd_shift();
void lcd_normal();
void lcd_reverse();
void lcd_shift_reverse();
void pulse();
void lcd_adx(uint8_t address);
void lcd_cursor(uint8_t opt);
void putch(char c);

uint8_t slowFlag = 0;

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

