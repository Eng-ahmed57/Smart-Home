/*
 * Motor_Lcfg.h
 *
 * Created: 3/4/2023 1:37:02 AM
 *  Author: ahmed57
 */ 

#include "Motor_cfg.h"

const MOTOR_Port_Config MOTOR_PORT_Config[3] ={
	{PORT_PB3,
	PORT_PIN_LEVEL_LOW,
	PORT_PINDIR_OUTPUT,
	PORT_PIN_IN_ATTATCH_FLOATING},
	
	{PORT_PB5,
	PORT_PIN_LEVEL_LOW,
	PORT_PINDIR_OUTPUT,
	PORT_PIN_IN_ATTATCH_FLOATING},
		
	{PORT_PB6,
	PORT_PIN_LEVEL_LOW,
	PORT_PINDIR_OUTPUT,
	PORT_PIN_IN_ATTATCH_FLOATING}
};
