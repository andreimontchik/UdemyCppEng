#include <cmath>
#include <cstdint>
#include <iostream>

#include "AdConstants.h"
#include "AdFunctions.h"

namespace Ad
{

using namespace Ad::Types;
using namespace Ad::Constants;

namespace Utils
{
float kph_to_mps(const float kph)
{
    return kph / 3.6f;
}
} // namespace Utils

namespace Data
{

VehicleType init_ego_vehicle()
{
    return VehicleType{EGO_VEHICLE_ID,
                       LaneAssociationType::CENTER,
                       20.0f,
                       10.0f};
}

NeighborVehiclesType init_vehicles()
{
    return NeighborVehiclesType{
        .on_the_left =
            {VehicleType{10, LaneAssociationType::LEFT, 10.0f, 20.0f},
             VehicleType{11, LaneAssociationType::LEFT, 20.0f, -30.0f}},
        .on_the_center =
            {VehicleType{20, LaneAssociationType::CENTER, 20.0f, 40.0f},
             VehicleType{21, LaneAssociationType::CENTER, 30.0f, -40.0f}},
        .on_the_right = {
            VehicleType{30, LaneAssociationType::RIGHT, 30.0f, 50.0f},
            VehicleType{31, LaneAssociationType::RIGHT, 40.0f, -60.0f}}};
}

} // namespace Data

namespace Visualize
{

void print_vehicle(const VehicleType &vehicle)
{
    std::cout << "Vehicle: id=" << vehicle.id
              << ", lane=" << static_cast<std::int32_t>(vehicle.lane)
              << ", speed_mps=" << vehicle.speed_mps
              << ", distance_m=" << vehicle.distance_m << std::endl;
}

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    print_vehicle(vehicles.on_the_left[0]);
    print_vehicle(vehicles.on_the_left[1]);
    print_vehicle(vehicles.on_the_center[0]);
    print_vehicle(vehicles.on_the_center[1]);
    print_vehicle(vehicles.on_the_right[0]);
    print_vehicle(vehicles.on_the_right[1]);
}

void print_vehicle_on_lane(const VehicleType *const vehicle,
                           const float range_m,
                           const float offset_m,
                           std::string &string,
                           std::size_t &idx)
{
    if ((vehicle != nullptr) && (range_m >= vehicle->distance_m) &&
        (vehicle->distance_m > (range_m - offset_m)))
    {
        string[1] = 'V';
        idx++;
    }
    else if ((vehicle != nullptr) &&
             (std::abs(vehicle->distance_m) > VIEW_RANGE_M))
    {
        idx++;
    }
}


void print_scene(const VehicleType &ego_vehicle,
                 const NeighborVehiclesType &vehicles)
{
    std::cout << "    \t   L     C     R  \n";

    auto left_idx = std::size_t{0};
    auto center_idx = std::size_t{0};
    auto right_idx = std::size_t{0};

    const auto offset_m = std::int32_t{20};
    const auto view_range_m = static_cast<std::int32_t>(VIEW_RANGE_M);

    for (auto i = view_range_m; i >= -view_range_m; i -= offset_m)
    {
        const auto range_m = static_cast<float>(i);

        auto left_string = std::string{"   "};
        auto center_string = std::string{"   "};
        auto right_string = std::string{"   "};

        if ((range_m >= ego_vehicle.distance_m) &&
            (ego_vehicle.distance_m > (range_m - offset_m)))
        {
            center_string[1] = 'E';
        }

        if (left_idx < NUM_VEHICLES_ON_LANE)
        {
            print_vehicle_on_lane(&vehicles.on_the_left[left_idx],
                                  range_m,
                                  offset_m,
                                  left_string,
                                  left_idx);
        }
        if (center_idx < NUM_VEHICLES_ON_LANE)
        {
            print_vehicle_on_lane(&vehicles.on_the_center[center_idx],
                                  range_m,
                                  offset_m,
                                  center_string,
                                  center_idx);
        }
        if (right_idx < NUM_VEHICLES_ON_LANE)
        {
            print_vehicle_on_lane(&vehicles.on_the_right[right_idx],
                                  range_m,
                                  offset_m,
                                  right_string,
                                  right_idx);
        }


        std::cout << i << "\t| " << left_string << " | " << center_string
                  << " | " << right_string << " | \n";
    }
}

} // namespace Visualize
} // namespace Ad
