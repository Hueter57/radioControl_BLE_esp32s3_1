#include <Motor/MotorDriver/TB6612.hpp>

Motor::MotorDriver::TB6612::TB6612(int pin1, int pin2, int ch1, int ch2) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    pwm_ch1    = ch1;
    pwm_ch2    = ch2;

    pinMode(pin1, OUTPUT);
    pinMode(pin1, OUTPUT);

    ledcSetup(pwm_ch1, 12800, 8);
    ledcAttachPin(this->pin1, pwm_ch1);
    ledcWrite(pwm_ch1, 0);

    ledcSetup(pwm_ch2, 12800, 8);
    ledcAttachPin(this->pin2, pwm_ch2);
    ledcWrite(pwm_ch2, 0);
}

auto Motor::MotorDriver::TB6612::changeSpeed(int value) -> void {
    if (value == 0){
        ledcWrite(pwm_ch1, 0);
        ledcWrite(pwm_ch2, 0);
    }else if(value > 0){
        ledcWrite(pwm_ch1, value);
        ledcWrite(pwm_ch2, 0);
    }else {
        ledcWrite(pwm_ch1, 0);
        ledcWrite(pwm_ch2, -value);
    }
}
