#include "../include/motion_blow/RotationMatrix.hpp"

void RotationMatrix::checkIfProper() {
    if(*this * this->t() != Matrix::IdentityMatrix(3)) {
        throw MatrixException();
    }
}

RotationMatrix::RotationMatrix(): Matrix(3,3) {
    checkIfProper();
}

RotationMatrix::RotationMatrix(std::vector<std::vector<double>> data): Matrix(3,3, data) {
    checkIfProper();
}

RotationMatrix::~RotationMatrix() {
    // TODO Auto-generated destructor stub
}
