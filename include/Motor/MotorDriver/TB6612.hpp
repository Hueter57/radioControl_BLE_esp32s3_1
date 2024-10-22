#pragma once

namespace Motor::MotorDriver {
#include <Arduino.h>

class TB6612 {
  private:
    int pin1;
    int pin2;
    int pwm_ch1;
    int pwm_ch2;

  public:
    TB6612();
    TB6612(int pin1, int pin2, int ch1, int ch2);

    auto changeSpeed(int value) -> void;
};
}  // namespace MotorDriver