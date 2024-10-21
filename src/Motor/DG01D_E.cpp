#include <Motor/DG01D_E.hpp>

Motor::DG01D_E::DG01D_E(int pin1, int pin2, int pin3, int pin4, int ch1, int ch2) {
    motorDriver = Motor::MotorDriver::TB6612(pin1, pin2, ch1, ch2);
    input_pin1  = pin3;
    input_pin2  = pin4;
    if (input_pin1 == -1) {
        pinMode(input_pin1, INPUT);
        pinMode(input_pin2, INPUT);
    }
}

auto Motor::DG01D_E::changeSpeed(int value) -> void {
    motorDriver.changeSpeed(value);
}