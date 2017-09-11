#pragma once
#include "Core/Types.h"
#include "Math/Vector.h"

namespace Math
{
    Vec2 clamp(const Vec2& v, float min, float max);
    Vec2 clamp(const Vec2& v, const Vec2& min, const Vec2& max);
    Vec3 clamp(const Vec3& v, float min, float max);
    Vec3 clamp(const Vec3& v, const Vec3& min, const Vec3& max);
    Vec4 clamp(const Vec4& v, float min, float max);
    Vec4 clamp(const Vec4& v, const Vec4& min, const Vec4& max);

    Vec3 cross(const Vec3& v1, const Vec3& v2);
    Vec3 cross(const Vec4& v1, const Vec4& v2);

    float distance(const Vec2& v1, const Vec2& v2);
    float distance(const Vec3& v1, const Vec3& v2);
    float distance(const Vec4& v1, const Vec4& v2);

    float dot(const Vec2& v1, const Vec2& v2);
    float dot(const Vec3& v1, const Vec3& v2);
    float dot(const Vec4& v1, const Vec4& v2);

    float length(const Vec2& v);
    float length(const Vec3& v);
    float length(const Vec4& v);

    Vec2 max(const Vec2& v, float max);
    Vec2 max(const Vec2& v, const Vec2& max);
    Vec3 max(const Vec3& v, float max);
    Vec3 max(const Vec3& v, const Vec3& max);
    Vec4 max(const Vec4& v, float max);
    Vec4 max(const Vec4& v, const Vec4& max);

    Vec2 min(const Vec2& v, float min);
    Vec2 min(const Vec2& v, const Vec2& min);
    Vec3 min(const Vec3& v, float min);
    Vec3 min(const Vec3& v, const Vec3& min);
    Vec4 min(const Vec4& v, float min);
    Vec4 min(const Vec4& v, const Vec4& min);

    Vec2 normalize(const Vec2& v);
    Vec3 normalize(const Vec3& v);
    Vec4 normalize(const Vec4& v);

    Vec2 reflect(const Vec2& incident, const Vec2& normal);
    Vec3 reflect(const Vec3& incident, const Vec3& normal);
    Vec4 reflect(const Vec4& incident, const Vec4& normal);

    Vec2 refract(const Vec2& incident, const Vec2& normal, float factor);
    Vec3 refract(const Vec3& incident, const Vec3& normal, float factor);
    Vec4 refract(const Vec4& incident, const Vec4& normal, float factor);

    Vec2 sqrt(const Vec2& v);
    Vec3 sqrt(const Vec3& v);
    Vec4 sqrt(const Vec4& v);

    float sqrtLength(const Vec2& v);
    float sqrtLength(const Vec3& v);
    float sqrtLength(const Vec4& v);
}

#include "VectorFunctions.inl"
