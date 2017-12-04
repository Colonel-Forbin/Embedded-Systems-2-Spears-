#include "Gpio_helper.h"


	
void GpioSetup()
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);               //Enable GPIO peripherals
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
		

		
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))         //Wait for peripherals to be ready
    {    
		}
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
   	}
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    {   
		}
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
		
    // Set up switches and IR break-beam
		GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
		GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0);
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
		
		GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);	
		GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
		
		
		// Set GPIO keypad pins
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1); //
		GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2); //
		GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3); //
    
	  SYSCTL_RCGCGPIO_R |= 0x08;        // 1) activate port D
    while((SYSCTL_PRGPIO_R&0x08)==0){};   // allow time for clock to stabilize
		GPIO_PORTD_LOCK_R = 0x4C4F434B;   // 2  unlock PE3-1
    GPIO_PORTD_AMSEL_R &= ~0xCF;      // 3) disable analog functionality on PD3-0
    GPIO_PORTD_PCTL_R &= ~0x0000FFFF; // 4) GPIO
    GPIO_PORTD_DIR_R |= 0xCF;         // 5) make PD3-0 out
    GPIO_PORTD_AFSEL_R &= ~0xCF;      // 6) regular port function 
    GPIO_PORTD_DEN_R |= 0xCF;         // 7) enable digital I/O on PD3-0
		//*IGNORE THIS LINE* GPIO_PORTD_PUR_R = 0x0F;          // enable pull-up on PF0 and PF4	
					
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);
				
		}
	
uint8_t KeypadScan()
{
	uint8_t KeyVal;
	
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);
	
	KeyVal=0;
	
	printf("Port E pin 1 is %d\n", GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1));
	printf("Port E pin 2 is %d\n", GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2));
	printf("Port E pin 3 is %d\n", GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3));
	printf("Port D pin 2 is %d\n", GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2));

if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0){
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0xF);
            if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) > 0)
                KeyVal=1;
            else {
                GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xF);
                if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) > 0)
                    KeyVal=4; 
                else {
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0xF);
                    if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) > 0)
                        KeyVal=7; 
                    else KeyVal=0;
											} } }
if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0){
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0xF);
            if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) > 0)
                KeyVal=2;
            else {
                GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xF);
                if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) > 0)
                    KeyVal=5; 
                else {
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0xF);
                    if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) > 0)
                        KeyVal=8; 
                    else KeyVal=0;
											} } }
if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) == 0){
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0xF);
            if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) > 0)
                KeyVal=3;
            else {
                GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xF);
                if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) > 0)
                    KeyVal=6; 
                else {
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0xF);
                    if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) > 0)
                        KeyVal=9; 
                    else KeyVal=0;
											} } }
printf("\nKeypadScan value is %d \n", KeyVal);
											return KeyVal;
									}										
		
void CycleLEDS ()
{

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xF);        //^^^
  for(int ui32Loop = 0; ui32Loop < 500000; ui32Loop++)
  {
 	}      
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
	
}

void TestSwitches()
{
	int8_t switchC4;                                              
	int8_t switchF4;
	int8_t switchE0;
	switchE0 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0);   //Reads in pin values and stores them as variables
	switchF4 = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
  switchC4 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4);
	if ( switchC4 < 1)                                    //If a switch is pressed then cycle through through connected LEDs
		CycleLEDS();              
	else                                                  //Otherwise let the user know that the switch is set high and print its value 
		printf("\nSwitch C4 set high (%d)\n", switchC4);    //                 (continue for the rest of the LEDs)
	
	if ( switchF4 < 1)
		CycleLEDS();
	else
		printf("\nSwitch F4 set high (%d) \n", switchF4);
	
	if ( switchE0 < 1)
		CycleLEDS();
	else
		printf("\nSwitch E0 set high (%d) \n", switchE0);
 }

uint8_t CANswitches(){
	 uint8_t CANdata;
	 int8_t switchC4;
	 int8_t switchF4;
	 int8_t switchE0;
	 switchE0 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0);   //Reads in pin values and stores them as variables
	 switchF4 = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
   switchC4 = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4);	 
	 if (switchE0 < 1 && switchF4 < 1 && switchC4 < 1)
		 CANdata = 7;
	 
	 if (switchE0 < 1 && switchF4 < 1 && switchC4 < 0)
		 CANdata = 6;	 
	 
	 if (switchE0 < 1 && switchF4 < 1 && switchC4 > 0)
		 CANdata = 5;
	 
	 if (switchE0 < 1 && switchF4 > 0 && switchC4 < 1)
		 CANdata = 4;
	 
	 if (switchE0 < 1 && switchF4 > 0 && switchC4 > 0)
		 CANdata = 3;
	 
	 if (switchE0 > 0 && switchF4 < 1 && switchC4 < 1)
		 CANdata = 2;
	 
	 if (switchE0 > 0 && switchF4 > 0 && switchC4 < 1)
		 CANdata = 1;
	 
	 if (switchE0 > 0 && switchF4 > 0 && switchC4 > 0)
		 CANdata = 0;
	 printf("CANdata = %d\n", CANdata);
	 return CANdata;

		 
 }