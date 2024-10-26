#pragma once

#include <Motor/DG01D_E.hpp>
namespace System{

auto changeSpeedMotors(int value, Motor::DG01D_E l_motor,Motor::DG01D_E r_motor) -> void;

}