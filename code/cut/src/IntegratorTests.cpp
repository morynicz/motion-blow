#include "Eigen/Dense"
#include "cut/Integrator.hpp"
#include "gmock/gmock.h"
#include "aquisition/Device.hpp"
#include "gtest/gtest.h"

TEST(TrajectoryIntegratorTests,
     givenNoRotationAndNoAccelerationPointShouldRemainInTheSamePlace)
{
    Device::Measurement start{0, {0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
    Device::Measurement second{1, {0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};

    std::vector<Device::Measurement> measurements{start, second};
    std::vector<Eigen::Vector3d> points{
        {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    std::vector<SomeName> expectedTrajectories{
        {0, {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}}},
        {0, {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};

    EXPECT_THAT(integrate(measurements, points),
                testing::ElementsAreArray(expectedTrajectories));
}