#pragma once

#include "motion_blow/Matrix.hpp"

class RotationMatrix: public Matrix {
        void checkIfProper();
    public:
        RotationMatrix();
        RotationMatrix(std::vector<std::vector<double>> data);
        virtual ~RotationMatrix();
};
