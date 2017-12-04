#include "CAN_helper.h"
#include "Gpio_helper.h"
#include <stdio.h>
#include <stdint.h>
// --------------------------------------------------------------------------------------
//			Global variables and structs:
// --------------------------------------------------------------------------------------
volatile bool errFlag = 0;                                                       // Transmission error flag
volatile bool rxFlag = 0;                                                        // Msg recieved flag

unsigned int msgData;                                                            // Four bytes of message data allocated as uint32
unsigned char *msgDataPtr = (unsigned char *)&msgData;                           // Pointer to message data for individual byte access

unsigned char RxMsgData[NUM_RX_MESSAGES][8];                                     // 8 byte buffer for RxObj[0] message data
unsigned char MsgData[NUM_RX_MESSAGES][4];                                   		 // Eventually will be external message data for Rx messages

tCANMsgObject TxObj[NUM_TX_MESSAGES], RxObj[NUM_RX_MESSAGES];                    // Set up Tx and Rx TCANMsgObject structs with defined quantites
// --------------------------------------------------------------------------------------
//			CAN initialize function:
// --------------------------------------------------------------------------------------
void CAN_Init(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);                                   // Enable GPIO for port E for use on CAN
	GPIOPinConfigure(GPIO_PE4_CAN0RX);                                             // Assign pin E4 to CAN0RX
	GPIOPinConfigure(GPIO_PE5_CAN0TX);                                             // Assign pin E5 to CAN0TX
	GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);                      // Enable pin type for CAN
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);                                    // Enable CAN periph
	printf("Initializing CAN0_BASE...\n");                                         // Printout for debugging
	CANInit(CAN0_BASE);                                                            // Initialize CAN0 base
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);                            // Set CAN bitrate
	printf("Setting CAN BitRate: 0.5 Megabytes/sec...\n");                         // Printout for debugging
	CANIntRegister(CAN0_BASE, CANIntHandler);                                      // Give dynamic vector table name of handler for CAN Interrupts
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);      // Enable CAN interrupts
	IntEnable(INT_CAN0);									                                         // Enable global interrupts
	CANEnable(CAN0_BASE);                                                          // Enable CAN functionality
	printf("CAN Initialized.\n\n");                                                // Printout for debugging
	Init_Structs();                                                                // Call function to initialize message structs
}
// --------------------------------------------------------------------------------------
//			CAN interrupt handler:
// --------------------------------------------------------------------------------------
void CANIntHandler(void) {

	unsigned long status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);						 // read interrupt status cause, 1-7 it will correspond with an Rx (1-7) or Tx (8-14) object, or be equal to 32768 for a system interrupt
	printf("Interrupt status id: %d\n", status);																	 // print status for debugging
	
	if(status == CAN_INT_INTID_STATUS) {                          								 // controller status interrupt
		status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);													 // read back error bits, do something with them?
		errFlag = 1;																																 // set error flag
	} 
	
	else if(1<=status & NUM_RX_MESSAGES >= status) {															 // if the interrupt status is from 1-7 an object has been received
		CANIntClear(CAN0_BASE, status); 																						 // clear interrupt	
		errFlag = 0;																																 // clear any error flags	
		CANMessageGet(CAN0_BASE, status, &RxObj[status-1], false); 									 // Get CAN message from buffer, store it into corresponding mailbox
		MsgData[status-1][0]=RxMsgData[status-1][0];																 // move from internal mailbox to buffer accessible by any module	
		MsgData[status-1][1]=RxMsgData[status-1][1];
		MsgData[status-1][2]=RxMsgData[status-1][2];
		MsgData[status-1][3]=RxMsgData[status-1][3];
	}

	else if((NUM_RX_MESSAGES+1)<=status & (NUM_RX_MESSAGES+NUM_TX_MESSAGES)>= status) { // if this case is triggered a message has been transmitted
		CANIntClear(CAN0_BASE, status);																							 // clear corresponding interrupt
		errFlag = 0;																																 // clear any error flags
}
	
	else {																																				 // should never happen
		printf("Unexpected CAN bus interrupt\n");
	}
}
// --------------------------------------------------------------------------------------
//			CAN transmit function:
// --------------------------------------------------------------------------------------
void CAN_Transmit(uint8_t data[4], uint8_t msgSelect){
		msgDataPtr[0] = data[0];
		msgDataPtr[1] = data[1];
		msgDataPtr[2] = data[2];
		msgDataPtr[3] = data[3];
		printf("Sending message %d:\tByte 1: %d\tByte 2: %d\tByte 3: %d\t Byte 4: %d\n", msgSelect, msgDataPtr[0], msgDataPtr[1], msgDataPtr[2], msgDataPtr[3]); // write colour to UART for debugging
		CANMessageSet(CAN0_BASE, (msgSelect+7), &TxObj[msgSelect-1], MSG_OBJ_TYPE_TX); // send as msg object 1
		printf("Message sent.\n");
	if(errFlag) { // check for errors
		printf("CAN Bus Error\n");
	}
}
// --------------------------------------------------------------------------------------
//			CAN receive functions:
// --------------------------------------------------------------------------------------

void initReceiver(){
	if(MESSAGE1)
	CANMessageSet(CAN0_BASE, 1, &RxObj[0], MSG_OBJ_TYPE_RX);	// Load msg into CAN peripheral message object 1 so it can trigger interrupts on any matched rx messages
	if(MESSAGE2)
	CANMessageSet(CAN0_BASE, 2, &RxObj[1], MSG_OBJ_TYPE_RX);
	if(MESSAGE3)
	CANMessageSet(CAN0_BASE, 3, &RxObj[2], MSG_OBJ_TYPE_RX);
	if(MESSAGE4)
	CANMessageSet(CAN0_BASE, 4, &RxObj[3], MSG_OBJ_TYPE_RX);
	if(MESSAGE5)
	CANMessageSet(CAN0_BASE, 5, &RxObj[4], MSG_OBJ_TYPE_RX);
	if(MESSAGE6)
	CANMessageSet(CAN0_BASE, 6, &RxObj[5], MSG_OBJ_TYPE_RX);
	if(MESSAGE7)
	CANMessageSet(CAN0_BASE, 7, &RxObj[6], MSG_OBJ_TYPE_RX);
}

// --------------------------------------------------------------------------------------
//						struct inits:
// --------------------------------------------------------------------------------------
void Init_Structs(){ // this case has no filter, just always uses identical MsgId's for Tx and Rx
	TxObj[0].ui32MsgID = 0x01; 
  TxObj[0].ui32MsgIDMask = 0x00;
  TxObj[0].ui32Flags = MSG_OBJ_TX_INT_ENABLE;  
  TxObj[0].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[0].pui8MsgData = msgDataPtr; 
	
	TxObj[1].ui32MsgID = 0x02; 
  TxObj[1].ui32MsgIDMask = 0x00;
  TxObj[1].ui32Flags = MSG_OBJ_TX_INT_ENABLE; 
  TxObj[1].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[1].pui8MsgData = msgDataPtr;  
	
	TxObj[2].ui32MsgID = 0x03; 
  TxObj[2].ui32MsgIDMask = 0x00;
  TxObj[2].ui32Flags = MSG_OBJ_TX_INT_ENABLE; 
  TxObj[2].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[2].pui8MsgData = msgDataPtr;  
	
	TxObj[3].ui32MsgID = 0x04; 
  TxObj[3].ui32MsgIDMask = 0x00;
  TxObj[3].ui32Flags = MSG_OBJ_TX_INT_ENABLE; 
  TxObj[3].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[3].pui8MsgData = msgDataPtr;  
	
	TxObj[4].ui32MsgID = 0x05; 
  TxObj[4].ui32MsgIDMask = 0x00;
  TxObj[4].ui32Flags = MSG_OBJ_TX_INT_ENABLE; 
  TxObj[4].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[4].pui8MsgData = msgDataPtr;  
	
	TxObj[5].ui32MsgID = 0x06; 
  TxObj[5].ui32MsgIDMask = 0x00;
  TxObj[5].ui32Flags = MSG_OBJ_TX_INT_ENABLE; 
  TxObj[5].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[5].pui8MsgData = msgDataPtr;  
	
	TxObj[6].ui32MsgID = 0x07; 
  TxObj[6].ui32MsgIDMask = 0x00;
  TxObj[6].ui32Flags = MSG_OBJ_TX_INT_ENABLE; 
  TxObj[6].ui32MsgLen = sizeof(msgDataPtr);
  TxObj[6].pui8MsgData = msgDataPtr;  
	
	RxObj[0].ui32MsgID = 0x01; // this receive ID acts as the filter 
  RxObj[0].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[0].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[0].ui32MsgLen = 8;
	RxObj[0].pui8MsgData = RxMsgData[0]; // This pointer needs to be set to buffer for Rx Message data. 
	
  RxObj[1].ui32MsgID = 0x02; // this receive ID acts as the filter 
  RxObj[1].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[1].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[1].ui32MsgLen = 8;
	RxObj[1].pui8MsgData = RxMsgData[1]; // This pointer needs to be set to buffer for Rx Message data. 
	
	RxObj[2].ui32MsgID = 0x03; // this receive ID acts as the filter 
  RxObj[2].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[2].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[2].ui32MsgLen = 8;
	RxObj[2].pui8MsgData = RxMsgData[2]; // This pointer needs to be set to buffer for Rx Message data. 
	
	RxObj[3].ui32MsgID = 0x04; // this receive ID acts as the filter 
  RxObj[3].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[3].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[3].ui32MsgLen = 8;
	RxObj[3].pui8MsgData = RxMsgData[3]; // This pointer needs to be set to buffer for Rx Message data. 
	
	RxObj[4].ui32MsgID = 0x05; // this receive ID acts as the filter 
  RxObj[4].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[4].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[4].ui32MsgLen = 8;
	RxObj[4].pui8MsgData = RxMsgData[4]; // This pointer needs to be set to buffer for Rx Message data. 
	
	RxObj[5].ui32MsgID = 0x06; // this receive ID acts as the filter 
  RxObj[5].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[5].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[5].ui32MsgLen = 8;
	RxObj[5].pui8MsgData = RxMsgData[5]; // This pointer needs to be set to buffer for Rx Message data. 
	
	RxObj[6].ui32MsgID = 0x07; // this receive ID acts as the filter 
  RxObj[6].ui32MsgIDMask = 0x00; // mask to enable filtration bits
  RxObj[6].ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  RxObj[6].ui32MsgLen = 8;
	RxObj[6].pui8MsgData = RxMsgData[6]; // This pointer needs to be set to buffer for Rx Message data. 
}	
	
	void CANmode() {	
	while(1){
		
	uint8_t data[4];
	data[0] = 0;
  data[1] = 0;
  data[2] = CANswitches();
  data[3] = KeypadScan();		
		
	CAN_Transmit(data,6);
	
  for(int ui32Loop1 = 0; ui32Loop1 < 10000000; ui32Loop1++) { }
 			
}	
	}
