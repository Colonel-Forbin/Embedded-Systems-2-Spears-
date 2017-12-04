#include "PWM_helper.h"


void PWMSetup() //Sets up AND starts PWM on PB6
{
	GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_6); //Configure GPIO PB6 as a PWM pin
	GPIOPinConfigure( GPIO_PB6_M0PWM0 );        //Set GPIO PB6 to PWM0  
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); //Enable PWM0 peripheral
	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)) //Wait for PWM0 to be ready
    {    
		}
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); //Set the PWM generator for count down mode with immediate updates to the parameters
	PWMGenPeriodSet(PWM0_BASE,PWM_GEN_0, 8000);    //Sets a 10 KHz frequency for the 80 MHz clock
  PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,1500);   //Creates a 18.75% duty cycle 
  PWMGenEnable(PWM0_BASE, PWM_GEN_0);		         //Start timers in generator 0
	PWMOutputState(PWM0_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), true);		//Enable the output
}

void TestPWM() //Displays the PWM in full working order by visually comparing brightness of two LEDs
{
	PWMSetup();                                                         //Send PWM signal
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0xF);                     //Send full-strength signal
	for(int ui32Loop = 0; ui32Loop < 50000000; ui32Loop++)              //delay to soak in the PWM beauty
  {
 	}
	PWMOutputState(PWM0_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), false);  //Turn off PWM signal
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x0);                     //Turn off full-strength signal
	
	
}

