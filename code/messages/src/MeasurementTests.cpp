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
    EXPECT_THAT(deserialized,
                AllOf(Field("timestamp", &Measurement::timestamp,
                            expectedMeasurement.timestamp),
                      Field("qx", &Measurement::qx, expectedMeasurement.qx),
                      Field("qy", &Measurement::qy, expectedMeasurement.qy),
                      Field("qz", &Measurement::qz, expectedMeasurement.qz),
                      Field("qs", &Measurement::qs, expectedMeasurement.qs),
                      Field("x", &Measurement::x, expectedMeasurement.x),
                      Field("y", &Measurement::y, expectedMeasurement.y),
                      Field("z", &Measurement::z, expectedMeasurement.z)));
}
} // namespace messages