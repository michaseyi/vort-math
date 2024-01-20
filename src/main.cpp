

#include "Mat.hpp"
#include "Quat.hpp"
#include "Spline.hpp"
#include "Vec.hpp"

using namespace math;

int main() {
    auto translationMatrix = translation(Vec3{1.0f, 3.0f, 9.0f});
    auto scaleMatrix = scale(Vec3{1.0f, 2.0f, 1.0f});
    auto rotationMatrix = rotation(20.0f, Vec3{1.0f, 0.0f, 0.0f});

    auto modelMatrix = translationMatrix * (rotationMatrix * scaleMatrix);
    return 0;
}
