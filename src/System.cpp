#include <System.hpp>

auto System::changeSpeedMotors(int value, Motor::DG01D_E l_motor, Motor::DG01D_E r_motor) -> void {
    switch (value) {
    case 0:
        l_motor.changeSpeed(0);
        r_motor.changeSpeed(0);
        break;
    case 1:
        l_motor.changeSpeed(200);
        r_motor.changeSpeed(200);
        break;
    case 2:
        l_motor.changeSpeed(-200);
        r_motor.changeSpeed(-200);
        break;
    case 3:
        l_motor.changeSpeed(200);
        r_motor.changeSpeed(-200);
        break;
    case 4:
        l_motor.changeSpeed(-200);
        r_motor.changeSpeed(200);
        break;

    default:
        l_motor.changeSpeed(0);
        r_motor.changeSpeed(0);
        break;
    }
}