#pragma once

#include <cmath>
#include "../Vectors/Vector3.h"
#include "../Matrix/Matrix3x3.h"

/**
 * @file Quaternion.h
 * @brief Defines a quaternion structure for representing 3D rotations.
 */

namespace EU::Math {

  /**
   * @class Quaternion
   * @brief Represents a quaternion used for 3D rotations.
   */
  struct Quaternion {
    float w, x, y, z;

    /// @brief Default constructor (identity quaternion).
    Quaternion() : w(1), x(0), y(0), z(0) {}

    /// @brief Constructor from components.
    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

    /// @brief Creates a quaternion from axis-angle representation.
    static Quaternion fromAxisAngle(const Vector3& axis, float angleRadians) {
      float halfAngle = angleRadians * 0.5f;
      float sinHalf = std::sin(halfAngle);
      return Quaternion(
        std::cos(halfAngle),
        axis.x * sinHalf,
        axis.y * sinHalf,
        axis.z * sinHalf
      );
    }

    /// @brief Returns the conjugate of the quaternion.
    Quaternion conjugate() const {
      return Quaternion(w, -x, -y, -z);
    }

    /// @brief Returns the squared length of the quaternion.
    float lengthSquared() const {
      return w * w + x * x + y * y + z * z;
    }

    /// @brief Returns the length of the quaternion.
    float length() const {
      return std::sqrt(lengthSquared());
    }

    /// @brief Normalizes the quaternion in-place.
    void normalize() {
      float len = length();
      if (len != 0) {
        w /= len;
        x /= len;
        y /= len;
        z /= len;
      }
    }

    /// @brief Returns a normalized copy of this quaternion.
    Quaternion normalized() const {
      float len = length();
      return len != 0 ? Quaternion(w / len, x / len, y / len, z / len)
        : Quaternion();
    }

    /// @brief Quaternion multiplication (combining rotations).
    Quaternion operator*(const Quaternion& other) const {
      return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
      );
    }

    /// @brief Rotates a 3D vector by this quaternion.
    Vector3 rotate(const Vector3& v) const {
      Quaternion qv(0, v.x, v.y, v.z);
      Quaternion result = (*this) * qv * conjugate();
      return Vector3(result.x, result.y, result.z);
    }

    /// @brief Converts the quaternion to a 3x3 rotation matrix.
    Matrix3x3 toMatrix3x3() const {
      float xx = x * x, yy = y * y, zz = z * z;
      float xy = x * y, xz = x * z, yz = y * z;
      float wx = w * x, wy = w * y, wz = w * z;

      return Matrix3x3({
          1 - 2 * (yy + zz), 2 * (xy - wz),     2 * (xz + wy),
          2 * (xy + wz),     1 - 2 * (xx + zz), 2 * (yz - wx),
          2 * (xz - wy),     2 * (yz + wx),     1 - 2 * (xx + yy)
        });
    }
  };

}
