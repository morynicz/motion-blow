#include "messages/Measurement.hpp"
#include "protos/Measurement.pb.h"
#include <ostream>

namespace messages
{
Measurement Measurement::deserialize(const std::string &serialized)
{
    protos::Measurement proto;
    proto.ParseFromString(serialized);
    const auto pose = proto.pose();
    const auto accel = proto.accelerations();
    return {proto.timestamp(),
            {pose.x(), pose.y(), pose.z(), pose.s()},
            {accel.x(), accel.y(), accel.z(), accel.a(), accel.b(), accel.c()}};
}

auto makeProtoAccelerations(const messages::Measurement::Accelerations &accel)
{
    protos::Accelerations accelerations;
    accelerations.set_x(accel.x);
    accelerations.set_y(accel.y);
    accelerations.set_z(accel.z);
    accelerations.set_a(accel.a);
    accelerations.set_b(accel.b);
    accelerations.set_c(accel.c);
    return accelerations;
}

auto makeProtoPose(const messages::Measurement::Pose &p)
{
    protos::Pose pose;
    pose.set_x(p.x);
    pose.set_y(p.y);
    pose.set_z(p.z);
    pose.set_s(p.s);
    return pose;
}

std::string Measurement::serialize() const
{
    protos::Measurement proto;

    proto.set_timestamp(timestamp);
    *proto.mutable_accelerations() = makeProtoAccelerations(accelerations);
    *proto.mutable_pose() = makeProtoPose(pose);

    std::string serialized;
    proto.SerializeToString(&serialized);
    return serialized;
}

std::ostream &operator<<(std::ostream &os, const Measurement::Pose &in)
{
    return os << "x: " << in.x << " y: " << in.y << " z: " << in.z
              << " s: " << in.s;
}
std::ostream &operator<<(std::ostream &os, const Measurement::Accelerations &in)
{
    return os << "x: " << in.x << " y: " << in.y << " z: " << in.z
              << " a: " << in.a << " b: " << in.b << " c: " << in.c;
}

std::ostream &operator<<(std::ostream &os, const Measurement &in)
{
    return os << "ts: " << in.timestamp << ", pose: {" << in.pose
              << " },  accel: {" << in.accelerations << " }";
}
} // namespace messages