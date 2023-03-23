/*
 * system_init.c
 *
 *  Created on: Mar 16, 2023
 *      Author: ahmed
 */

/******************************************
  INCLUDES
*******************************************/
#define F_CPU 16000000UL

#include "Port_int.h"
#include "APP_int.h"


/* Port Config Extern */
extern const Port_ConfigType PORT_Config_Arr[];

/* UART Config Extern */
extern const UART_Config_t UART_CONFIG2;

/* External Interrupt Config */
extern EXTI_CONFIG_t EXTI_INT_ArrConfig[EXTI_INT_ArrConfig_Size];

/* Init Function */ 	
ES_t sytem_init(){
	
	/* Initialize all Required Ports and Pins */
		Port_Init(PORT_Config_Arr , 21);

		/* LCD Initialization */
		H_LCD_void_Init();

		/* Global interrupt Initialization */
		M_vEnable_Global_Interrupts();

		/* UART Initialization */
		UART_Init(UART_CONFIG2);

		/* Timer0 Init */
		M_vTIMER0_Init( TIMER0_PWM_PhaseCorrect_MODE,  TIMER0_PWM_PHASECORRECT_NonInverted_MODE);
		
		/* Timer1 Init */
		M_TIMER1_void_Init(Timer_1_Fast_PWM, TIMER_1_NonINV );

		/* External interrupt init */
		M_vEXTI_INT_Enable(EXTI_INT_ArrConfig);
		M_vEXTI_SetCallBack(ECU1_Login_Sucsess_Signal, EXTI_INT0);
}

/* External interrupt Callback funtion */
/* When user login to system this function set Login_Sucsess_Flag to 1 */
void ECU1_Login_Sucsess_Signal()
{
	Login_Sucsess_Flag = 1;
}

/* wait until user login to system then connect to wifi  */
void Check_Login_Sucsess()
{
	/* Make sure that Login_Sucsess_Flag and Logout_Request_Flag reset */
	Login_Sucsess_Flag =0;
	Logout_Request_Flag =1;
	
	H_LCD_void_sendString("Wait User Login");
	/* wait until user login to system */
	while(1)
	{	
		
		if (Login_Sucsess_Flag == 1)
		{
			/* Display welcome Messeage */
			H_LCD_void_Clear_Display();
			_delay_ms(200);
			H_LCD_void_sendString("welcome Home");
			_delay_ms(1000);
			H_LCD_void_Clear_Display();
			
			/* Connect to wifi */
			_delay_ms(200);
			H_LCD_void_gotoXY(0,0);
			_delay_ms(200);
			H_LCD_void_sendString("Connecting ...");
			_delay_ms(200);
			wifi_connect2();
			_delay_ms(200);
			
			/* Show Control Options Menu to user on mobile */
			Request_Menu = 'm';
			Show_Menu_Wifi();
			H_LCD_void_Clear_Display();
			_delay_ms(200);
			break;
		}
	}
}

/* if user request logout from system this function will reset all flags and close wifi connection then return 
   control to Check_Login_Sucsess function to wait for user login again */
void Logout_Request_Handler()
{
	if(Logout_Request_Flag == Logout_Requested)
	{
		Login_Sucsess_Flag = 0;
		H_LCD_void_Clear_Display();
		_delay_ms(200);
		H_LCD_void_sendString(" System Logout Requested... ");
		_delay_ms(3000);
		H_LCD_void_Clear_Display();
		
		/* Close wifi connection */
		UART_sendString("AT+CIPCLOSE=1\r\n");
		H_LCD_void_sendString(" Wifi Closed ... ");
		_delay_ms(3000);
		H_LCD_void_Clear_Display();
		_delay_ms(200);
		
		/* Reset all system flags and control */
		Motor_State_Flag = 0;
		LED_State_Flag =0;
		MOTOR_ON(MOTOR_CW , 0);
		M_TIMER1_void_Stop();
		
		/* Transfere Control to Check login sucsess */
		Check_Login_Sucsess();
		
	}
	
}