#include <cmath>
#include <cstdint>
#include <iostream>

#include "AdConstants.h"
#include "AdFunctions.h"

namespace Ad
{
namespace Utils
{
float kph_to_mps(const float kph)
{
    return kph / 3.6f;
}
} // namespace Utils

namespace Data
{
Ad::Types::VehicleType init_ego_vehicle()
{
    return Ad::Types::VehicleType{
        .id = Ad::Constants::EGO_VEHICLE_ID,
        .lane = Ad::Types::LaneAssociationType::UnknownLane,
        .speed = 0,
        .distance = 0};
};
} // namespace Data

namespace Visualize
{
void print_vehicle(const Ad::Types::VehicleType &vehicle)
{
    std::cout << "Vehicle: id=" << vehicle.id
              << ", lane=" << static_cast<std::int32_t>(vehicle.lane)
              << ", speed=" << vehicle.speed
              << ", distance=" << vehicle.distance << std::endl;
}
} // namespace Visualize
} // namespace Ad