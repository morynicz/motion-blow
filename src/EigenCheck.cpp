#include "Eigen/Dense"
#include "RTIMULib.h"
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

Eigen::Quaterniond rtToEQuat(RTQuaternion rq)
{
    return Eigen::Quaterniond(rq.scalar(), rq.x(), rq.y(), rq.z());
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    std::fstream input, output;

    input.open(argv[1], std::fstream::in);
    output.open(argv[2], std::fstream::out);

    std::vector<std::tuple<long, Eigen::Quaterniond, Eigen::Vector3d>>
        inputData;

    Eigen::Vector3d sword;
    sword << 1, 0, 0;

    while (!input.eof())
    {
        long timestamp;
        double x, y, z, qx, qy, qz, qs;

        input >> timestamp >> qs >> qx >> qy >> qz >> x >> y >> z;
        inputData.push_back(std::make_tuple(timestamp,
                                            Eigen::Quaterniond(qs, qx, qy, qz),
                                            Eigen::Vector3d(x, y, z)));
    }

    for (auto t : inputData)
    {
        output << std::get<0>(t);
        Eigen::Quaterniond q = std::get<1>(t);
        //        Eigen::Vector3d transformed = q._transformVector(sword);
        //        output<<" "<<transformed.x()<<" "<<transformed.y()<<"
        //        "<<transformed.z()<<std::endl;
        Eigen::AngleAxisd aa(q);
        output << " " << aa.angle() << " " << aa.axis().x() << " "
               << aa.axis().y() << " " << aa.axis().z() << std::endl;
    }

    Eigen::Quaterniond q;

    return 0;
}
