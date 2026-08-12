#ifndef TIMER_FUNCTION_H
#define TIMER_FUNCTION_H
 
#include "main.h"
#include "stm32g4xx_hal_fdcan.h"
#include <stdint.h>
 
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan3;
extern volatile float angle;

/*タイマー関数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
 
#endif