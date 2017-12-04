#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "pin_map.h"

void GpioSetup(void); //Sets up GPIO 
void CycleLEDs (void); //Turns 4 external LEDs and one on-board LED on and off in succession
void TestSwitches(void); //Reads switch values. CycleLEDs if a switch is pressed and prints switch values to the terminal for unpressed switches
uint8_t KeypadScan ();
uint8_t CANswitches();