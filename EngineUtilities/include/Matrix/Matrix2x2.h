#pragma once

#include <cmath>
#include <array>

/**
 * @file Matrix2x2.h
 * @brief Defines a 2x2 matrix with basic operations.
 */

namespace EU::Math {

  /**
   * @class Matrix2x2
   * @brief Represents a 2x2 matrix.
   */
  struct Matrix2x2 {
    // Elements stored in row-major order
    float m[2][2];

    /// @brief Default constructor initializes to identity matrix.
    Matrix2x2() {
      m[0][0] = 1; m[0][1] = 0;
      m[1][0] = 0; m[1][1] = 1;
    }

    /// @brief Constructor with elements.
    Matrix2x2(float m00, float m01,
      float m10, float m11) {
      m[0][0] = m00; m[0][1] = m01;
      m[1][0] = m10; m[1][1] = m11;
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
    Matrix2x2 operator+(const Matrix2x2& other) const {
      return Matrix2x2(
        m[0][0] + other.m[0][0], m[0][1] + other.m[0][1],
        m[1][0] + other.m[1][0], m[1][1] + other.m[1][1]
      );
    }

    /// @brief Matrix subtraction.
    Matrix2x2 operator-(const Matrix2x2& other) const {
      return Matrix2x2(
        m[0][0] - other.m[0][0], m[0][1] - other.m[0][1],
        m[1][0] - other.m[1][0], m[1][1] - other.m[1][1]
      );
    }

    /// @brief Matrix multiplication.
    Matrix2x2 operator*(const Matrix2x2& other) const {
      return Matrix2x2(
        m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0],
        m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1],
        m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0],
        m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1]
      );
    }

    /// @brief Scalar multiplication.
    Matrix2x2 operator*(float scalar) const {
      return Matrix2x2(
        m[0][0] * scalar, m[0][1] * scalar,
        m[1][0] * scalar, m[1][1] * scalar
      );
    }

    /// @brief Calculates the determinant.
    float determinant() const {
      return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    /// @brief Returns the transposed matrix.
    Matrix2x2 transpose() const {
      return Matrix2x2(
        m[0][0], m[1][0],
        m[0][1], m[1][1]
      );
    }

    /// @brief Returns the inverse matrix (assumes determinant != 0).
    Matrix2x2 inverse() const {
      float det = determinant();
      if (det == 0) {
        // Return identity if not invertible (could also throw)
        return Matrix2x2();
      }
      float invDet = 1.0f / det;
      return Matrix2x2(
        m[1][1] * invDet, -m[0][1] * invDet,
        -m[1][0] * invDet, m[0][0] * invDet
      );
    }
  };

}
