#include "Uart_helper.h"

//Modified from Valvano starter files.

//------------UART_InChar------------
// Wait for new serial port input
// Initialize the UART for 38400 baud rate 
// 8 bit word length, no parity bits, one stop bit, 
// Input: none
// Output: none
void UartSetup()
{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);		// Enable the UART0 module.
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
		{
			// Wait for the UART0 module to be ready.
		}
		
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); 		// activate port A
		GPIOPinConfigure(GPIO_PA0_U0RX); 								//Pin 0 is configured as receive
		GPIOPinConfigure(GPIO_PA1_U0TX); 								//Pin 1 is configured as transmit
		
		// enable alt funct on PA1-0 and enable digital I/O on PA1-0
		GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1|GPIO_PIN_1);
		GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
		
		// Initialize the UART. Set the baud rate, number of data bits, turn off
		// parity, number of stop bits, and stick mode. The UART is enabled by the
		//SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);   
		UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 38400,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

// Print a character to UART.
int fputc(int ch, FILE *f){
  if((ch == 10) || (ch == 13) || (ch == 27)){
    UART_OutChar(13);
    UART_OutChar(10);
    return 1;
  }
  UART_OutChar(ch);
  return 1;
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar()
{
	while((UART0_FR_R&UART_FR_RXFE) !=0){};
	return ((char)(UART0_DR_R&0xFF)); //returns the character from the port
}

// Get a character from UART.
int fgetc(FILE *f){
  return UART_InChar();
}

// Function called when file error occurs.
int ferror(FILE *f){
  /* Your implementation of ferror */
  return 1;
}
// this function does the same thing as UartSetup(), but uses direct register access method