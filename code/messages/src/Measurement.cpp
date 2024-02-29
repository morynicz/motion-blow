#include "messages/Measurement.hpp"
#include "protos/Measurement.pb.h"

namespace messages
{
Measurement Measurement::deserialize(const std::string& serialized)
{
    protos::Measurement proto;
    proto.ParseFromString(serialized);
    return {
        proto.timestamp(),
        proto.qx(),
        proto.qy(),
        proto.qz(),
        proto.qs(),
        proto.x(),
        proto.y(),
        proto.z()
    };
}

std::string Measurement::serialize() const
{
    protos::Measurement proto;
    proto.set_timestamp(timestamp);
    proto.set_qx(qx);
    proto.set_qy(qy);
    proto.set_qz(qz);
    proto.set_qs(qs);
    proto.set_x(x);
    proto.set_y(y);
    proto.set_z(z);
    std::string serialized;
    proto.SerializeToString(&serialized);
    return serialized;
}
}