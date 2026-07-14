#pragma once

#include <cstdint>

#include "AdConstants.h"

namespace Ad::Types
{
enum class LaneAssociationType
{
    UnknownLane,
    LeftLane,
    CenterLane,
    RightLane
};

struct VehicleType
{
    std::int32_t id;
    LaneAssociationType lane;
    uint32_t speed;
    uint32_t distance;
};
} // namespace Ad::Types
