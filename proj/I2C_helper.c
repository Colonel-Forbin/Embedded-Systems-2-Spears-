#include "I2C_helper.h"
#define MAXRETRIES              5

void I2CSetup(void)
{
	
/*	SYSCTL_RCGCI2C_R |= 0x0001;           // activate I2C0
	SYSCTL_RCGCGPIO_R |= 0x0002;          // activate port B
	while((SYSCTL_PRGPIO_R&0x0002) == 0){};// ready?
  SYSCTL_RCGCI2C_R |= (1<<0); // Using I2C0 module
	SYSCTL_RCGCGPIO_R |= (1<<1); // Enable clock to PortB
	GPIO_PORTB_AFSEL_R |= (0x06<<1); //enable alt function on pins 2 and 3	
	GPIO_PORTB_ODR_R |= (1<<3); // Open drain on pb3
	GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB2_I2C0SCL; //PIN 2 is now serial clock 
	GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_I2C0SDA; //PIN 3 is now serial data
	GPIO_PORTB_CR_R |= (0x06<<1);
	I2CMasterEnable(I2C0_BASE);  //Initialize master to do work and stuff   
	I2C0_MTPR_R = 0x09; //Correct clock speed for fast mode a 3 would be fast mode plus */


  SYSCTL_RCGCI2C_R |= 0x0001;           // activate I2C0
  SYSCTL_RCGCGPIO_R |= 0x0002;          // activate port B
  while((SYSCTL_PRGPIO_R&0x0002) == 0){};// ready?
  GPIO_PORTB_AFSEL_R |= 0x0C;           // 3) enable alt funct on PB2,3
  GPIO_PORTB_ODR_R |= 0x08;             // 4) enable open drain on PB3 only
  GPIO_PORTB_DEN_R |= 0x0C;             // 5) enable digital I/O on PB2,3              
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF00FF)+0x00003300; // 6) configure PB2,3 as I2C
  GPIO_PORTB_AMSEL_R &= ~0x0C;          // 7) disable analog functionality on PB2,3
  I2C0_MCR_R = I2C_MCR_MFE;      // 9) master function enable
  I2C0_MTPR_R = 0x09; //Correct clock speed for fast mode a 3 would be fast mode plus
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);	
 
/*	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0))
  {
  }
	I2CMasterEnable(I2C0_BASE);
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);
	I2CMasterSlaveAddrSet(I2C0_BASE, 0x70, false);	
*/	
}
void DisplayBoot(){
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C0_MSA_R = (0x70<<1)&0xFE;    // MSA[7:1] is slave address
  I2C0_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C0_MDR_R = 0x21&0xFF;         // prepare first byte
  I2C0_MCS_R = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
        
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C0_MSA_R = (0x70<<1)&0xFE;    // MSA[7:1] is slave address
  I2C0_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C0_MDR_R = 0x81&0xFF;         // prepare first byte
  I2C0_MCS_R = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
                                     
	printf("Enter brightness value E0-EF\n");
	uint8_t data2 = getc(stdin);
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C0_MSA_R = (0x70<<1)&0xFE;    // MSA[7:1] is slave address
  I2C0_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C0_MDR_R = data2&0xFF;         // prepare first byte
  I2C0_MCS_R = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
  printf("%0x", (I2C0_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR)));
}

void I2C_Send1(){
	
	uint16_t displayBuffer[8];
	printf("Enter value to send now\n");
	uint8_t data1 = getc(stdin);
	for (uint8_t i = 0; i < 8; i++){
  displayBuffer[i] = 0x0000 ;
	}
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C0_MSA_R = (0x70<<1)&0xFE;    // MSA[7:1] is slave address
  I2C0_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C0_MDR_R = 0x00&0xFF;         // prepare first byte
  I2C0_MCS_R = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
		
	for (uint8_t i = 0; i < 8; i++){
	while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C0_MSA_R = (0x70<<1)&0xFE;    // MSA[7:1] is slave address
  I2C0_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C0_MDR_R = (displayBuffer[i]&0xFF);         // prepare first byte
  I2C0_MCS_R = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done

	while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C0_MSA_R = (0x70<<1)&0xFE;    // MSA[7:1] is slave address
  I2C0_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C0_MDR_R = (displayBuffer[i]>>8);         // prepare first byte
  I2C0_MCS_R = (0
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C0_MCS_R&I2C_MCS_BUSY){};// wait for transmission done	
 
}
}
