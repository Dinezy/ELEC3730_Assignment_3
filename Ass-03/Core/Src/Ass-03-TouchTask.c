/*
 * Ass-03-TouchTask.c
 *
 *  Created on: 16 May 2023
 *      Author: TobyD
 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "touch_panel.h"
#include "Ass-03.h"



void welcomeState_Touch(void);
void registerState_Touch(void);
void loginState_Touch(void);



void StartTouchTask(void const * argument)
{
  /* USER CODE BEGIN StartTouchTask */
	osSignalWait(LCD_INIT, osWaitForever);
  /* Infinite loop */
  for(;;)
  {
    getDisplayPoint(&display, Read_Ads7846(), &matrix);

    //Touch State Machine
    switch(LCD_State){
    case LCD_WELCOME:
    	welcomeState_Touch();
    	break;
    case LCD_REGIS:
    	registerState_Touch();
    	break;

    case LCD_LOG:
    	loginState_Touch();
    	break;
    }

	osDelay(100);
  }
  /* USER CODE END StartTouchTask */
}

void welcomeState_Touch(void){

	osMutexWait(TouchScreenAccessHandle, osWaitForever);

	//Register Button
	if(display.x >= (SCREENWIDTH / 2) - BUTTONWIDTH - 10 && display.x <= (SCREENWIDTH / 2) - 10 &&
	       display.y >= SCREENHEIGHT - BUTTONHEIGHT - 10 && display.y <= SCREENHEIGHT - 10) {
	      // Handle button 1 press
	      //handleButton1Press();
	      printf("but1\n");
	}
	//Login Button
	if(display.x >= (SCREENWIDTH / 2) + 10 && display.x <= (SCREENWIDTH / 2) + BUTTONWIDTH + 10 &&
	            display.y >= SCREENHEIGHT - BUTTONHEIGHT - 10 && display.y <= SCREENHEIGHT - 10) {
	      // Handle button 2 press
	      //handleButton2Press();
	      printf("but2\n");
	    }

	osMutexRelease(TouchScreenAccessHandle);



}

void registerState_Touch(void){

}

void loginState_Touch(void){



}





