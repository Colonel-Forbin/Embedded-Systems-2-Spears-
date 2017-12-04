#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "tm4c123gh6pm.h"
#include "../inc/tm4c123gh6pm.h"
#include "systick.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "pin_map.h"


void SystickSetup(void);                             //Sets up Systick
void PLLSetup(void);                                 //Set clock speed
void SystickWait(uint32_t tickestdelay);             //(Used to set up Systick)
void Systick_Wait10ms(uint32_t tickestdelay);        //This function makes the Systick wait 10 ms
