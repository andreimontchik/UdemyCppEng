#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

using ClockType = std::chrono::steady_clock;
using ClockRes = std::chrono::microseconds;

namespace
{
constexpr auto NUM_ELEMENTS = size_t{1'000'000U};
};

std::int32_t gen()
{
    static auto seed = std::random_device{};
    static auto g = std::mt19937{seed()};
    static auto d = std::uniform_int_distribution<std::int32_t>{-10, 10};

    return d(g);
}

template <typename T>
void print_vector(const std::vector<T> &vec)
{
    for (const auto val : vec)
    {
        std::cout << val << '\n';
    }
    std::cout << '\n';
}

int main()
{
    auto my_vector = std::vector<std::int32_t>(NUM_ELEMENTS, 0U);
    const auto start_time = ClockType::now();

    std::generate(my_vector.begin(), my_vector.end(), gen);
    // print_vector(my_vector);
    std::cout << "Starting..." << std::endl;
    const auto elapsed_time =
        std::chrono::duration_cast<ClockRes>(ClockType::now() - start_time)
            .count();
    std::cout << "Completed. Time elapsed: " << elapsed_time << " us\n";
    return 0;
}
