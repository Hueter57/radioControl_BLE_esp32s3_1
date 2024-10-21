#pragma once

namespace Motor {
#include <Arduino.h>
#include <Motor/MotorDriver/TB6612.hpp>

class DG01D_E {
  private:
    Motor::MotorDriver::TB6612 motorDriver;
    int                        input_pin1;
    int                        input_pin2;

  public:
    DG01D_E(int pin1, int pin2, int pin3, int pin4, int ch1, int ch2);
    auto changeSpeed(int value) -> void;
};
}  // namespace Motor