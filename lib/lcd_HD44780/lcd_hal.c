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


/****************************************************************/
void rwPort(uint8_t val){
    PORTBbits.RB7 = val & 0x1;
}
void init_rwPort(){
   TRISBbits.TRISB7 = 0;
}
void rsPort(uint8_t val){
    PORTBbits.RB6 = val&0x1;
}
void init_rsPort(){
    TRISBbits.TRISB6 = 0;
}

void enPort(uint8_t val){
    PORTDbits.RD7 = val&0x1;
}
void init_enPort(){
     TRISDbits.TRISD7 = 0; // E
}

void init_pPort_4bit(uint8_t inOut){ //in/out by viewing toward MCU ports
    if (inOut) //if in
        TRISD |= 0x0F;
    else //out
        TRISD &= 0xF0; // keep 4 unused bit, output the others LSB
}
uint8_t pPort_4bit(uint8_t val){
    if (TRISD & 0x0F)
        return PORTD; //use port
    PORTD &= 0xF0; // keep 4 unused bit, prepare the others LSB... use LATD to modify
    PORTD |= val & 0x0F; //set values
    return 0;
}


/****************************************************************/
