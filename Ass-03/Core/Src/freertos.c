/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LCDTaskHandle;
osThreadId controlTaskHandle;
osThreadId touchTaskHandle;
osThreadId cameraTaskHandle;
osThreadId SDTaskHandle;
osMessageQId stateMachineQueueHandle;
osMessageQId LCDUpdateQueueHandle;
osMutexId LCDAccessHandle;
osMutexId TouchScreenAccessHandle;
osMutexId ConsolAccessHandle;
osMutexId FrameDMAAccessHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartLCDTask(void const * argument);
void StartControlTask(void const * argument);
void StartTouchTask(void const * argument);
void StartCameraTask(void const * argument);
void StartSDTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of LCDAccess */
  osMutexDef(LCDAccess);
  LCDAccessHandle = osMutexCreate(osMutex(LCDAccess));

  /* definition and creation of TouchScreenAccess */
  osMutexDef(TouchScreenAccess);
  TouchScreenAccessHandle = osMutexCreate(osMutex(TouchScreenAccess));

  /* definition and creation of ConsolAccess */
  osMutexDef(ConsolAccess);
  ConsolAccessHandle = osMutexCreate(osMutex(ConsolAccess));

  /* definition and creation of FrameDMAAccess */
  osMutexDef(FrameDMAAccess);
  FrameDMAAccessHandle = osMutexCreate(osMutex(FrameDMAAccess));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of stateMachineQueue */
  osMessageQDef(stateMachineQueue, 16, uint16_t);
  stateMachineQueueHandle = osMessageCreate(osMessageQ(stateMachineQueue), NULL);

  /* definition and creation of LCDUpdateQueue */
  osMessageQDef(LCDUpdateQueue, 16, uint16_t);
  LCDUpdateQueueHandle = osMessageCreate(osMessageQ(LCDUpdateQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LCDTask */
  osThreadDef(LCDTask, StartLCDTask, osPriorityIdle, 0, 128);
  LCDTaskHandle = osThreadCreate(osThread(LCDTask), NULL);

  /* definition and creation of controlTask */
  osThreadDef(controlTask, StartControlTask, osPriorityIdle, 0, 128);
  controlTaskHandle = osThreadCreate(osThread(controlTask), NULL);

  /* definition and creation of touchTask */
  osThreadDef(touchTask, StartTouchTask, osPriorityIdle, 0, 128);
  touchTaskHandle = osThreadCreate(osThread(touchTask), NULL);

  /* definition and creation of cameraTask */
  osThreadDef(cameraTask, StartCameraTask, osPriorityIdle, 0, 128);
  cameraTaskHandle = osThreadCreate(osThread(cameraTask), NULL);

  /* definition and creation of SDTask */
  osThreadDef(SDTask, StartSDTask, osPriorityIdle, 0, 128);
  SDTaskHandle = osThreadCreate(osThread(SDTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartLCDTask */
/**
* @brief Function implementing the LCDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCDTask */
__weak void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLCDTask */
}

/* USER CODE BEGIN Header_StartControlTask */
/**
* @brief Function implementing the controlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlTask */
__weak void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartControlTask */
}

/* USER CODE BEGIN Header_StartTouchTask */
/**
* @brief Function implementing the touchTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTouchTask */
__weak void StartTouchTask(void const * argument)
{
  /* USER CODE BEGIN StartTouchTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTouchTask */
}

/* USER CODE BEGIN Header_StartCameraTask */
/**
* @brief Function implementing the cameraTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCameraTask */
__weak void StartCameraTask(void const * argument)
{
  /* USER CODE BEGIN StartCameraTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartCameraTask */
}

/* USER CODE BEGIN Header_StartSDTask */
/**
* @brief Function implementing the SDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSDTask */
__weak void StartSDTask(void const * argument)
{
  /* USER CODE BEGIN StartSDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
