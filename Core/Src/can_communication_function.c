#include "main.h"
#include "stm32g4xx.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_fdcan.h"
#include "can_communication_function.h"


/*受信コールバック関数*/
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs) {

  if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET) {

    uint8_t RxData[12];

    if (HAL_FDCAN_GetRxMessage(&hfdcan3, FDCAN_RX_FIFO1, &RxHeader, RxData) != HAL_OK) {
      Error_Handler();
    }

  }
}