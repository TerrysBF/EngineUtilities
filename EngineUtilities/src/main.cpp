#include <iostream>

#include "../include/Vectors/Vector3.h"
#include "../include/Vectors/Vector4.h"
#include "../include/Rotations/Quaternion.h"
#include "../include/Matrix/Matrix4x4.h"
#include "../include/Utilities/EngineMath.h"
#include "../include/ECS/ECS.h"
#include "../include/Matrix/Matrix2x2.h"


using namespace EU;

void VectorsExample() {
  std::cout << "\n--- Vector3 Example ---\n";
  Math::Vector3 a(1.0f, 2.0f, 3.0f);
  Math::Vector3 b(4.0f, 5.0f, 6.0f);
  Math::Vector3 c = a + b;

  std::cout << "a + b = (" << c.x << ", " << c.y << ", " << c.z << ")\n";
  std::cout << "a · b = " << a.dot(b) << "\n";

  auto cross = a.cross(b);
  std::cout << "a x b = (" << cross.x << ", " << cross.y << ", " << cross.z << ")\n";
}

void QuaternionExample() {
  std::cout << "\n--- Quaternion Example ---\n";
  Math::Quaternion q1(1, 0, 1, 0);
  Math::Quaternion q2(1, 0.5f, 0.5f, 0.75f);
  Math::Quaternion q3 = q1 * q2;

  std::cout << "q1 * q2 = (" << q3.w << ", " << q3.x << ", " << q3.y << ", " << q3.z << ")\n";
}

void Matrix2x2Example() {
  std::cout << "\n--- Matrix2x2 Example ---\n";

  Math::Matrix2x2 matA(
    1.0f, 2.0f,
    3.0f, 4.0f
  );

  Math::Matrix2x2 matB(
    5.0f, 6.0f,
    7.0f, 8.0f
  );

  Math::Matrix2x2 result = matA * matB;

  std::cout << "matA * matB =\n";
  std::cout << result.m[0][0] << " " << result.m[0][1] << "\n";
  std::cout << result.m[1][0] << " " << result.m[1][1] << "\n";

  float det = matA.determinant();
  std::cout << "det(matA) = " << det << "\n";
}


void EngineMathExample() {
  std::cout << "\n--- EngineMath Example ---\n";
  using namespace Math::EngineMath;

  float deg = 45.0f;
  float rad = radians(deg);
  std::cout << "radians(45°) = " << rad << "\n";
  std::cout << "cos(radians(45)) = " << std::cos(static_cast<double>(rad)) << "\n";

  std::cout << "circleArea(3) = " << circleArea(3.0f) << "\n";
  std::cout << "factorial(5) = " << factorial(5) << "\n";
  std::cout << "approxEqual(0.1f + 0.2f, 0.3f) = "
    << (approxEqual(0.1f + 0.2f, 0.3f) ? "true" : "false") << "\n";
}

void ECSExample() {
  std::cout << "\n--- ECS Example ---\n";

  struct Position {
    float x, y;
  };
  struct Velocity {
    float vx, vy;
  };

  ECS::Coordinator coordinator;
  coordinator.RegisterComponent<Position>();
  coordinator.RegisterComponent<Velocity>();

  auto entity = coordinator.CreateEntity();
  coordinator.AddComponent(entity, Position{ 10, 20 });
  coordinator.AddComponent(entity, Velocity{ 1, -2 });

  auto pos = coordinator.GetComponent<Position>(entity);
  auto vel = coordinator.GetComponent<Velocity>(entity);

  pos->x += vel->vx;
  pos->y += vel->vy;

  std::cout << "Updated position: (" << pos->x << ", " << pos->y << ")\n";
}

int main() {
  std::cout << "=== EngineUtilities DEMO ===\n";

  Matrix2x2Example();
  VectorsExample();
  QuaternionExample();
  EngineMathExample();
  ECSExample();

  return 0;
}
