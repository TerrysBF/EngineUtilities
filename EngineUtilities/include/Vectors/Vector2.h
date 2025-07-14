#pragma once

#include <cmath>

/**
 * @file Vector2.h
 * @brief Defines a 2D vector with basic operations.
 */

namespace EU::Math {

  /**
   * @class Vector2
   * @brief Represents a 2-dimensional vector with float components.
   */
  struct Vector2 {
    float x, y;

    /// @brief Default constructor initializes to zero.
    Vector2() : x(0), y(0) {}

    /// @brief Constructor with component initialization.
    Vector2(float x, float y) : x(x), y(y) {}

    /// @brief Vector addition.
    Vector2 operator+(const Vector2& other) const {
      return Vector2(x + other.x, y + other.y);
    }

    /// @brief Vector subtraction.
    Vector2 operator-(const Vector2& other) const {
      return Vector2(x - other.x, y - other.y);
    }

    /// @brief Scalar multiplication.
    Vector2 operator*(float scalar) const {
      return Vector2(x * scalar, y * scalar);
    }

    /// @brief Scalar division.
    Vector2 operator/(float scalar) const {
      return Vector2(x / scalar, y / scalar);
    }

    /// @brief Dot product of two vectors.
    float dot(const Vector2& other) const {
      return x * other.x + y * other.y;
    }

    /// @brief Returns the squared length of the vector.
    float lengthSquared() const {
      return x * x + y * y;
    }

    /// @brief Returns the length (magnitude) of the vector.
    float length() const {
      return std::sqrt(lengthSquared());
    }

    /// @brief Returns the normalized vector (unit vector).
    Vector2 normalized() const {
      float len = length();
      return len != 0 ? *this / len : Vector2(0, 0);
    }

    /// @brief Normalizes the current vector.
    void normalize() {
      float len = length();
      if (len != 0) {
        x /= len;
        y /= len;
      }
    }
  };

}
