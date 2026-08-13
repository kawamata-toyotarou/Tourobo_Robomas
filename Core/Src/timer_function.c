#include "main.h"
#include "stm32g4xx.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_fdcan.h"
#include "can_communication_function.h"
#include "timer_function.h"

Motor motor; 

volatile float angle;
volatile int speed_target;
volatile int send_current;
float gravity = 0.0f;
int cutoff = 6;

int pid(float current_number, float target_number, float p_gain, float i_gain, float d_gain,
        float *difference_sum, float *low_pass_difference, float gravity, int cutoff,
        float *last_time_difference) {

    float difference = target_number - current_number;
    int send_number;

    *difference_sum += difference * 0.001f;   
    if (*difference_sum > 10000) *difference_sum = 10000;
    if (*difference_sum < -10000) *difference_sum = -10000;

    float derivative = (difference - *last_time_difference);
    *low_pass_difference += (derivative - *low_pass_difference) / cutoff;
    if (*low_pass_difference > 5000) *low_pass_difference = 5000;
    if (*low_pass_difference < -5000) *low_pass_difference = -5000;

    send_number = (int)(p_gain * difference + i_gain * (*difference_sum) + d_gain * (*low_pass_difference) + gravity); //モーターに力がかかるので工夫してもいいかも
    *last_time_difference = difference;

    if (send_number > 16384) {
        send_number = 16384;
    } else if (send_number < -16384) {
        send_number = -16384;
    }

    return send_number;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

  if (htim == &htim6) {
      angle = raw_angle_data * 360.0 / 8192.0;

      speed_target = pid(rotate_total_angle, motor.angle_target,
                          motor.Kp, motor.Ki, motor.Kd,
                          &motor.angle_total_difference, &motor.angle_lowpass_difference,
                          gravity, cutoff, &motor.angle_last_time_difference);

      if (speed_target > MAX_SPEED_RPM) {
        speed_target = MAX_SPEED_RPM;
      } else if (speed_target < -MAX_SPEED_RPM) {
        speed_target = -MAX_SPEED_RPM;
      }

      send_current = pid(robomasu_speed_rpm, (float)speed_target,
                          motor.speed_Kp, motor.speed_Ki, motor.speed_Kd,
                          &motor.speed_total_difference, &motor.speed_lowpass_difference,
                          0, cutoff, &motor.speed_last_time_difference);
  }
}



