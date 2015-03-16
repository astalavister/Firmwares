/* The MIT License (MIT)
 * Copyright (c) 2015 Enrico Sanino
 * File:   timers.h
 * Author: Enrico Sanino
 *
 * Created on 28 febbraio 2015, 18.42
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif



typedef enum {T16BIT, T8BIT} _t_bitmode;
typedef enum {RISING, FALLING} _t_edge;
typedef enum {CLKPIN, CLKOSC, CLKINST} _t_timer_clock;
typedef enum {TMRINT_ON, TMRINT_OFF} _t_timer_int;

#ifdef _timer0
void initTimer0(uint16_t, _t_bitmode, _t_edge, _t_timer_clock, _t_timer_int,  _t_priority, uint8_t );
void startTimer0();
void stopTimer0();
uint16_t readTimer0();
void writeTimer0(uint16_t value);
#endif

#ifdef _timer1
void initTimer1(uint16_t presc, _t_timer_clock, _t_timer_int, _t_priority);
void initTimer1Gate(uint8_t, _t_timer_int, _t_priority);
void startTimer1();
void stopTimer1();
uint16_t readTimer1();
void writeTimer1(uint16_t value);
#endif

#ifdef _timer2
void initTimer2(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio);
void timer2Comp(uint8_t);
void startTimer2();
void stopTimer2();
uint8_t readTimer2();
void writeTimer2(uint8_t value);
#endif


#ifdef _timer3
void initTimer3(uint16_t presc, _t_timer_clock, _t_timer_int, _t_priority, uint8_t);
void initTimer3Gate(uint8_t, _t_timer_int, _t_priority);
void startTimer3();
void stopTimer3();
uint16_t readTimer3();
void writeTimer3(uint16_t value);
#endif

#ifdef _timer4
void initTimer4(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio);
void timer4Comp(uint8_t);
void startTimer4();
void stopTimer4();
uint8_t readTimer4();
void writeTimer4(uint8_t value);
#endif

#ifdef _timer5
void initTimer5(uint16_t presc, _t_timer_clock, _t_timer_int, _t_priority, uint8_t);
void initTimer5Gate(uint8_t, _t_timer_int, _t_priority);
void startTimer5();
void stopTimer5();
uint16_t readTimer5();
void writeTimer5(uint16_t value);
#endif

#ifdef _timer6
void initTimer6(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio);
void timer6Comp(uint8_t);
void startTimer6();
void stopTimer6();
uint8_t readTimer6();
void writeTimer6(uint8_t value);
#endif


#ifdef _timer8
void initTimer8(uint16_t presc, uint16_t post, _t_timer_int timer_int, _t_priority prio);
void timer8Comp(uint8_t);
void startTimer8();
void stopTimer8();
uint8_t readTimer8();
void writeTimer8(uint8_t value);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

