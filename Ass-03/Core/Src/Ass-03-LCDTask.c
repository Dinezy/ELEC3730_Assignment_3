/*
 * Ass-03-LCDTask.c
 *
 *  Created on: May 9, 2023
 *      Author: TobyD
 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLCDTask */
}
