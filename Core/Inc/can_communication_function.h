#ifndef CAN_COMMUNICATION_FUNCTION_H
#define CAN_COMMUNICATION_FUNCTION_H
 
#include "main.h"
#include "stm32g4xx_hal_fdcan.h"
#include <stdint.h>
 
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan3;
extern volatile int16_t robomasu_speed_rpm;
extern volatile float raw_angle_data;
extern volatile float last_time_raw_angle_data;
extern volatile float rotate_total_angle;
extern volatile float last_time_rotate_total_angle;

void update_total_angle(void);
/*受信コールバック関数*/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
 
#endif /* CAN_COMMUNICATION_FUNCTION_H */