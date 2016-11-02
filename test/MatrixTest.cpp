/*
 * MatrixTest.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: link
 */

#include "motion_blow/Matrix.hpp"
#include "gtest/gtest.h"

Matrix m1(2, 2,
{
{ 1, 3 },
{ 2, 4 } });
Matrix m2(2, 2,
{
{ 5, 7 },
{ 6, 8 } });

Matrix m3(2, 2,
{
{ 6, 10 },
{ 8, 12 } });

Matrix m4(4, 2,
{
{ 7, 11 },
{ 8, 12 },
{ 9, 13 },
{ 10, 14 } });

Matrix m5(4, 2,
{
{ 29, 65 },
{ 32, 72 },
{ 35, 79 },
{ 38, 86 } });

TEST(MatrixTest, MatrixAdditionProperDimensions) {
    EXPECT_EQ(m1 + m2 , m3);
}

TEST(MatrixTest, MatrixSubstractionProperDimensions) {
    EXPECT_EQ(m3 - m2, m1);
}


TEST(MatrixTest, MatrixMultiplicationProperDimensions) {
    EXPECT_EQ(m1 * m4, m5);
}

TEST(MatrixTest, MatrixMultiplicationByScalar) {
    EXPECT_EQ(1,1); //Later
}

TEST(MatrixTest, MatrixMultiplyByIdentity) {
    EXPECT_EQ(m1 * Matrix::IdentityMatrix(2), m1);
}

TEST(MatrixTest, MatrixOperatorNotEqual) {
    EXPECT_TRUE(m1 != m2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
