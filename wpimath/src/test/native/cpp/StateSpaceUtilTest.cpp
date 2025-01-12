// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>

#include <array>

#include "Eigen/Core"
#include "frc/StateSpaceUtil.h"
#include "frc/system/NumericalIntegration.h"

TEST(StateSpaceUtilTest, MakeMatrix) {
  // Column vector
  Eigen::Vector<double, 2> mat1 = frc::MakeMatrix<2, 1>(1.0, 2.0);
  EXPECT_NEAR(mat1(0), 1.0, 1e-3);
  EXPECT_NEAR(mat1(1), 2.0, 1e-3);

  // Row vector
  Eigen::RowVector<double, 2> mat2 = frc::MakeMatrix<1, 2>(1.0, 2.0);
  EXPECT_NEAR(mat2(0), 1.0, 1e-3);
  EXPECT_NEAR(mat2(1), 2.0, 1e-3);

  // Square matrix
  Eigen::Matrix<double, 2, 2> mat3 = frc::MakeMatrix<2, 2>(1.0, 2.0, 3.0, 4.0);
  EXPECT_NEAR(mat3(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat3(0, 1), 2.0, 1e-3);
  EXPECT_NEAR(mat3(1, 0), 3.0, 1e-3);
  EXPECT_NEAR(mat3(1, 1), 4.0, 1e-3);

  // Nonsquare matrix with more rows than columns
  Eigen::Matrix<double, 3, 2> mat4 =
      frc::MakeMatrix<3, 2>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  EXPECT_NEAR(mat4(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat4(0, 1), 2.0, 1e-3);
  EXPECT_NEAR(mat4(1, 0), 3.0, 1e-3);
  EXPECT_NEAR(mat4(1, 1), 4.0, 1e-3);
  EXPECT_NEAR(mat4(2, 0), 5.0, 1e-3);
  EXPECT_NEAR(mat4(2, 1), 6.0, 1e-3);

  // Nonsquare matrix with more columns than rows
  Eigen::Matrix<double, 2, 3> mat5 =
      frc::MakeMatrix<2, 3>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  EXPECT_NEAR(mat5(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat5(0, 1), 2.0, 1e-3);
  EXPECT_NEAR(mat5(0, 2), 3.0, 1e-3);
  EXPECT_NEAR(mat5(1, 0), 4.0, 1e-3);
  EXPECT_NEAR(mat5(1, 1), 5.0, 1e-3);
  EXPECT_NEAR(mat5(1, 2), 6.0, 1e-3);
}

TEST(StateSpaceUtilTest, CostParameterPack) {
  Eigen::Matrix<double, 3, 3> mat = frc::MakeCostMatrix(1.0, 2.0, 3.0);
  EXPECT_NEAR(mat(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat(0, 1), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 0), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 1), 1.0 / 4.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(2, 2), 1.0 / 9.0, 1e-3);
}

TEST(StateSpaceUtilTest, CostArray) {
  Eigen::Matrix<double, 3, 3> mat = frc::MakeCostMatrix<3>({1.0, 2.0, 3.0});
  EXPECT_NEAR(mat(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat(0, 1), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 0), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 1), 1.0 / 4.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(2, 2), 1.0 / 9.0, 1e-3);
}

TEST(StateSpaceUtilTest, CovParameterPack) {
  Eigen::Matrix<double, 3, 3> mat = frc::MakeCovMatrix(1.0, 2.0, 3.0);
  EXPECT_NEAR(mat(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat(0, 1), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 0), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 1), 4.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(2, 2), 9.0, 1e-3);
}

TEST(StateSpaceUtilTest, CovArray) {
  Eigen::Matrix<double, 3, 3> mat = frc::MakeCovMatrix<3>({1.0, 2.0, 3.0});
  EXPECT_NEAR(mat(0, 0), 1.0, 1e-3);
  EXPECT_NEAR(mat(0, 1), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 0), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 1), 4.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(0, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(1, 2), 0.0, 1e-3);
  EXPECT_NEAR(mat(2, 2), 9.0, 1e-3);
}

TEST(StateSpaceUtilTest, WhiteNoiseVectorParameterPack) {
  Eigen::Vector<double, 2> vec = frc::MakeWhiteNoiseVector(2.0, 3.0);
  static_cast<void>(vec);
}

TEST(StateSpaceUtilTest, WhiteNoiseVectorArray) {
  Eigen::Vector<double, 2> vec = frc::MakeWhiteNoiseVector<2>({2.0, 3.0});
  static_cast<void>(vec);
}

TEST(StateSpaceUtilTest, IsStabilizable) {
  Eigen::Matrix<double, 2, 1> B{0, 1};

  // We separate the result of IsStabilizable from the assertion because
  // templates break gtest.

  // First eigenvalue is uncontrollable and unstable.
  // Second eigenvalue is controllable and stable.
  Eigen::Matrix<double, 2, 2> A1{{1.2, 0}, {0, 0.5}};
  bool ret = frc::IsStabilizable<2, 1>(A1, B);
  EXPECT_FALSE(ret);

  // First eigenvalue is uncontrollable and marginally stable.
  // Second eigenvalue is controllable and stable.
  Eigen::Matrix<double, 2, 2> A2{{1, 0}, {0, 0.5}};
  ret = frc::IsStabilizable<2, 1>(A2, B);
  EXPECT_FALSE(ret);

  // First eigenvalue is uncontrollable and stable.
  // Second eigenvalue is controllable and stable.
  Eigen::Matrix<double, 2, 2> A3{{0.2, 0}, {0, 0.5}};
  ret = frc::IsStabilizable<2, 1>(A3, B);
  EXPECT_TRUE(ret);

  // First eigenvalue is uncontrollable and stable.
  // Second eigenvalue is controllable and unstable.
  Eigen::Matrix<double, 2, 2> A4{{0.2, 0}, {0, 1.2}};
  ret = frc::IsStabilizable<2, 1>(A4, B);
  EXPECT_TRUE(ret);
}
