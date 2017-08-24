#include "Core/Logging.h"
#include "Math/MathFunctions.h"
#include <math.h>


namespace Math
{
	inline Vec2 clamp(const Vec2& v, float min, float max)
	{
		return Vec2(clamp(v.x, min, max), clamp(v.y, min, max));
	}

	inline Vec2 clamp(const Vec2& v, const Vec2& min, const Vec2& max)
	{
		return Vec2(clamp(v.x, min.y, max.y), clamp(v.y, min.y, max.y));
	}

	inline Vec3 clamp(const Vec3& v, float min, float max)
	{
		return Vec3(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
	}

	inline Vec3 clamp(const Vec3& v, const Vec3& min, const Vec3& max)
	{
		return Vec3(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z));
	}

	inline Vec4 clamp(const Vec4& v, float min, float max)
	{
		return Vec4(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max));
	}

	inline Vec4 clamp(const Vec4& v, const Vec4& min, const Vec4& max)
	{
		return Vec4(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w));
	}

	inline Vec3 cross(const Vec3& v1, const Vec3& v2)
	{
		return Vec3(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}

	inline Vec3 cross(const Vec4& v1, const Vec4& v2)
	{
		return cross(v1.xyz, v2.xyz);
	}

	inline float distance(const Vec2& v1, const Vec2& v2)
	{
		return length(v1 - v2);
	}

	inline float distance(const Vec3& v1, const Vec3& v2)
	{
		return length(v1 - v2);
	}

	inline float distance(const Vec4& v1, const Vec4& v2)
	{
		return length(v1 - v2);
	}

	inline float dot(const Vec2& v1, const Vec2& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	inline float dot(const Vec3& v1, const Vec3& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	inline float dot(const Vec4& v1, const Vec4& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
	}

	inline float length(const Vec2& v)
	{
		return sqrtf((v.x * v.x) + (v.y * v.y));
	}

	inline float length(const Vec3& v)
	{
		return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	inline float length(const Vec4& v)
	{
		return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
	}

	inline Vec2 max(const Vec2& v, float m)
	{
		return Vec2(min(v.x, m), min(v.y, m));
	}

	inline Vec2 max(const Vec2& v, const Vec2& m)
	{
		return Vec2(min(v.x, m.x), min(v.y, m.y));
	}

	inline Vec3 max(const Vec3& v, float m)
	{
		return Vec3(min(v.x, m), min(v.y, m), min(v.z, m));
	}

	inline Vec3 max(const Vec3& v, const Vec3& m)
	{
		return Vec3(min(v.x, m.x), min(v.y, m.y), min(v.z, m.z));
	}

	inline Vec4 max(const Vec4& v, float m)
	{
		return Vec4(min(v.x, m), min(v.y, m), min(v.z, m), min(v.w, m));
	}

	inline Vec4 max(const Vec4& v, const Vec4& m)
	{
		return Vec4(min(v.x, m.x), min(v.y, m.y), min(v.z, m.z), min(v.w, m.w));
	}

	inline Vec2 min(const Vec2& v, float m)
	{
		return Vec2(min(v.x, m), min(v.y, m));
	}

	inline Vec2 min(const Vec2& v, const Vec2& m)
	{
		return Vec2(min(v.x, m.x), min(v.y, m.x));
	}

	inline Vec3 min(const Vec3& v, float m)
	{
		return Vec3(min(v.x, m), min(v.y, m), min(v.z, m));
	}

	inline Vec3 min(const Vec3& v, const Vec3& m)
	{
		return Vec3(min(v.x, m.x), min(v.y, m.y), min(v.z, m.z));
	}

	inline Vec4 min(const Vec4& v, float m)
	{
		return Vec4(min(v.x, m), min(v.y, m), min(v.z, m), min(v.w, m));
	}

	inline Vec4 min(const Vec4& v, const Vec4& m)
	{
		return Vec4(min(v.x, m.x), min(v.y, m.y), min(v.z, m.z), min(v.w, m.w));
	}

	inline Vec2 normalize(const Vec2& v)
	{
		auto len = length(v);
		//assert(len != 0 && "[normalize][Vec2] length of vector is zero");
		auto invLength = 1.0f / len;
		return v * invLength;
	}

	inline Vec3 normalize(const Vec3& v)
	{
		auto len = length(v);
		//assert(len != 0 && "[normalize][Vec3] length of vector is zero");
		auto invLength = 1.0f / len;
		return v * invLength;
	}

	inline Vec4 normalize(const Vec4& v)
	{
		auto len = length(v);
		//assert(len != 0 && "[normalize][Vec4] length of vector is zero");
		auto invLength = 1.0f / len;
		return v * invLength;
	}

	inline Vec2 reflect(const Vec2& incident, const Vec2& normal)
	{
		return incident - 2.0f * dot(incident, normal) * normal;
	}

	inline Vec3 reflect(const Vec3& incident, const Vec3& normal)
	{
		return incident - 2.0f * dot(incident, normal) * normal;
	}

	inline Vec4 reflect(const Vec4& incident, const Vec4& normal)
	{
		return incident - 2.0f * dot(incident, normal) * normal;
	}

	inline Vec2 refract(const Vec2& incident, const Vec2& normal, float factor)
	{
		float n_dot_i = dot(normal, incident);
		float k = 1.0f - factor * factor * (1.0f - n_dot_i * n_dot_i);
		if (k < 0.0f)
			return Vec2();
		return factor * incident - (factor * n_dot_i + sqrtf(k) * normal);
	}

	inline Vec3 refract(const Vec3& incident, const Vec3& normal, float factor)
	{
		float n_dot_i = dot(normal, incident);
		float k = 1.0f - factor * factor * (1.0f - n_dot_i * n_dot_i);
		if (k < 0.0f)
			return Vec3();
		return factor * incident - (factor * n_dot_i + sqrtf(k) * normal);
	}

	inline Vec4 refract(const Vec4& incident, const Vec4& normal, float factor)
	{
		float n_dot_i = dot(normal, incident);
		float k = 1.0f - factor * factor * (1.0f - n_dot_i * n_dot_i);
		if (k < 0.0f)
			return Vec4();
		return factor * incident - (factor * n_dot_i + sqrtf(k) * normal);
	}

	inline Vec2 sqrt(const Vec2& v)
	{
		return Vec2((v.x * v.x), (v.y * v.y));
	}

	inline Vec3 sqrt(const Vec3& v)
	{
		return Vec3((v.x * v.x), (v.y * v.y), (v.z * v.z));
	}

	inline Vec4 sqrt(const Vec4& v)
	{
		return Vec4((v.x * v.x), (v.y * v.y), (v.z * v.z), (v.w * v.w));
	}

	inline float sqrtLength(const Vec2& v)
	{
		return (v.x * v.x) + (v.y * v.y);
	}

	inline float sqrtLength(const Vec3& v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	inline float sqrtLength(const Vec4& v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w);
	}
}
