/*
 * wifi_prg.c
 *
 * Created: 3/11/2023 2:40:48 PM
 *  Author: ahmed57
 */ 

//#include "Mcu_HW.h"
#include "UART_int.h"
#include "wifi_int.h"
#include "UART_priv.h"
#include "LCD_int.h"
#include  <string.h>
#define F_CPU 16000000UL
#include <util/delay.h>
/***********************************************************************/
/* Wifi initialization function to connect to wifi and TCP server */
/***********************************************************************/
/*
void wifi_connect()
{
	//Set callback function to receive wifi responses 
	UART_Set_CallBack(Wifi_Response_Reciver_UART_CallBack);
	
	//Stop echo and check for OK 
	UART_sendString("ATE0\r\n");
	_delay_ms(1000);
	Check_Wifi_Respones("OK", "AT_ERROR");
	_delay_ms(1000);
	H_LCD_void_Clear_Display();
	_delay_ms(200);
	Wifi_Buffer_Reset();
	//H_LCD_void_sendData('2');
	H_LCD_void_sendString("Connecting 1...");
	_delay_ms(1000);
	
	//Set wifi mode to station and server
	UART_sendString("AT+CWMODE=3\r\n");
	_delay_ms(1000);
	Check_Wifi_Respones("OK", "AT+CWMODE_ERROR");
	_delay_ms(1000);
	H_LCD_void_Clear_Display();
	_delay_ms(200);
	Wifi_Buffer_Reset();
	//H_LCD_void_sendData('3');
	H_LCD_void_sendString("Connecting 2...");

	_delay_ms(1000);
	
	//"Fiber\",\"P@ssw0rd@MCIT\
	// "ahmed57\",\"asd52479955\
	// Connect to wifi
	
	UART_sendString("AT+CWJAP=\"NTI\",\"12345678\"\r\n");
	_delay_ms(3000);
	//Check_Wifi_Respones("WIFI DISCONNECT", "Connect_ERROR");
	//_delay_ms(3000);
	//Check_Wifi_Respones("WIFI CONNECTED", "Connect_ERROR");
	_delay_ms(3000);
	Check_Wifi_Respones("OK", "AT+CWMODE_ERROR");
	//H_LCD_void_sendString("OK");
	_delay_ms(2000);
	H_LCD_void_Clear_Display();
	_delay_ms(200);
	Wifi_Buffer_Reset();
	//H_LCD_void_sendData('4');
	H_LCD_void_sendString("Connecting 3...");

	_delay_ms(1000);
	
	// connect to TCP Server 
	UART_sendString("AT+CIPSTART=\"TCP\",\"192.168.137.81\",9999\r\n");
	_delay_ms(3000);
	Check_Wifi_Respones("OK", "AT+CIPSERVER_ERROR");
	_delay_ms(3000);
	H_LCD_void_Clear_Display();
	_delay_ms(200);
	Wifi_Buffer_Reset();
	//H_LCD_void_sendData('5');
	H_LCD_void_sendString("Connecting4...");

	_delay_ms(1000);
	H_LCD_void_sendString("Connected");
	_delay_ms(1000);

}
*/
/***************************************************************/
void wifi_connect2()
{
	/* Set callback function to recive wifi responses */
	UART_Set_CallBack(Wifi_Response_Reciver_UART_CallBack);
	
	/* Stop echo and check for OK */
	UART_sendString("ATE0\r\n");
	_delay_ms(200);
	Wifi_Wait_Respones("OK", "AT_ERROR", "Wifi Response1:");
	Wifi_Buffer_Reset();
	
	/* Set wifi mode to station and server */
	UART_sendString("AT+CWMODE=3\r\n");
	_delay_ms(200);
	Wifi_Wait_Respones("OK", "AT+CWMODE_ERROR" ,"Wifi Response2:");
	Wifi_Buffer_Reset();

	//"Fiber\",\"P@ssw0rd@MCIT\
	// "ahmed57\",\"asd52479955\
	/* Connect to wifi */
	UART_sendString("AT+CWJAP=\"NTI\",\"12345678\"\r\n");
	_delay_ms(200);
	Wifi_Wait_Respones("OK", "AT+CWJAP_ERROR", "Wifi Response3:");
	Wifi_Buffer_Reset();
	
	/* Connect to TCP Server */
	UART_sendString("AT+CIPSTART=\"TCP\",\"192.168.137.131\",9999\r\n");
	_delay_ms(200);
	Wifi_Wait_Respones("OK", "AT+CIPSTART_ERROR", "Wifi Response4:");
	Wifi_Buffer_Reset();
 
	H_LCD_void_gotoXY(0,0);
	_delay_ms(10);
	H_LCD_void_Clear_Display();
	_delay_ms(10);
	H_LCD_void_sendString("Connected");
	_delay_ms(2000);

}

/***********************************************************************/
/* Function to check wifi response without blocking nor time out */
/* only used for instantly checking */
/***********************************************************************/
/*
void Check_Wifi_Respones(u8 *Wifi_Response , u8 *Error_Message)
{
	u8 index =NULL;
	
	if((index = strstr(Rx_Buffer_UART, Wifi_Response)) != NULL)
	{
		//H_LCD_void_Clear_Display();
		_delay_ms(10);
		H_LCD_void_gotoXY(3,0);
		H_LCD_void_sendString("Wifi Response:");
		_delay_ms(10);
		H_LCD_void_sendString(Wifi_Response);
		_delay_ms(10);
		Wifi_Buffer_Reset();

	}
	else
	{
		//H_LCD_void_Clear_Display();
		_delay_ms(10);
		H_LCD_void_gotoXY(3,0);
		_delay_ms(10);
		H_LCD_void_sendString("Wifi Response:");
		_delay_ms(10);
		H_LCD_void_sendString(Rx_Buffer_UART);
		_delay_ms(10);
		Wifi_Buffer_Reset();

	

	}
}
*/

/*************************************************/
/* Function to check wifi response (blocking)  */
/*************************************************/
void Wifi_Wait_Respones(u8 *Wifi_Response ,  u8 *Error_Message , u8* Messeage)
{
	/* set this response to 0 when you got response */
	u8 Response_Found =1;
	u8 Max_check_time = 0;
	

	_delay_ms(10);
	H_LCD_void_gotoXY(3,0);
	_delay_ms(10);
	H_LCD_void_sendString(Messeage);
	
	while(Response_Found && Max_check_time <= 30)
	{
		H_LCD_void_gotoXY(3,15);
		H_LCD_void_sendString("  ");
		if(strstr(Rx_Buffer_UART, Wifi_Response) != NULL)
		{
	
			_delay_ms(10);
			H_LCD_void_gotoXY(3,15);
			_delay_ms(10);
			H_LCD_void_sendString(Wifi_Response);
			Response_Found = 0;		
		}
		else
		{
			Max_check_time++;
		}
		_delay_ms(200);
	}
	
	if(Response_Found)
	{
		H_LCD_void_gotoXY(3,0);
		H_LCD_void_sendString("No valid response");
	}
}

/*************************************************/
/* Function to Recive data from wifi and check for the required data  */
/*************************************************/
u8 Wifi_Wait_Data(u8 Wifi_Data)
{
	/* set this response to 0 when you got response */
	u8 Data_Found =1;
	u16 timeout = 5;
	/* Return state = 1 when data found  */
	u8 Return_State = 0;
	
	while(Data_Found && timeout )
	{
		
		if(strchr(Rx_Buffer_UART, Wifi_Data) != NULL)
		{

			Data_Found = 0;
			Return_State = 1;
		}
		else
		{

			timeout--;
		}

	}
	return Return_State;
}

/*************************************************/
/* Function to Send Data to server  */
/*************************************************/

void Wifi_Send_Data2(u8 *Data)
{
	u16 Len = strlen(Data);
	 char buffer[20];
	 
	sprintf(buffer, "AT+CIPSEND=%d\r\n",Len);
	
	UART_sendString(buffer);
	
	_delay_ms(50);
	//Wifi_Wait_Respones("OK" ,"ERRORSS", "\0");
	UART_sendString(Data);
}

/*************************************************/
/* Function to Reset Wifi Buffer  */
/*************************************************/
void Wifi_Buffer_Reset()
{
	
	/* fill the buffer with 5 to reset */
	for(int j =0; j <UART_BUFFER_SIZE + 1; j++)
	{
		Rx_Buffer_UART[j] = '9';
	}
	
	RX_Wr_Index_UART = 0;
	RX_Rd_Index_UART = 0;
	RX_Counter_UART = 0;
}

/****************************************************************************/
/* wifi callback funtion to be passed to UART ISR to recive wifi responses */
/* then store it in a buffer */
/****************************************************************************/
void Wifi_Response_Reciver_UART_CallBack()
{
	
	u8 rx_byte;
	rx_byte = UART_UDR_REG;	
	Rx_Buffer_UART[RX_Wr_Index_UART] = rx_byte;  // put received byte in buffer
	if (++RX_Wr_Index_UART > UART_BUFFER_SIZE)
	RX_Wr_Index_UART = 0;
	if (++RX_Counter_UART > UART_BUFFER_SIZE) // keep a character count
	{
		RX_Counter_UART = UART_BUFFER_SIZE;  //;  if too many chars came

	}
	
}
