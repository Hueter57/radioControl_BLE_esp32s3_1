#pragma once

namespace System{
#include <Motor/DG01D_E.hpp>

auto changeSpeedMotors(int value, Motor::DG01D_E l_motor,Motor::DG01D_E r_motor) -> void;

}