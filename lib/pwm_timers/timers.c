/* The MIT License (MIT)
 * Copyright (c) 2015 Enrico Sanino
 * File:   timers.c
 * Author: Enrico Sanino
 *
 * Created on 28 febbraio 2015, 18.42
 */

/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

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
#include "system.h"
#include "timers.h"
#endif


#ifdef _timer0
void initTimer0(uint16_t prescaler, _t_bitmode bitmode, _t_edge edge, _t_timer_clock clock, _t_timer_int timer_int,  _t_priority prio, uint8_t rpn){
    T0CON = 0;
    switch (prescaler){
        case 0:
            T0CON = 0x08; //PSA bit
            break;
        case 2:
            T0CON = 0;
            break;
        case 4:
            T0CON = 1;
            break;
        case 8:
            T0CON = 2;
            break;
        case 16:
            T0CON = 3;
            break;
        case 32:
            T0CON = 4;
            break;
        case 64:
            T0CON = 5;
            break;
        case 128:
            T0CON = 6;
            break;
        case 256:
            T0CON = 7;
            break;
        default:
            T0CON = 0;
            break;
    }
    switch (bitmode){
        case T16BIT:
            T0CON &= ~(0x40); //T08BIT bit
            break;
        case T8BIT:
            T0CON |= 0x40;
            break;
    }
    switch (edge){
        case RISING:
            T0CON &= ~(0x10); //T0SE bit
            break;
        case FALLING:
            T0CON |= 0x10;
            break;
    }
    switch (clock){
        case CLKOSC:
            T0CON &= ~(0x20); //T0CS bit
            break;
        case CLKPIN:
            RPINR4 = rpn; // Timer external clock input
            T0CON |= 0x20;
            break;
    }
        switch (timer_int){
        case TMRINT_ON:
            INTCONbits.TMR0IE = 1;
            break;
        case TMRINT_OFF:
            INTCONbits.TMR0IE = 0;
            break;
    }
    if (prio == HIGH_PRI) {
        INTCON2bits.TMR0IP = 1;
    } else {INTCON2bits.TMR0IP = 0;}



}

void startTimer0()
{
    T0CON |= 0x80;
}
void stopTimer0(){
    T0CON &= ~(0x80);
}
uint16_t readTimer0(){
    if (T0CON & 0x40) {
        return ((uint16_t)TMR0L);
    }
    else {
        uint8_t temp = TMR0L;
        return ((uint16_t)(TMR0H << 8)+(uint16_t)(temp));
    }
}
void writeTimer0(uint16_t value){
    if (T0CON & 0x40) {
        TMR0L = (uint8_t)(TMR0L);
    }
    else {
        TMR0H = (uint8_t)(value >> 8);
        TMR0L = (uint8_t)(value);
    }
}

#endif

#ifdef _timer1
void initTimer1(uint16_t presc, _t_timer_clock clock, _t_timer_int timer_int, _t_priority prio){
 T1CON = 0;
    switch (presc){
        case 1:
            T1CON &= ~(0x30); //T1CKPS bit
            break;
        case 2:
            T1CON |= 0x10;
            break;
        case 4:
            T1CON |= 0x20;
            break;
        case 8:
            T1CON |= 0x30;
            break;
        default:
            T1CON &= ~(0x30);
            break;
    }
    switch (clock){
        case CLKPIN:
            TRISCbits.TRISC0 = 1;
            T1CON |= 0x80; //TMR1CS bit
            break;
        case CLKOSC:
            T1CON |= 0x40;
            break;
        case CLKINST:
            T1CON |= 0x00;
            break;
    }
     switch (timer_int){
        case TMRINT_ON:
            PIE1bits.TMR1IE=1;
            break;
        case TMRINT_OFF:
            PIE1bits.TMR1IE=0;
            break;
    }
    T1CONbits.NOT_T1SYNC = 0; //syncron
    T1CONbits.RD16 = 1; //read word-wide
    if (prio == HIGH_PRI) {
        IPR1bits.TMR1IP = 1;
    } else IPR1bits.TMR1IP = 0;

}

void initTimer1Gate(uint8_t cfg, _t_timer_int timer_int, _t_priority prio){
    
    T1GCON = cfg;
    switch (timer_int){
        case TMRINT_ON:
            PIE5bits.TMR1GIE=1;
            break;
        case TMRINT_OFF:
            PIE5bits.TMR1GIE=0;
            break;
    }
    if (prio == HIGH_PRI) {
        IPR5bits.TMR1GIP = 1;
    } else IPR5bits.TMR1GIP = 0;
}

void startTimer1(){
    T1CONbits.TMR1ON = 1;
}

void stopTimer1(){
    T1CONbits.TMR1ON = 0;
}

uint16_t readTimer1(){
    uint8_t temp = TMR1L;
    return ((uint16_t)(TMR1H << 8)+(uint16_t)(temp));
}
void writeTimer1(uint16_t value){
    TMR1H = (uint8_t)(value >> 8);
    TMR1L = (uint8_t)(value);
}

#endif

#ifdef _timer2
void initTimer2(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio){

    T2CON = 0;
    switch (presc){
        case 1:
            T2CON |= 0x00; //T2CKPS bit
            break;
        case 4:
            T2CON |= 0x01;
            break;
        case 16:
            T2CON |= 0x02;
            break;
        default:
            T2CON |= 0x00; //T2CKPS bit
            break;
    }
    T2CON |= ((post-1) << 3);
    switch (timer_int){
        case TMRINT_ON:
            PIE1bits.TMR2IE=1;
            break;
        case TMRINT_OFF:
            PIE1bits.TMR2IE=0;
            break;
    }
     if (prio == HIGH_PRI) {
        IPR1bits.TMR2IP = 1;
    } else IPR1bits.TMR2IP = 0;
}

uint8_t readTimer2(){
    return (TMR2);
}
void writeTimer2(uint8_t value){
    TMR2 = value;
}

void timer2Comp(uint8_t comparator){
        PR2 = comparator;
}


void startTimer2(){
    T2CONbits.TMR2ON = 1;
}

void stopTimer2(){
    T2CONbits.TMR2ON = 0;
}
#endif

#ifdef _timer3
void initTimer3(uint16_t presc, _t_timer_clock clock, _t_timer_int timer_int, _t_priority prio, uint8_t rpn){
 T3CON = 0;
    switch (presc){
        case 1:
            T3CON &= ~(0x30); //T1CKPS bit
            break;
        case 2:
            T3CON |= 0x10;
            break;
        case 4:
            T3CON |= 0x20;
            break;
        case 8:
            T3CON |= 0x30;
            break;
        default:
            T3CON &= ~(0x30);
            break;
    }
    switch (clock){
        case CLKPIN:
            // Timer external clock input
            RPINR6 = rpn;
            T3CON |= 0x80; //TMR1CS bit
            break;
        case CLKOSC:
            T3CON |= 0x40;
            break;
        case CLKINST:
            T3CON |= 0x00;
            break;
    }
     switch (timer_int){
        case TMRINT_ON:
            PIE2bits.TMR3IE=1;
            break;
        case TMRINT_OFF:
            PIE2bits.TMR3IE=0;
            break;
    }
    T3CONbits.NOT_T3SYNC = 0; //syncron
    T3CONbits.RD16 = 1; //read word-wide
    if (prio == HIGH_PRI) {
        IPR2bits.TMR3IP = 1;
    } else IPR2bits.TMR3IP = 0;
}

void initTimer3Gate(uint8_t cfg, _t_timer_int timer_int, _t_priority prio){

    T3GCON = cfg;
    switch (timer_int){
        case TMRINT_ON:
            PIE3bits.TMR3GIE=1;
            break;
        case TMRINT_OFF:
            PIE3bits.TMR3GIE=0;
            break;
    }
    if (prio == HIGH_PRI) {
        IPR3bits.TMR3GIP = 1;
    } else IPR3bits.TMR3GIP = 0;
}

void startTimer3(){
    T3CONbits.TMR3ON = 1;
}

void stopTimer3(){
    T3CONbits.TMR3ON = 0;
}

uint16_t readTimer3(){
    uint8_t temp = TMR3L;
    return ((uint16_t)(TMR3H << 8)+(uint16_t)(temp));
}
void writeTimer3(uint16_t value){
    TMR3H = (uint8_t)(value >> 8);
    TMR3L = (uint8_t)(value);
}

#endif

#ifdef _timer5
void initTimer5(uint16_t presc, _t_timer_clock clock, _t_timer_int timer_int, _t_priority prio, uint8_t rpn){
 T5CON = 0;
    switch (presc){
        case 1:
            T5CON &= ~(0x30); //T1CKPS bit
            break;
        case 2:
            T5CON |= 0x10;
            break;
        case 4:
            T5CON |= 0x20;
            break;
        case 8:
            T5CON |= 0x30;
            break;
        default:
            T5CON &= ~(0x30);
            break;
    }
    switch (clock){
        case CLKPIN:
            // Timer external clock input
            RPINR15 = rpn;
            T5CON |= 0x80; //TMR1CS bit
            break;
        case CLKOSC:
            T5CON |= 0x40;
            break;
        case CLKINST:
            T5CON |= 0x00;
            break;
    }
     switch (timer_int){
        case TMRINT_ON:
            PIE5bits.TMR5IE=1;
            break;
        case TMRINT_OFF:
            PIE5bits.TMR5IE=0;
            break;
    }
    T5CONbits.NOT_T5SYNC = 0; //syncron
    T5CONbits.RD16 = 1; //read word-wide
    if (prio == HIGH_PRI) {
        IPR5bits.TMR5IP = 1;
    } else IPR5bits.TMR5IP = 0;
}

void initTimer5Gate(uint8_t cfg, _t_timer_int timer_int, _t_priority prio){

    T5GCON = cfg;
    switch (timer_int){
        case TMRINT_ON:
            PIE5bits.TMR5GIE=1;
            break;
        case TMRINT_OFF:
            PIE5bits.TMR5GIE=0;
            break;
    }
    if (prio == HIGH_PRI) {
        IPR5bits.TMR5GIP = 1;
    } else IPR5bits.TMR5GIP = 0;
}

void startTimer5(){
    T5CONbits.TMR5ON = 1;
}

void stopTimer5(){
    T5CONbits.TMR5ON = 0;
}

uint16_t readTimer5(){
    uint8_t temp = TMR5L;
    return ((uint16_t)(TMR5H << 8)+(uint16_t)(temp));
}
void writeTimer5(uint16_t value){
    TMR5H = (uint8_t)(value >> 8);
    TMR5L = (uint8_t)(value);
}

#endif

#ifdef _timer4
void initTimer4(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio){

    T4CON = 0;
    switch (presc){
        case 1:
            T4CON |= 0x00; //T2CKPS bit
            break;
        case 4:
            T4CON |= 0x01;
            break;
        case 16:
            T4CON |= 0x02;
            break;
        default:
            T4CON |= 0x00; //T2CKPS bit
            break;
    }
    T4CON |= ((post-1) << 3);

    switch (timer_int){
        case TMRINT_ON:
            PIE3bits.TMR4IE=1;
            break;
        case TMRINT_OFF:
            PIE3bits.TMR4IE=0;
            break;
    }
     if (prio == HIGH_PRI) {
        IPR3bits.TMR4IP = 1;
    } else IPR3bits.TMR4IP = 0;
}

uint8_t readTimer4(){
    return (TMR4);
}
void writeTimer4(uint8_t value){
    TMR4 = value;
}

void timer4Comp(uint8_t comparator){
        PR4 = comparator;
}

void startTimer4(){
    T4CONbits.TMR4ON = 1;
}

void stopTimer4(){
    T4CONbits.TMR4ON = 0;
}
#endif


#ifdef _timer6
void initTimer6(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio){

    T6CON = 0;
    switch (presc){
        case 1:
            T6CON |= 0x00; //T2CKPS bit
            break;
        case 4:
            T6CON |= 0x01;
            break;
        case 16:
            T6CON |= 0x02;
            break;
        default:
            T6CON |= 0x00; //T2CKPS bit
            break;
    }
    T6CON |= ((post-1) << 3);
    switch (timer_int){
        case TMRINT_ON:
            PIE5bits.TMR6IE=1;
            break;
        case TMRINT_OFF:
            PIE5bits.TMR6IE=0;
            break;
    }
     if (prio == HIGH_PRI) {
        IPR5bits.TMR6IP = 1;
    } else IPR5bits.TMR6IP = 0;
}

uint8_t readTimer6(){
    return (TMR6);
}
void writeTimer6(uint8_t value){
    TMR6 = value;
}

void timer6Comp(uint8_t comparator){
        PR6 = comparator;
}

void startTimer6(){
    T6CONbits.TMR6ON = 1;
}

void stopTimer6(){
    T6CONbits.TMR6ON = 0;
}

#endif


#ifdef _timer8
void initTimer8(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio){

    T8CON = 0;
    switch (presc){
        case 1:
            T8CON |= 0x00; //T2CKPS bit
            break;
        case 4:
            T8CON |= 0x01;
            break;
        case 16:
            T8CON |= 0x02;
            break;
        default:
            T8CON |= 0x00; //T2CKPS bit
            break;
    }
    T8CON |= ((post-1) << 3);

    switch (timer_int){
        case TMRINT_ON:
            PIE5bits.TMR8IE=1;
            break;
        case TMRINT_OFF:
            PIE5bits.TMR8IE=0;
            break;
    }
     if (prio == HIGH_PRI) {
        IPR5bits.TMR8IP = 1;
    } else IPR5bits.TMR8IP = 0;
}

uint8_t readTimer8(){
    return (TMR8);
}
void writeTimer8(uint8_t value){
    TMR8 = value;
}

void timer8Comp(uint8_t comparator){
        PR8 = comparator;
}

void startTimer8(){
    T8CONbits.TMR8ON = 1;
}

void stopTimer8(){
    T8CONbits.TMR8ON = 0;
}
#endif


