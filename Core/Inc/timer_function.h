#ifndef TIMER_FUNCTION_H
#define TIMER_FUNCTION_H
 
#include "main.h"
#include "stm32g4xx_hal_fdcan.h"
#include <stdint.h>

typedef struct {
    // 位置ループ変数
    float Kp, Ki, Kd;
    float angle_target;
    float angle_total_difference;
    float angle_lowpass_difference;
    float angle_last_time_difference;

    // 速度ループ変数
    float speed_Kp, speed_Ki, speed_Kd;
    float speed_total_difference;
    float speed_lowpass_difference;
    float speed_last_time_difference;
} Motor;

#define MAX_SPEED_RPM 2000.0f

extern Motor motor;
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan3;
extern FDCAN_TxHeaderTypeDef TxHeader;

extern volatile float angle;
extern volatile int speed_target;   // 位置ループの出力
extern volatile int send_current;   // 速度ループの出力
extern float gravity;               // 重力補償
extern int cutoff;                  // ローパスのカットオフ
extern volatile int mode;

/*タイマー関数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
int pid(float current_number, float target_number, float p_gain, float i_gain, float d_gain, float *difference_sum, float *low_pass_difference, float gravity, int cutoff, float *last_time_difference);
 
#endif