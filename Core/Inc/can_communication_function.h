#ifndef CAN_COMMUNICATION_FUNCTION_H
#define CAN_COMMUNICATION_FUNCTION_H
 
#include "main.h"
#include "stm32g4xx_hal_fdcan.h"
#include <stdint.h>
 
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan3;
extern volatile int16_t robomasu_speed_rpm;

/*受信コールバック関数*/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
 
#endif /* CAN_COMMUNICATION_FUNCTION_H */