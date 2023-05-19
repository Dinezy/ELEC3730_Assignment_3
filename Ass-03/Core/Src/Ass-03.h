/*
 * Ass-03.h
 *
 *  Created on: May 15, 2023
 *      Author: TobyD
 */

#ifndef SRC_ASS_03_H_
#define SRC_ASS_03_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "ili9325.h"
#include "openx07v_c_lcd.h"
#include "fatfs.h"
#include "dcmi.h"
#include "dcmi_ov7670.h"
#include <stdio.h>
#include <string.h>


//Screen Size stuff
#define BUTTONWIDTH 50
#define BUTTONHEIGHT 30
#define SCREENHEIGHT 240 // replace with your actual screen height
#define SCREENWIDTH 320  // replace with your actual screen width
#define BUFFER_LEN SCREENWIDTH


// RTOS Handles
extern osThreadId defaultTaskHandle;
extern osThreadId LCDTaskHandle;
extern osThreadId controlTaskHandle;
extern osThreadId touchTaskHandle;
extern osThreadId cameraTaskHandle;
extern osThreadId SDTaskHandle;

extern osMutexId LCDAccessHandle;
extern osMutexId TouchScreenAccessHandle;
extern osMutexId ConsolAccessHandle;
extern osMutexId FrameDMAAccessHandle;


extern osMessageQId stateMachineQueueHandle;
extern osMessageQId LCDUpdateQueueHandle;
//LCD States
extern uint32_t LCD_State;

#define LCD_WELCOME 1
#define LCD_REGIS 2
#define LCD_LOG 3

#define LCD_WELC_EVENT 1
#define LCD_REG_EVENT 2
#define LCD_LOGIN_EVENT 3



//Message Queue defines
#define LCD_INIT 0x00000001







#endif /* SRC_ASS_03_H_ */
