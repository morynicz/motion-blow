#pragma once
#include "Eigen/Dense"
#include "aquisition/Device.hpp"
#include <cctype>
#include <vector>

struct SomeName
{
    uint64_t timestamp;
    std::vector<Eigen::Vector3d> points;
};

bool operator==(const SomeName &lhs, const SomeName &rhs);

std::vector<SomeName> integrate(const std::vector<Device::Measurement> &,
                                const std::vector<Eigen::Vector3d> &);
