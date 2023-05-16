/*
 * Ass-03-controlTask.c
 *
 *  Created on: May 16, 2023
 *      Author: TobyD
 */

#include "Ass-03.h"

uint32_t LCD_State = LCD_WELCOME;

void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END StartControlTask */
}
