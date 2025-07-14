#pragma once

#include <cmath>

/**
 * @file Vector4.h
 * @brief Defines a 4D vector with basic operations.
 */

namespace EU::Math {

  /**
   * @class Vector4
   * @brief Represents a 4-dimensional vector with float components.
   */
  struct Vector4 {
    float x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vector4 operator+(const Vector4& other) const {
      return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) const {
      return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 operator*(float scalar) const {
      return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vector4 operator/(float scalar) const {
      return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    float dot(const Vector4& other) const {
      return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float lengthSquared() const {
      return x * x + y * y + z * z + w * w;
    }

    float length() const {
      return std::sqrt(lengthSquared());
    }

    Vector4 normalized() const {
      float len = length();
      return len != 0 ? *this / len : Vector4(0, 0, 0, 0);
    }

    void normalize() {
      float len = length();
      if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
        w /= len;
      }
    }
  };

}
