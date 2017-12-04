#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "pin_map.h"
#include "adc.h"
#include "pwm.h"
#include "hw_pwm.h"
#include "hw_gpio.h"
#include "hw_types.h"

void PWMSetup(void);      //Sets up AND starts PWM on PB6
void TestPWM(void);       //Displays the PWM in full working order by visually comparing brightness of two LEDs