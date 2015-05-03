/* 
 * File:   lcd_hal.h
 * Author: TheXeno
 *
 * Created on 8 aprile 2015, 14.26
 */

#ifndef LCD_HAL_H
#define	LCD_HAL_H

#ifdef	__cplusplus
extern "C" {
#endif

/****************************************************************/
void rwPort(uint8_t val);
void init_rwPort();
void rsPort(uint8_t val);
void init_rsPort();

void enPort(uint8_t val);
void init_enPort();

void init_pPort_4bit(uint8_t inOut);
uint8_t pPort_4bit(uint8_t val);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_HAL_H */

