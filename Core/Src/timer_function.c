#include "main.h"
#include "stm32g4xx.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_fdcan.h"
#include "can_communication_function.h"
#include "timer_function.h"

volatile float angle;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  
  if (htim == &htim6) {
      angle = raw_angle_data *360.0 / 8192.0;
  }
}