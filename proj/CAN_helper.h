#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_memmap.h"

#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "stdbool.h"
#include "driverlib/can.h"
#include "inc/hw_memmap.h"
#include "./driverlib/sysctl.h"

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"

#include "driverlib/adc.h"
#include "driverlib/aes.h"
#include "driverlib/can.h"
#include "driverlib/comp.h"
#include "driverlib/cpu.h"
#include "driverlib/crc.h"
#include "driverlib/debug.h"
#include "driverlib/des.h"
#include "driverlib/eeprom.h"
#include "driverlib/emac.h"
#include "driverlib/epi.h"
#include "driverlib/flash.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/hibernate.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/lcd.h"
#include "driverlib/mpu.h"
#include "driverlib/onewire.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/rtos_bindings.h"
#include "driverlib/shamd5.h"
#include "driverlib/ssi.h"
#include "driverlib/sw_crc.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysexc.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/usb.h"
#include "driverlib/watchdog.h"
#include "tm4c123gh6pm.h"
#include "src/Uart_helper.h"

#define NUM_RX_MESSAGES 7
#define NUM_TX_MESSAGES 7

// place a 1 by each message you would like to receive

#define MESSAGE1 1			
#define MESSAGE2 1
#define MESSAGE3 1 
#define MESSAGE4 1
#define MESSAGE5 1
#define MESSAGE6 1
#define MESSAGE7 1


extern unsigned char MsgData[NUM_RX_MESSAGES][4];

void initReceiver(void);
void CAN_Transmit(uint8_t data[4], uint8_t msgSelect);
void CANIntHandler(void);
void CAN_Init(void);
void Init_Structs(void);
void CANmode(void);