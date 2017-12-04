#include "Systick_helper.h"


void ClockSetup()
{
	/*  // 0) configure the system to use RCC2 for advanced features
  //    such as 400 MHz PLL and non-integer System Clock Divisor
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  // 4) set the desired system divider and the system divider least significant bit
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
                  + (7<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;*/
		
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL| SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}

void SystickSetup()
{
	NVIC_ST_CTRL_R = 0;              //disable SysTick during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF;   //maximum reload value
	NVIC_ST_CURRENT_R = 0;           //any write to current clears it
	NVIC_ST_CTRL_R = 0x00000005;     //enable SysTick with core clock

}

void Systick_Wait(uint32_t tickestdelay)        
{
	NVIC_ST_RELOAD_R = tickestdelay-1;            //number of counts to wait
	NVIC_ST_CURRENT_R = 0;                        //any value written to CURRENT clears
	while ((NVIC_ST_CTRL_R&0x0010000)==0) { }	    //wait for COUNT flag
}

void Systick_Wait10ms(uint32_t tickestdelay)
{
	for(uint32_t i = 0 ; i < tickestdelay ; i++)  
	{
		
		Systick_Wait(800000);                              //wait 10 ms. (12.5 ns period for 80MHz clock implies 800000 will set this function up properly)
    
	}
}