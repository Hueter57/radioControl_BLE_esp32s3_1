#pragma once

#include <Arduino.h>

namespace assign {

constexpr uint8_t LEFT_MOTOR_PWM_PIN1      = A0;
constexpr uint8_t LEFT_MOTOR_PWM_PIN2      = A1;
constexpr uint8_t LEFT_MOTOR_PWM_CH1       = 0;
constexpr uint8_t LEFT_MOTOR_PWM_CH2       = 1;
constexpr uint8_t LEFT_MOTOR_ENCODER_PIN1  = A4;
constexpr uint8_t LEFT_MOTOR_ENCODER_PIN2  = A5;
constexpr uint8_t RIGHT_MOTOR_PWM_PIN1     = A2;
constexpr uint8_t RIGHT_MOTOR_PWM_PIN2     = A3;
constexpr uint8_t RIGHT_MOTOR_PWM_CH1      = 2;
constexpr uint8_t RIGHT_MOTOR_PWM_CH2      = 3;
constexpr uint8_t RIGHT_MOTOR_ENCODER_PIN1 = A8;
constexpr uint8_t RIGHT_MOTOR_ENCODER_PIN2 = A9;
// constexpr uint8_t LEFT_MOTOR_PWM_PIN1      = 0;

}  // namespace assign