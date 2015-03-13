#Overview

I2C libraries for a PIC18FxxJ53 family. There is support now for only one bus, where are two in these devices. 

#Usage

These libraries are supporting 3 functional modes:
- _MASTER mode, which need to be defined by putting ```#define _MASTER``` in the header, will enable all the master functions
- _SLAVE mode, which need to be defined by putting ```#define _SLAVE``` in the header, will enable all the slave functions
- _MIXED mode, the default one, which need to be defined by putting ```#define _MIXED``` or not defining anything in the header, will enable all the I2C handling capabilities

Code in i2c headers contains some apparently random bits, but are related to the SSPxSTAT register of PIC18FxxJ53 family, which keep trace of the status of the bus.

```
#define SLAVE_ADDR 0x68
#define SLAVE_STATUS 0b00101101
#define ADX_W 0b00001001
#define DATA_W 0b00101001
#define ADX_R 0b00001100
#define DATA_R 0b00101100
#define ERR 0b00101100
#define MASK_BF_BIT 0xFE
#define UNMASK_S_BIT 0x08
```

If the device change, they need to be checked again.

##Functions usage

- **void i2c_init (_t_i2c_mode mode, uint8_t bus)** initialize the module with a given baudrate is master, or a given address if slave.

  - *mode* can be ```I2C_MASTER``` or ```I2C_SLAVE```. Every call will reset all previous initializations, allowing to swith the application from master to slave and viceversa.
  - *bus* can be either 0 or 1, depending on what hardware module is desired. In this version, only 0 is supported.

- **SLAVE_ADDR** is self explanatory

- **void i2cSlaveHandler(uint8_t bus)**
  - Describes a state machine which is used to understand the type of the last received byte from the bus.

- **void i2c_start(uint8_t bus)** put bus in start condition
- **void i2c_repStart(uint8_t bus)** put bus in repeated start condition
- **void i2c_stop(uint8_t bus)** guess what, it will put a stop condition
- **unsigned char i2c_read( unsigned char ack, uint8_t bus )** read from *bus* and transmit back an inverted *ack* signal, while returning the received byte.
- **unsigned char i2c_write( unsigned char i2cWriteData, uint8_t bus )** write *i2CWriteData* to *bus*, it returns 0.
- **uint8_t isAckI2C(uint8_t bus)** return a true boolean value if the slave acknowledge.

This library rely on the *system.h* header, which defines the oscillator settings. This library is made of a PLL clock of 48MHz, therefore the I2C clocking settings are based on PLL mode on as a primary oscillator.

- ** void mainOsc(_t_pllmode, _t_clksource) ** uses a *PLL_ON* mode as a primary *CLK_PRI* oscillator
- ** void secondOsc(_t_soscmode) ** not needed for this lib.

# Compiling

These libs are developed using the XC8 v1.20 compiler. Copy them in your project and include the *system.h* and *i2c.h*. I've left these headers
separated to have more flexibility. Make sure that the IDE do not uses the I2C default libraries, this is IDE dependent.
