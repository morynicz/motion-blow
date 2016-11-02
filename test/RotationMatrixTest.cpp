#include "motion_blow/RotationMatrix.hpp"
#include "gtest/gtest.h"

TEST(RotationMatrixTest, RotationMatrixProperMatrix) {
    EXPECT_NO_THROW(RotationMatrix({{1,0,0},{0,1,0}, {0,0,1}}));
}

TEST(RotationMatrixTest, RotationMatrixInproperMatrix) {
    EXPECT_THROW(RotationMatrix({{2,0,0},{0,1,0}, {0,0,1}}), MatrixException);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
