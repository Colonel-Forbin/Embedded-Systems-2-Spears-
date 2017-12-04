/*******************************************************************************************************************************************************|
|     This program displays basic use and initialization of vital embedded system concepts including PWM, ADC, GPIO, UART, SysTick and more.           | 
|     This code is not perfect but does exhibit some important factors of modularity and cohesion. An effort was made to keep the code relatively clean |
|     and easy to understand. In preparing this program I have developed critical skills in understanding how embedded systems work and how to use them |
|     to achieve a goal. Additionally, I have gained the ability to program the key peripherals of the microcontroller.                                 |
|                                                                                                                                                       |
|     The structure of the program is as follows:                                                                                                       |
|     First, this program sets up the hardware needed for the main function by calling the SetupHardware function, which calls the setup routines for   |
|     the necessary hardware components.                                                                                                                |
|     Then, displays a user-friendly menu with options to choose from. Option 1 will cycle through the connected LEDs if a switch is pressed and display|
|     the values of the switches that aren't pressed in order to test the GPIO. Option 2 will test use of the SysTick by turn on an LED for exactly one |
|     second. Option 3 will visually display proper use of the PWM module by turning on 2 LEDs at different brightness levels. Option 4 will test the   |
|     ADC by sampling 3 channels and printing their value to the user interface. If an unrecognized option is selected then the the program will print  |
|     "Wai you do dis?"                                                                                                                                 |
********************************************************************************************************************************************************/






#include "project.h"
#include <stdio.h>
#include <stdint.h>

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


void SetupHardware()
{
	ClockSetup();                  //Set clock
	UartSetup();                   //Set up UART
	GpioSetup();	                 //Set up GPIO
	I2CSetup();
	CAN_Init();
	ADCSetup();
}

int  main(void)
{
		uint8_t temp=0;             //This is the value used for the menu selection
	  
	  SetupHardware();            //Calls all hardware setup routines
   
    while(1) //main loop
    {  				
			printf("\n\nWelcome to this program.\nSelect an option:\n1. Test keypad \n2. Test switches \n3. Test I2C \n4.Test ADC  \n5. CAN mode "); //Prints a user friendly menu
			temp = getc(stdin);       //menu selection value used in the following switch statement
			switch (temp){
				case 1 :                
				KeypadScan();         //                         
				break;
				
				case 2 :                                           
				TestSwitches();			
				break;
				
				case 3 :
				DisplayBoot();
				while(1){	
				I2C_Send1();
				}	
				break;
				
				case 4 :
				ADCRead();	
        break;
				
				case 6 :
				LabMode();
				break;
				
				case 5 :
				CANmode();
				break;
				
				default:                                           //If user selects a random option the system asks why they 'did it' 
			  printf("\nWai you do dis?\n");				
			}			
	//*IGNORE THIS LINE*  UARTCharPut(UART0_BASE, temp);		//send a character			 
		}		
	}

	void LabMode(){
		int HotTemp; 
		printf("Enter overheat temperature");
		HotTemp = getc(stdin);
		//read thermo heat
		//send to display
		//if > HotTemp turn on fan
		//if < HotTemp turn off fan
		
				
	}
	