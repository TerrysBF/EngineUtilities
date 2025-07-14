#pragma once

#include <cmath>
#include <array>
#include "../Vectors/Vector3.h"

/**
 * @file Matrix4x4.h
 * @brief Defines a 4x4 matrix used for 3D transformations.
 */

namespace EU::Math {

  /**
   * @class Matrix4x4
   * @brief Represents a 4x4 matrix used in 3D graphics transformations.
   */
  struct Matrix4x4 {
    // Row-major 4x4 matrix elements
    float m[4][4];

    /// @brief Default constructor initializes identity matrix.
    Matrix4x4() {
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          m[i][j] = (i == j) ? 1.0f : 0.0f;
    }

    /// @brief Constructor with all elements.
    Matrix4x4(float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33) {
      m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
      m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
      m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
      m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
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
    Matrix4x4 operator+(const Matrix4x4& other) const {
      Matrix4x4 result;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          result.m[i][j] = m[i][j] + other.m[i][j];
      return result;
    }

    /// @brief Matrix subtraction.
    Matrix4x4 operator-(const Matrix4x4& other) const {
      Matrix4x4 result;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          result.m[i][j] = m[i][j] - other.m[i][j];
      return result;
    }

    /// @brief Matrix multiplication.
    Matrix4x4 operator*(const Matrix4x4& other) const {
      Matrix4x4 result;
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
          result.m[i][j] = 0;
          for (int k = 0; k < 4; ++k)
            result.m[i][j] += m[i][k] * other.m[k][j];
        }
      }
      return result;
    }

    /// @brief Scalar multiplication.
    Matrix4x4 operator*(float scalar) const {
      Matrix4x4 result;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          result.m[i][j] = m[i][j] * scalar;
      return result;
    }

    /// @brief Calculates the determinant of the matrix.
    float determinant() const {
      // This is a lengthy calculation, here's an implementation for 4x4 determinant:

      float det = 0.0f;

      det += m[0][0] * (
        m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
        m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) +
        m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
        );

      det -= m[0][1] * (
        m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
        m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
        m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
        );

      det += m[0][2] * (
        m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
        m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
        m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
        );

      det -= m[0][3] * (
        m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
        m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) +
        m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
        );

      return det;
    }

    /// @brief Returns the transposed matrix.
    Matrix4x4 transpose() const {
      Matrix4x4 result;
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
          result.m[i][j] = m[j][i];
      return result;
    }

    /// @brief Returns the inverse matrix (assumes determinant != 0).
    Matrix4x4 inverse() const {
      float det = determinant();
      if (det == 0) {
        return Matrix4x4();
      }

      Matrix4x4 inv;
      float invDet = 1.0f / det;

      // Cofactor matrix calculation (hardcoded for 4x4)
      inv.m[0][0] = m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) - m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]);
      inv.m[0][1] = -m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) - m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]);
      inv.m[0][2] = m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) - m[0][2] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]);
      inv.m[0][3] = -m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) - m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);

      inv.m[1][0] = -m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) - m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]);
      inv.m[1][1] = m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) - m[0][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]);
      inv.m[1][2] = -m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][0] * m[3][3] - m[1][3] * m[3][0]) - m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]);
      inv.m[1][3] = m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) - m[0][2] * (m[1][0] * m[2][3] - m[1][3] * m[2][0]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);

      inv.m[2][0] = m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) - m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
      inv.m[2][1] = -m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) - m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
      inv.m[2][2] = m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) - m[0][1] * (m[1][0] * m[3][3] - m[1][3] * m[3][0]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]);
      inv.m[2][3] = -m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][0] * m[2][3] - m[1][3] * m[2][0]) - m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

      inv.m[3][0] = -m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) - m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
      inv.m[3][1] = m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) - m[0][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
      inv.m[3][2] = -m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]) - m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]);
      inv.m[3][3] = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

      return inv * invDet;
    }

    /// @brief Creates a translation matrix.
    static Matrix4x4 translation(const Vector3& translation) {
      Matrix4x4 result;
      result.m[0][3] = translation.x;
      result.m[1][3] = translation.y;
      result.m[2][3] = translation.z;
      return result;
    }

    /// @brief Creates a scaling matrix.
    static Matrix4x4 scale(const Vector3& scale) {
      Matrix4x4 result;
      result.m[0][0] = scale.x;
      result.m[1][1] = scale.y;
      result.m[2][2] = scale.z;
      return result;
    }

    /// @brief Creates a rotation matrix around X axis.
    static Matrix4x4 rotationX(float radians) {
      float c = std::cos(radians);
      float s = std::sin(radians);
      Matrix4x4 result;
      result.m[1][1] = c;  result.m[1][2] = -s;
      result.m[2][1] = s;  result.m[2][2] = c;
      return result;
    }

    /// @brief Creates a rotation matrix around Y axis.
    static Matrix4x4 rotationY(float radians) {
      float c = std::cos(radians);
      float s = std::sin(radians);
      Matrix4x4 result;
      result.m[0][0] = c;  result.m[0][2] = s;
      result.m[2][0] = -s; result.m[2][2] = c;
      return result;
    }

    /// @brief Creates a rotation matrix around Z axis.
    static Matrix4x4 rotationZ(float radians) {
      float c = std::cos(radians);
      float s = std::sin(radians);
      Matrix4x4 result;
      result.m[0][0] = c;  result.m[0][1] = -s;
      result.m[1][0] = s;  result.m[1][1] = c;
      return result;
    }

    /// @brief Creates a rotation matrix from a Quaternion.
    static Matrix4x4 fromQuaternion(const Quaternion& q) {
      float xx = q.x * q.x;
      float yy = q.y * q.y;
      float zz = q.z * q.z;
      float xy = q.x * q.y;
      float xz = q.x * q.z;
      float yz = q.y * q.z;
      float wx = q.w * q.x;
      float wy = q.w * q.y;
      float wz = q.w * q.z;

      Matrix4x4 result;

      result.m[0][0] = 1 - 2 * (yy + zz);
      result.m[0][1] = 2 * (xy - wz);
      result.m[0][2] = 2 * (xz + wy);
      result.m[0][3] = 0;

      result.m[1][0] = 2 * (xy + wz);
      result.m[1][1] = 1 - 2 * (xx + zz);
      result.m[1][2] = 2 * (yz - wx);
      result.m[1][3] = 0;

      result.m[2][0] = 2 * (xz - wy);
      result.m[2][1] = 2 * (yz + wx);
      result.m[2][2] = 1 - 2 * (xx + yy);
      result.m[2][3] = 0;

      result.m[3][0] = 0;
      result.m[3][1] = 0;
      result.m[3][2] = 0;
      result.m[3][3] = 1;

      return result;
    }
  };

}