#Timers and PWM handling on PIC families 1.0

A full set of libraries for timers and capture/compare system. PWM is also supported. The enhanced modes are not supported yet.

## Capture/Compare libraries

Are supported modules numbered from 4 to 10, but indicated as generic *x*, below. The appropriate I/O pins are set accordingly.
The number *x* is associated to the physical module on datasheet of PIC18F47J53 MCU.

- **void initCCPx(_t_ccp , _t_used_timer tmr, _t_ccpint ccpint, _t_priority prio)** select if the module is used as capture, compare or PWM modes, what timer uses, if interrupt are used and their priority.
- **void compx(uint16_t comp)** write the 16bit value of the comparator
- **void pwmxInit(uint8_t comparator, uint16_t prescaler, uint16_t duty, _t_used_timer tmr)** inits the PWM module, where the period is given by the *instruction clock* divided by the *comparator* and the *prescale*. Its internally called functions can be used individually.
- **void pwmxDuty(uint16_t)** the PWM duty cycle, 10-bit resolution

Each module can be included in compilation by a proper ```#define ccpx```.

The enumeration that can be used in the above functions:

- **_t_ccp**: CCP_OFF, COMP_TOGGLE, COMP_HIGH, COMP_LOW, COMP_INT_ONLY, COMP_RST_TMR, CAPT_FALL,CAPT_RISE, CAPT_4RISE, CAPT_16RISE, CCP_PWM
- **_t_used_timer**: USE_TMR1, USE_TMR2, USE_TMR3, USE_TMR4, USE_TMR5, USE_TMR6, USE_TMR8
- **_t_ccpint**: CCPINT_ON, CCPINT_OFF (the interrupt capability)

The **_t_priority** is included in *system.h* file. If alredy included by other libraries written here, can be omitted.

## Timer libraries

- **void initTimerX(uint16_t prescaler, _t_bitmode bitmode, _t_edge edge, _t_timer_clock clock, _t_timer_int timer_int,  _t_priority prio, uint8_t rpn)** 
  - *prescaler* from one to 256 in powers of 2.
  - *bitmode*, 16bit timer with T16BIT or 8bit T8BIT
  - *edge* of clock, RISING or FALLING
  - *clock* source of the timer, can be from external clock input ar pin *rpn* or from system clock. In some timers the CLK_INST, the instruction clock, is supported. When the *rpn* is not present, refer to datasheet for what pin is related to. When *rpn* is present, the pin must configured accordingly before use it; otherwise it is already configured.
  - *timer_int* and *prio* are the enable of interrupts (TMRINT_ON or TMRINT_OFF) and its relative priority.
 
- Other functions ar epresent for each timer, like read/write/start/stop timerX. Can be handy, specially when using 16bit timers.
- Few timers are supporting also the compare mode (used in PWM mostly) and others the gate capabilities:
  - **void initTimerxGate(uint8_t cfg, _t_timer_int timer_int, _t_priority prio)** where cfg is a proper configuration word. It is not so nice since I didn't need the gate, yet.

- Timers 1, 3 and 5 can use the source clock CLKPIN. By default it is an external signal clock. By calling the **secondOsc(_t_soscmode = SOSC_ON)** those timers need a resonator on the MCU second oscillator pins. Use the datasheet to know what are.

# Compiling
These libs are developed using the XC8 v1.20 compiler. Copy them in your project and depending on what you need, you can include only *timers.h*, or *capturecompare.h* or *pwm.h*. Note that PWM header simply includes the first two.
