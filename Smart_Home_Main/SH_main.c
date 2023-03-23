/*
 * SH_main.c
 *
 *  Created on:
 *      Author:
 */

/*****************************************************************/
/* FILE DESCRIPTION:
----------------------------------------------------------------
*  file    : SH_main.c
*  brief   : main function
*****************************************************************

/******************************************
  INCLUDES
*******************************************/
#define F_CPU 16000000UL
#include "APP_int.h"


void main(){
	
	/* Initialize All System modules */
	sytem_init();
	_delay_ms(200);
	/* Wait for user to login to connect wifi and start system */
	Check_Login_Sucsess();
			
	while(1)
	{

		/* Wait for ECU1 Login Success Signal to start Application */
		while(Login_Sucsess_Flag == 1)
		{
			/* Check User Input From Wifi */
			Read_Wifi();
			/*read LM35 and LDR values*/
			getTempAndIntens();
			/* Update fan speed based on User input */
			Adjust_FanSpeed();
			/* Update LED_intens based on User input */
			Adjust_LEDIntensety();
			
			/* Show Room temperature on mobile phone upon user request */
			Show_Temperture_Wifi();
			
			/* Led Auto control upon user request */
			Led_Control();
			
			/* Auto Fan control Based on user request */
			Motor_Control();
			
			Show_Menu_Wifi();
			
			/* Check if Logout requested, Reset the system and wait for Login again */
			Logout_Request_Handler();

			_delay_ms(150);	
			
		}
	}
}

