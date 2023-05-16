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
#include "touch_panel.h"
#include "Ass-03.h"

char WELCOME[8] = {'W','E','L','C','O','M','E', 0};
char REGISTER[9] = {'R','E','G','I','S','T','E','R',0};
char LOGIN[6] = {'L','O','G','I','N',0};
char key[2] = {0, 0}; // Temporary string for single digit
char save[5] = {'S','A','V','E',0}; // String for "Save" button
char ENTER[9] = {'E','N','T','E','R',' ', 'I','D',0};
char PIN[10] = {'E','N','T','E','R',' ','P','I','N',0};


void drawWelcomeScreen(void);
void drawRegisterScreen(void);
void drawUserScreen(void);
void drawPinScreen(void);

void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
	osMutexWait(LCDAccessHandle, osWaitForever);
	BSP_LCD_Init();
	BSP_LCD_DisplayOn();
	TouchPanel_Calibrate();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font8);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	osMutexRelease(LCDAccessHandle);
	drawWelcomeScreen();
	//drawRegisterScreen();
	//drawPinScreen();

	osSignalSet(touchTaskHandle, LCD_INIT);




  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END StartLCDTask */
}

void drawWelcomeScreen(void){
  // Prepare
  osMutexWait(LCDAccessHandle, osWaitForever);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&Font12);

  // Draw "WELCOME" at the top of the screen
  BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)WELCOME, CENTER_MODE);


  // Draw button 1
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect((SCREENWIDTH / 2) - BUTTONWIDTH - 10, SCREENHEIGHT - BUTTONHEIGHT - 10, BUTTONWIDTH, BUTTONHEIGHT);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAt((SCREENWIDTH / 2) - BUTTONWIDTH - 10 + (BUTTONWIDTH - strlen(REGISTER) * BSP_LCD_GetFont()->Width) / 2,
                          SCREENHEIGHT - BUTTONHEIGHT - 10 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                          (uint8_t *)REGISTER, LEFT_MODE);

  // Draw button 2
  BSP_LCD_SetTextColor(LCD_COLOR_RED);
  BSP_LCD_FillRect((SCREENWIDTH / 2) + 10, SCREENHEIGHT - BUTTONHEIGHT - 10, BUTTONWIDTH, BUTTONHEIGHT);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAt((SCREENWIDTH / 2) + 10 + (BUTTONWIDTH - strlen(LOGIN) * BSP_LCD_GetFont()->Width) / 2,
                          SCREENHEIGHT - BUTTONHEIGHT - 10 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                          (uint8_t *)LOGIN, LEFT_MODE);

  osMutexRelease(LCDAccessHandle);
}

void drawRegisterScreen(void){
    // Prepare
    osMutexWait(LCDAccessHandle, osWaitForever);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&Font12);


//draw pinpad
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int num = j * 3 + i + 1; // Calculate number 1-9
            key[0] = '0' + num; // Convert to character
            BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
            BSP_LCD_FillRect((SCREENWIDTH / 4) * i, (SCREENHEIGHT / 4) * j + BUTTONHEIGHT - 10*j, BUTTONWIDTH, BUTTONHEIGHT);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) * i + (BUTTONWIDTH - strlen(key) * BSP_LCD_GetFont()->Width) / 2,
                                    (SCREENHEIGHT / 4) * j + BUTTONHEIGHT - 10*j + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                                    (uint8_t *)key, LEFT_MODE);
        }
    }

    // Draw 0 button
    key[0] = '0';
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect((SCREENWIDTH / 4), (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30, BUTTONWIDTH, BUTTONHEIGHT);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) + (BUTTONWIDTH - strlen(key) * BSP_LCD_GetFont()->Width) / 2,
                            (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                            (uint8_t *)key, LEFT_MODE);

    // Draw "Save" button
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect((SCREENWIDTH / 4) * 2, (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30, BUTTONWIDTH, BUTTONHEIGHT);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) * 2 + (BUTTONWIDTH - strlen(save) * BSP_LCD_GetFont()->Width) / 2,
                            (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                            (uint8_t *)save, LEFT_MODE);

    osMutexRelease(LCDAccessHandle);
}

void drawUserScreen(){
    // Prepare
    osMutexWait(LCDAccessHandle, osWaitForever);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&Font12);

    // Draw "WELCOME" at the top of the screen
     BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)ENTER, CENTER_MODE);

//draw pinpad
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int num = j * 3 + i + 1; // Calculate number 1-9
            key[0] = '0' + num; // Convert to character
            BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
            BSP_LCD_FillRect((SCREENWIDTH / 4) * i, (SCREENHEIGHT / 4) * j + BUTTONHEIGHT - 10*j, BUTTONWIDTH, BUTTONHEIGHT);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) * i + (BUTTONWIDTH - strlen(key) * BSP_LCD_GetFont()->Width) / 2,
                                    (SCREENHEIGHT / 4) * j + BUTTONHEIGHT - 10*j + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                                    (uint8_t *)key, LEFT_MODE);
        }
    }

    // Draw 0 button
    key[0] = '0';
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect((SCREENWIDTH / 4), (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30, BUTTONWIDTH, BUTTONHEIGHT);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) + (BUTTONWIDTH - strlen(key) * BSP_LCD_GetFont()->Width) / 2,
                            (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                            (uint8_t *)key, LEFT_MODE);

    // Draw "Save" button
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect((SCREENWIDTH / 4) * 2, (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30, BUTTONWIDTH, BUTTONHEIGHT);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) * 2 + (BUTTONWIDTH - strlen(save) * BSP_LCD_GetFont()->Width) / 2,
                            (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                            (uint8_t *)save, LEFT_MODE);

    osMutexRelease(LCDAccessHandle);


}

void drawPinScreen(void){
    // Prepare
    osMutexWait(LCDAccessHandle, osWaitForever);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&Font12);

    // Draw "WELCOME" at the top of the screen
     BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)PIN, CENTER_MODE);

//draw pinpad
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            int num = j * 3 + i + 1; // Calculate number 1-9
            key[0] = '0' + num; // Convert to character
            BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
            BSP_LCD_FillRect((SCREENWIDTH / 4) * i, (SCREENHEIGHT / 4) * j + BUTTONHEIGHT - 10*j, BUTTONWIDTH, BUTTONHEIGHT);
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) * i + (BUTTONWIDTH - strlen(key) * BSP_LCD_GetFont()->Width) / 2,
                                    (SCREENHEIGHT / 4) * j + BUTTONHEIGHT - 10*j + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                                    (uint8_t *)key, LEFT_MODE);
        }
    }

    // Draw 0 button
    key[0] = '0';
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect((SCREENWIDTH / 4), (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30, BUTTONWIDTH, BUTTONHEIGHT);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) + (BUTTONWIDTH - strlen(key) * BSP_LCD_GetFont()->Width) / 2,
                            (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                            (uint8_t *)key, LEFT_MODE);

    // Draw "Save" button
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect((SCREENWIDTH / 4) * 2, (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30, BUTTONWIDTH, BUTTONHEIGHT);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt((SCREENWIDTH / 4) * 2 + (BUTTONWIDTH - strlen(save) * BSP_LCD_GetFont()->Width) / 2,
                            (SCREENHEIGHT / 4) * 3 + BUTTONHEIGHT - 30 + (BUTTONHEIGHT - BSP_LCD_GetFont()->Height) / 2,
                            (uint8_t *)save, LEFT_MODE);

    osMutexRelease(LCDAccessHandle);

}









