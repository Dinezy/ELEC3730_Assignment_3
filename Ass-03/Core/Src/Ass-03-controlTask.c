/*
 * Ass-03-controlTask.c
 *
 *  Created on: May 16, 2023
 *      Author: TobyD
 */

#include "Ass-03.h"

uint32_t LCD_State = LCD_WELCOME;
uint32_t EVENT;

void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {

	 EVENT = osMessageGet(stateMachineQueueHandle,0).value.v;

	 //STATE MACHINE
	 switch(EVENT){
	 case LCD_WELC_EVENT:
		 LCD_State = LCD_WELCOME;
		 osMessagePut(LCDUpdateQueueHandle,LCD_WELC_EVENT,0);
		 break;
	 case LCD_REG_EVENT:
		 LCD_State = LCD_REGIS;
		 break;
	 case LCD_LOGIN_EVENT:
		 LCD_State = LCD_LOG;
		 break;
	 }

    osDelay(100);
  }
  /* USER CODE END StartControlTask */
}
