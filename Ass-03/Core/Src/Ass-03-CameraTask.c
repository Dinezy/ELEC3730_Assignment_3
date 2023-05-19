/*
 * Ass-03-CameraTask.c
 *
 *  Created on: May 19, 2023
 *      Author: TobyD
 */


#include "Ass-03.h"

OV7670_IDTypeDef OV7670ID;
uint16_t camera_buffer[BUFFER_LEN];
int8_t FrameXferCplt = 0;
int8_t LineXferCplt = 0;
int16_t LineCounter = 0;

void LCD_Small_Print(void);

void StartCameraTask(void const * argument)
{
  /* USER CODE BEGIN StartCameraTask */
	// Wait for LCD Init
	  if(DCMI_OV7670_ReadID(&OV7670ID) != 0){
		osMutexWait(ConsolAccessHandle, osWaitForever);
		printf("Read ID error\r\n");
	  }
	  if(DCMI_OV7670_Init()==0){
		osMutexWait(ConsolAccessHandle, osWaitForever);
		printf("OV7670 OK\r\n");
	  }else{
		osMutexWait(ConsolAccessHandle, osWaitForever);
		printf("failed\r\n");
	  }

	  osMutexRelease(ConsolAccessHandle);

	  osSignalWait(LCD_INIT,osWaitForever);

	  /* Converts uint16_t camera_buffer to uint32_t, so the actual length is BUFFER_LEN / 2 */
	  osMutexWait(FrameDMAAccessHandle,0);
	  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)camera_buffer, BUFFER_LEN / 2);


  /* Infinite loop */
  for(;;)
  {
	  if(LineXferCplt){
		  if(osMutexWait(LCDAccessHandle, 0) == osOK){
			  	  LCD_Small_Print();
			  	  osMutexRelease(LCDAccessHandle);
	  			   }

	  			   if((LineCounter >= SCREENHEIGHT) && FrameXferCplt)
	  			   {
	  					 // Allow an SD trigger event to proceed
	  					 osMutexRelease(FrameDMAAccessHandle);
	  					 osThreadYield();
	  					 osMutexWait(FrameDMAAccessHandle,osWaitForever);

	  					 // For every Frame
	  					 FrameXferCplt = 0;
	  					 LineCounter = 0;
	  			   }

	  			  /* Converts uint16_t camera_buffer to uint32_t, so the actual length is BUFFER_LEN / 2 */
	  			  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)camera_buffer, BUFFER_LEN / 2);

	  			  LineXferCplt = 0;
	  			 }

	  		  	 osThreadYield();
	  	}
}

  void LCD_Small_Print(void)
  {
  	// For every Line
  	ili9325_SetDisplayWindow(SCREENWIDTH-SCREENHEIGHT/2-1, 1, SCREENHEIGHT/2, SCREENWIDTH/2);
  	ili9325_WriteReg(LCD_REG_3, 0x1020); //change write-LCD direction

  	ili9325_SetCursor (SCREENWIDTH-SCREENHEIGHT/2-1+LineCounter, 1);
  	LCD_IO_WriteReg (LCD_REG_34);
  	LCD_IO_WriteMultipleData ((uint8_t *) camera_buffer, SCREENWIDTH/2*2);

  	ili9325_SetDisplayWindow(0, 0, SCREENWIDTH, SCREENHEIGHT);
  	ili9325_WriteReg(LCD_REG_3, 0x1028); //Restore write-LCD direction
  }

  /**
    * @brief  Frame Event callback.
    * @param  None
    * @retval None
    */
  void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
  {
    /* the first frame will be abnormal, discarded */
    FrameXferCplt = 1;
  }

  /**
    * @brief  Line Event callback.
    * @param  None
    * @retval None
    */
  void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
  {
    LineXferCplt = 1;
    LineCounter++;
  }


