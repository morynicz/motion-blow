#include "gmock/gmock.h"
#include "messages/Measurement.hpp"
#include "gtest/gtest.h"

using testing::AllOf;
using testing::Field;

namespace messages
{
// Dummy test prepared for when I know how do I want to serialize this
TEST(MeasurementTests, testSerializationAndDeserialization)
{
    messages::Measurement measurement{1u, 2, 3, 4, 5, 6, 7, 8};

    auto serialized = measurement.serialize();
    auto deserialized = Measurement::deserialize(serialized);

    messages::Measurement expectedMeasurement{measurement};
    EXPECT_THAT(
        deserialized,
        AllOf(Field("timestamp", &Measurement::timestamp,
                    expectedMeasurement.timestamp),
              Field("pose", &Measurement::pose,
                    AllOf(Field("qx", &Measurement::Pose::x,
                                expectedMeasurement.pose.x),
                          Field("qy", &Measurement::Pose::y,
                                expectedMeasurement.pose.y),
                          Field("qz", &Measurement::Pose::z,
                                expectedMeasurement.pose.z),
                          Field("qs", &Measurement::Pose::s,
                                expectedMeasurement.pose.s)

                              )),
              Field("accelerations", &Measurement::accelerations,
                    AllOf(Field("x", &Measurement::Accelerations::x,
                                expectedMeasurement.accelerations.x),
                          Field("y", &Measurement::Accelerations::y,
                                expectedMeasurement.accelerations.y),
                          Field("z", &Measurement::Accelerations::z,
                                expectedMeasurement.accelerations.z),
                          Field("z", &Measurement::Accelerations::a,
                                expectedMeasurement.accelerations.a),
                          Field("z", &Measurement::Accelerations::b,
                                expectedMeasurement.accelerations.b),
                          Field("z", &Measurement::Accelerations::c,
                                expectedMeasurement.accelerations.c)))));
}
} // namespace messages