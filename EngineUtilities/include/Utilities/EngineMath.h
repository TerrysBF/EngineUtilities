#pragma once

#include <cmath>

/**
 * @file EngineMath.h
 * @brief Mathematical utility functions for EngineUtilities library.
 */

namespace EU::Math::EngineMath {

  // --- Constantes ---
  constexpr float PI = 3.14159265358979323846f;
  constexpr float E = 2.71828182845904523536f;

  // --- Funciones b�sicas ---

  /// @brief Calcula la ra�z cuadrada de un n�mero.
  inline float sqrt(float x) {
    return std::sqrt(x);
  }

  /// @brief Calcula el cuadrado de un n�mero.
  inline float square(float x) {
    return x * x;
  }

  /// @brief Calcula el cubo de un n�mero.
  inline float cube(float x) {
    return x * x * x;
  }

  /// @brief Eleva base a la potencia exp.
  inline float power(float base, float exp) {
    return std::pow(base, exp);
  }

  /// @brief Valor absoluto.
  inline float abs(float x) {
    return std::fabs(x);
  }

  /// @brief Retorna el m�ximo entre dos valores.
  template<typename T>
  inline T EMax(T a, T b) {
    return (a > b) ? a : b;
  }

  /// @brief Retorna el m�nimo entre dos valores.
  template<typename T>
  inline T EMin(T a, T b) {
    return (a < b) ? a : b;
  }

  /// @brief Redondea al entero m�s cercano.
  inline float round(float x) {
    return std::round(x);
  }

  /// @brief Redondea hacia abajo.
  inline float floor(float x) {
    return std::floor(x);
  }

  /// @brief Redondea hacia arriba.
  inline float ceil(float x) {
    return std::ceil(x);
  }

  /// @brief Valor absoluto flotante.
  inline float fabs(float x) {
    return std::fabs(x);
  }

  /// @brief Calcula el m�dulo (resto) entre dos floats.
  inline float mod(float x, float y) {
    return std::fmod(x, y);
  }

  /// @brief Exponencial (e^x).
  inline float exp(float x) {
    return std::exp(x);
  }

  /// @brief Logaritmo natural.
  inline float log(float x) {
    return std::log(x);
  }

  /// @brief Logaritmo base 10.
  inline float log10(float x) {
    return std::log10(x);
  }

  // --- Funciones trigonom�tricas ---

  /// @brief Seno.
  inline float sin(float x) {
    return std::sin(x);
  }

  /// @brief Coseno.
  inline float cos(float x) {
    return std::cos(x);
  }

  /// @brief Tangente.
  inline float tan(float x) {
    return std::tan(x);
  }

  /// @brief Arco seno.
  inline float asin(float x) {
    return std::asin(x);
  }

  /// @brief Arco coseno.
  inline float acos(float x) {
    return std::acos(x);
  }

  /// @brief Arco tangente.
  inline float atan(float x) {
    return std::atan(x);
  }

  /// @brief Seno hiperb�lico.
  inline float sinh(float x) {
    return std::sinh(x);
  }

  /// @brief Coseno hiperb�lico.
  inline float cosh(float x) {
    return std::cosh(x);
  }

  /// @brief Tangente hiperb�lica.
  inline float tanh(float x) {
    return std::tanh(x);
  }

  // --- Conversi�n angular ---

  /// @brief Convierte grados a radianes.
  inline float radians(float degrees) {
    return degrees * (PI / 180.0f);
  }

  /// @brief Convierte radianes a grados.
  inline float degrees(float radians) {
    return radians * (180.0f / PI);
  }

  // --- Funciones geom�tricas ---

  /// @brief �rea de un c�rculo dado el radio.
  inline float circleArea(float radius) {
    return PI * radius * radius;
  }

  /// @brief Per�metro de un c�rculo dado el radio.
  inline float circleCircumference(float radius) {
    return 2 * PI * radius;
  }

  /// @brief �rea de un rect�ngulo dado base y altura.
  inline float rectangleArea(float width, float height) {
    return width * height;
  }

  /// @brief Per�metro de un rect�ngulo dado base y altura.
  inline float rectanglePerimeter(float width, float height) {
    return 2 * (width + height);
  }

  /// @brief �rea de un tri�ngulo dado base y altura.
  inline float triangleArea(float base, float height) {
    return 0.5f * base * height;
  }

  /// @brief Distancia euclidiana entre dos puntos en 2D.
  inline float distance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
  }

  // --- Otras funciones �tiles ---

  /// @brief Interpolaci�n lineal entre a y b, par�metro t en [0,1].
  inline float lerp(float a, float b, float t) {
    return a + t * (b - a);
  }

  /// @brief Calcula factorial de un entero >= 0.
  inline unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 2; i <= n; ++i) {
      result *= i;
    }
    return result;
  }

  /// @brief Compara dos floats con tolerancia epsilon.
  inline bool approxEqual(float a, float b, float epsilon = 1e-6f) {
    return abs(a - b) <= epsilon;
  }

}
