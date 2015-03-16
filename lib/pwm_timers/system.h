/* The MIT License (MIT)
 * Copyright (c) 2015 Enrico Sanino
 * File:   timers.h
 * Author: Enrico Sanino
 *
 * Created on 28 febbraio 2015, 18.42
 */
/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        48000000L
#define FCY             SYS_FREQ/4
#define _XTAL_FREQ      SYS_FREQ  // it is not the actual XTAL, but it is used by few functions

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */
#define _timer0
#define _timer1
#define _timer2
#define _timer3
#define _timer4
#define _timer5
#define _timer6
#define _timer8
#define ccp4
#define ccp5
#define ccp6
#define ccp7
#define ccp8
#define ccp9
#define ccp10


typedef enum {SOSC_ON, SOSC_OFF} _t_soscmode;
typedef enum {PLL_ON, PLL_OFF} _t_pllmode;
typedef enum {HIGH_PRI, LOW_PRI} _t_priority;
typedef enum {CLK_PRI, CLK_SEC, CLK_INT} _t_clksource;

void mainOsc(_t_pllmode, _t_clksource); /* Handles clock switching/osc initialization */
void secondOsc(_t_soscmode);
