#include "main.h"
#include "stm32g4xx.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_fdcan.h"
#include "can_communication_function.h"

volatile int16_t robomasu_speed_rpm = 0;

/*受信コールバック関数*/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {

  if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {

    FDCAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];

    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
      Error_Handler();
    }

    if (RxHeader.Identifier == 0x201) {
      robomasu_speed_rpm = (int16_t)((RxData[2] << 8) | RxData[3]);
    }

  }
}