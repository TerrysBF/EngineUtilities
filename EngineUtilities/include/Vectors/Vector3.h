#pragma once

#include <cmath>

/**
 * @file Vector3.h
 * @brief Defines a 3D vector with basic operations.
 */

namespace EU::Math {

  /**
   * @class Vector3
   * @brief Represents a 3-dimensional vector with float components.
   */
  struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
      return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
      return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
      return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const {
      return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float dot(const Vector3& other) const {
      return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
      return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
      );
    }

    float lengthSquared() const {
      return x * x + y * y + z * z;
    }

    float length() const {
      return std::sqrt(lengthSquared());
    }

    Vector3 normalized() const {
      float len = length();
      return len != 0 ? *this / len : Vector3(0, 0, 0);
    }

    void normalize() {
      float len = length();
      if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
      }
    }
  };

}
