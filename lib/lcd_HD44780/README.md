# LCD 16x2 characters HD44780 handling libraries 1.0

LCD libraries for a PIC18FxxJ53 family. The algorithm can be ported on other MCUs since there is an Hardware Abstraction Level code which is device dependent, where the algorithm is contained in the *lcd.c* file, which is universal, if a proper HAL is adapted. The support is only for the 16x2 characters, but can be easily extended on other HD44780 compatible devices, by changing its initialization sequence. 

*NOTE that this is not a guide on how the HD44780 works, but is a firmware support for it and the description is on how to use the firmware. Therefore a base knowledge on the HD standard is required.*

It is released under MIT licence, inside LICENSE file in https://github.com/thexeno/Firmwares

#Usage

There is a list of parameters which are used for the typical commands for this Hitachi display. They are related to the most used commands and data types used by the HD44780 standard. 
These defines in the *lcd.h* are used to enable the specified function. Therefore, if **LCD_SETCGRAMADDR** is used, should be ORred with the address value. With this philosophy more parameters defined in the header can be orred together. For compatiblity reasons and simplicity, these values are extended in 16bit, to keep them aligned with the register interface of the display, which is 10bit wide.

At the moment, it is not supported the display for using it as a general purpose RAM.

##API

- **void pulse()** generates a pulse of proper duration on the E pin.
- **bool write_com(uint16_t comando)** issue a command on the display, using 8bit parallel interface
- **bool write_com_4bit(uint16_t comando)** issue a command on the display, using 4bit parallel interface
- **void lcd_gen_char(uint8_t address, char newChar[])** writes, at defined address, the character matrix for the custom character generator.
- **bool lcd_init()** initialize the display with default mode of 4bit parallel interface, 16x2 characters.
- **lcd_clear()** will blank the display and bring the cursor to home position at first row
- **lcd_home_1()** return the display to the first position at first row
- **lcd_home_2()** return the display to the first position at second row
- **cursor_shift_L()** or **cursor_shift_R()** at each call, moves the cursor toward left or right
- **disp_shift_L()** or **disp_shift_R()** at each call, moves the entire displayed data toward left or right
- **void lcd_shift()** enable the shift mode of the LCD
- **void lcd_normal()** enable the default mode of the LCD, which is static displayed data and cursor moving
- **void lcd_reverse()** enable the default mode of the LCD, but writing in reverse way
- **void lcd_shift_reverse()** enable the shift mode of the LCD, but reversed
- **void lcd_cursor(uint8_t opt)** set the type of cursor. 0 -> no cursor, 1 -> blink without cursor, 2 -> cursor without blink, 3 -> cursor and blink
- It is included the **putch(char c)** which can be exchanged with the standard one, in order to use the *printf* standard libraries.

##HAL

Here are present the functions which should be modified when changing the hardware

- **void rwPort(uint8_t val)** put the digital value to the RW pin.
- **void init_rwPort()** initialize correctly the MCU's RW port.
* The same is for RS and E port *
- **void init_pPort_4bit(uint8_t inOut)** initialize the 4bit interface as input (inOut = 1) or output (inOut = 0).
- **uint8_t pPort_4bit(uint8_t val)** write the val to the 4 bit port. If it was set as output, will return the value of 4 LSBs.

# Compiling

These libs are developed using the XC8 v1.20 compiler. Copy them in your project and include the *lcd.h* and *lcd_hal.h*. I've left these headers
separated to have more flexibility. To redirect the output of standard libraries to the LCD, make sure that the *putch()* in the *lcd.h* is compiled instead of the default one.



