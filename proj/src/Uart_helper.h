#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "pin_map.h"


void UartSetup(void);		//sets up Uart for configuration using library

//redirect for printf.
int fputc(int ch, FILE *f);

//redirect input from serial port
//read info edit by: Sir Hutson
int fgetc(FILE *f);