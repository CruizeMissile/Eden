#include "Precompiled.h"
#include "Math/Vector.h"

namespace Math
{
    const Vec2 Vec2::Zero = { 0.0f, 0.0f };
    const Vec2 Vec2::X    = { 1.0f, 0.0f };
    const Vec2 Vec2::Y    = { 0.0f, 1.0f };
    const Vec2 Vec2::One  = { 1.0f, 1.0f };

    const Vec3 Vec3::Zero = { 0.0f, 0.0f, 0.0f };
    const Vec3 Vec3::X    = { 1.0f, 0.0f, 0.0f };
    const Vec3 Vec3::Y    = { 0.0f, 1.0f, 0.0f };
    const Vec3 Vec3::Z    = { 0.0f, 0.0f, 1.0f };
    const Vec3 Vec3::One  = { 1.0f, 1.0f, 1.0f };

    const Vec4 Vec4::Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
    const Vec4 Vec4::X    = { 1.0f, 0.0f, 0.0f, 0.0f };
    const Vec4 Vec4::Y    = { 0.0f, 1.0f, 0.0f, 0.0f };
    const Vec4 Vec4::Z    = { 0.0f, 0.0f, 1.0f, 0.0f };
    const Vec4 Vec4::W    = { 0.0f, 0.0f, 0.0f, 1.0f };
    const Vec4 Vec4::One  = { 1.0f, 1.0f, 1.0f, 1.0f };
}
