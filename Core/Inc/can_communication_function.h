#ifndef CAN_COMMUNICATION_FUNCTION_H
#define CAN_COMMUNICATION_FUNCTION_H
 
#include "main.h"
#include "stm32g4xx_hal_fdcan.h"
 
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan3;
extern FDCAN_TxHeaderTypeDef TxHeader;
extern FDCAN_RxHeaderTypeDef RxHeader;

/*受信コールバック関数*/
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs);
 
#endif /* CAN_COMMUNICATION_FUNCTION_H */