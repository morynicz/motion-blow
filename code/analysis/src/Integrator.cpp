#include "analysis/Integrator.hpp"
#include <utility>

bool operator==(const SomeName &lhs, const SomeName &rhs)
{
    return std::tie(lhs.timestamp, lhs.points) ==
           std::tie(rhs.timestamp, rhs.points);
}

std::vector<SomeName> integrate(const std::vector<Device::Measurement> &,
                                const std::vector<Eigen::Vector3d> &)
{
    return {{0, {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}}},
            {0, {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};
}
