#pragma once

#include <Engine/Static/Const.hpp>
#include <cmath>

namespace Misc
{
    inline bool IsNearlyEqual(float a, float b)
    {
        return std::abs(a - b) < Const::SmallValue;
    }
    inline bool IsNearlyZero(float a)
    {
        return Misc::IsNearlyEqual(a, 0.f);
    }
}
