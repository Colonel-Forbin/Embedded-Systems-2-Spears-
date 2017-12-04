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

void ADCSetup(void);      //