#include "messages/Measurement.hpp"
#include "protos/Measurement.pb.h"
#include <ostream>

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

std::ostream& operator<<(std::ostream& os, const Measurement& in)
{
    return os <<in.timestamp <<", "<<in.qx <<", "<<in.qy <<", "<<in.qz <<", "<<in.qs <<", "<<in.x <<", "<<in.y <<", "<<in.z;
}
}