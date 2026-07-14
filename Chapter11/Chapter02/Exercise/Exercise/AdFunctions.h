#pragma once

#include "AdTypes.h"

namespace Ad
{
namespace Utils
{
float kph_to_mps(const float kph);
}

namespace Data
{
Ad::Types::VehicleType init_ego_vehicle();
}

namespace Visualize
{
void print_vehicle(const Ad::Types::VehicleType &vehicle);
}
} // namespace Ad