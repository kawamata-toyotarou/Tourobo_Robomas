#include "main.h"
#include "stm32g4xx.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_fdcan.h"
#include "can_communication_function.h"

volatile int16_t robomasu_speed_rpm;
volatile float raw_angle_data;
volatile float last_time_raw_angle_data;
volatile float rotate_total_angle;
volatile float last_time_rotate_total_angle;

void update_total_angle(void) {

    int16_t angle_diference = (int16_t)raw_angle_data - (int16_t)last_time_raw_angle_data;
    if (angle_diference > 4096) {
        angle_diference -= 8192;
    }
    if (angle_diference < -4096) {
        angle_diference += 8192;
    }

    rotate_total_angle += angle_diference;
    last_time_raw_angle_data = raw_angle_data; 
}

/*受信コールバック関数*/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {

  if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {

    FDCAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];

    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
      Error_Handler();
    }

    if (RxHeader.Identifier == 0x202) {
      raw_angle_data = (uint16_t)((RxData[0] << 8) | RxData[1]);
      robomasu_speed_rpm = (int16_t)((RxData[2] << 8) | RxData[3]);
      update_total_angle(); 
    }

  }
}