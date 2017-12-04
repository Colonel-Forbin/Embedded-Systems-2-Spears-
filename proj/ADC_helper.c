#include "ADC_helper.h"

void ADCSetup()
{
	GPIOPinTypeADC(GPIO_PORTB_BASE,GPIO_PIN_4); //Configure GPIO pins for ADC
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);                       //Enable ADC0 module
	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) { }             //Wait for ADC0 to be ready
	
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 1);     //Set trigger type and priorities for ADC sequences
	
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_IE | ADC_CTL_END |ADC_CTL_CH10);  //Set step number and configure channel numbers for ADC sequences
	
	ADCSequenceEnable(ADC0_BASE, 1);                                  //Enable ADC sampling on sequences 1,2 and 3
}
	
	void ADCRead() {
	uint32_t ADCvalueB4;	
	ADCProcessorTrigger(ADC0_BASE, 1);                                //Triggers ADC sampling sequence 1
	while(!ADCIntStatus(ADC0_BASE, 1, false)) { }                     //Wait until sampling sequence 1 is complete
	ADCSequenceDataGet(ADC0_BASE, 1, &ADCvalueB4);                    //Read in sampling sequence 1 value(s) 	
	
	
	printf("\n ADC B4 value = %lf \n",  (((((3.3/4095)*ADCvalueB4)-1.25)/.005)*1.8)+32 );                    //Print sampling sequence 1 value(s) 	
}