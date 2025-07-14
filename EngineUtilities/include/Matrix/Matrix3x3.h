#pragma once

#include <cmath>
#include <array>
#include "../Vectors/Vector3.h"

/**
 * @file Matrix3x3.h
 * @brief Defines a 3x3 matrix with operations including 2D transformations.
 */

namespace EU::Math {

  /**
   * @class Matrix3x3
   * @brief Represents a 3x3 matrix used often for 2D affine transformations.
   */
  struct Matrix3x3 {
    // Row-major order 3x3 matrix
    float m[3][3];

    /// @brief Default constructor initializes identity matrix.
    Matrix3x3() {
      m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
      m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
      m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }

    /// @brief Constructor with elements.
    Matrix3x3(float m00, float m01, float m02,
      float m10, float m11, float m12,
      float m20, float m21, float m22) {
      m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
      m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
      m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    /// @brief Access element by row and column.
    float& operator()(int row, int col) {
      return m[row][col];
    }

    /// @brief Access element by row and column (const).
    float operator()(int row, int col) const {
      return m[row][col];
    }

    /// @brief Matrix addition.
    Matrix3x3 operator+(const Matrix3x3& other) const {
      Matrix3x3 result;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          result.m[i][j] = m[i][j] + other.m[i][j];
      return result;
    }

    /// @brief Matrix subtraction.
    Matrix3x3 operator-(const Matrix3x3& other) const {
      Matrix3x3 result;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          result.m[i][j] = m[i][j] - other.m[i][j];
      return result;
    }

    /// @brief Matrix multiplication.
    Matrix3x3 operator*(const Matrix3x3& other) const {
      Matrix3x3 result;
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          result.m[i][j] = 0;
          for (int k = 0; k < 3; ++k) {
            result.m[i][j] += m[i][k] * other.m[k][j];
          }
        }
      }
      return result;
    }

    /// @brief Scalar multiplication.
    Matrix3x3 operator*(float scalar) const {
      Matrix3x3 result;
      for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
          result.m[i][j] = m[i][j] * scalar;
      return result;
    }

    /// @brief Calculates the determinant of the matrix.
    float determinant() const {
      return
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
        m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
        m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    /// @brief Returns the transposed matrix.
    Matrix3x3 transpose() const {
      return Matrix3x3(
        m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
      );
    }

    /// @brief Returns the inverse matrix (assumes determinant != 0).
    Matrix3x3 inverse() const {
      float det = determinant();
      if (det == 0) {
        // Return identity or throw exception, here identity
        return Matrix3x3();
      }
      float invDet = 1.0f / det;

      Matrix3x3 inv;

      inv.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
      inv.m[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * invDet;
      inv.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;

      inv.m[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * invDet;
      inv.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
      inv.m[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * invDet;

      inv.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
      inv.m[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * invDet;
      inv.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;

      return inv;
    }

    /// @brief Creates a translation matrix for 2D translation.
    static Matrix3x3 translation(float tx, float ty) {
      return Matrix3x3(
        1, 0, tx,
        0, 1, ty,
        0, 0, 1
      );
    }

    /// @brief Creates a rotation matrix for 2D rotation (angle in radians).
    static Matrix3x3 rotation(float angleRadians) {
      float c = std::cos(angleRadians);
      float s = std::sin(angleRadians);
      return Matrix3x3(
        c, -s, 0,
        s, c, 0,
        0, 0, 1
      );
    }

    /// @brief Creates a scaling matrix for 2D scale.
    static Matrix3x3 scale(float sx, float sy) {
      return Matrix3x3(
        sx, 0, 0,
        0, sy, 0,
        0, 0, 1
      );
    }
  };

}
