#include "Precompiled.h"
#include "Vector.h"

#include <math.h>

namespace edn
{

#pragma region Vector2

	vec2::vec2()
	{
	}

	vec2::vec2(float X, float Y)
		: x(X), y(Y)
	{
	}

	vec2::vec2(float val)
		: x(val), y(val)
	{
	}

	bool vec2::operator==(const vec2 &RHS) const
	{
		return (this->x == RHS.x) && (this->y == RHS.y);
	}

	bool vec2::operator!=(const vec2 &RHS) const
	{
		return (this->x != RHS.x) || (this->y != RHS.y);
	}

	vec2& vec2::operator=(const vec2 &RHS)
	{
		this->x = RHS.x;
		this->y = RHS.y;
		return *this;
	}

	vec2& vec2::operator-=(const vec2 &RHS)
	{
		this->x -= RHS.x;
		this->y -= RHS.y;
		return *this;
	}

	vec2& vec2::operator+=(const vec2 &RHS)
	{
		this->x += RHS.x;
		this->y += RHS.y;
		return *this;
	}

	vec2& vec2::operator*=(const vec2& RHS)
	{
		this->x *= RHS.x;
		this->y *= RHS.y;
		return *this;
	}

	vec2& vec2::operator/=(const vec2& RHS)
	{
		this->x /= RHS.x;
		this->y /= RHS.y;
		return *this;
	}

	vec2& vec2::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	vec2& vec2::operator/=(float divisor)
	{
		float inverse = 1.0f / divisor;
		this->x *= inverse;
		this->y *= inverse;
		return *this;
	}

	vec2 vec2::operator-(const vec2 &RHS) const
	{
		return vec2(x - RHS.x, y - RHS.y);
	}

	vec2 vec2::operator+(const vec2 &RHS) const
	{
		return vec2(x + RHS.x, y + RHS.y);
	}

	vec2 vec2::operator*(const vec2 &RHS) const
	{
		return vec2(x * RHS.x, y * RHS.y);
	}

	vec2 vec2::operator/(const vec2 &RHS) const
	{
		return vec2(x / RHS.x, y / RHS.y);
	}

	vec2 vec2::operator*(float scalar) const
	{
		return vec2(x * scalar, y * scalar);
	}

	vec2 vec2::operator/(float divisor) const
	{
		float inverse = 1.0f / divisor;
		return vec2(x * inverse, y * inverse);
	}

	vec2 vec2::operator-() const
	{
		return vec2(-x, -y);
	}

	float vec2::operator[](unsigned int index) const
	{
		assert(index >= 0 && index < 2, "'index' must be in the range of [0, 1].");
		return *(&x + index);
	}

	float &vec2::operator[](unsigned int index)
	{
		assert(index >= 0 && index < 2, "'index' must be in the range of [0, 1].");
		return *(&x + index);
	}

	float vec2::Length() const
	{
		return sqrt(this->x * this->x + this->y * this->y);
	}

	float vec2::LengthSquared() const
	{
		return this->x * this->x + this->y * this->y;
	}

	void vec2::Normalize()
	{
		float invLength = 1.0f / this->Length();

		assert(!std::isinf(invLength), "Zero length vector cannot be normalized.");

		this->x *= invLength;
		this->y *= invLength;
	}

	vec2 vec2::GetNormalized() const
	{
		float invLength = 1.0f / this->Length();

		assert(!std::isinf(invLength), "Zero length vector cannot be normalized.");

		return vec2(x * invLength, y * invLength);
	}

#pragma endregion

#pragma region Vector3

	vec3::vec3()
	{
	}

	vec3::vec3(const vec2 &xy, float Z)
		: x(xy.x), y(xy.y), z(Z)
	{
	}

	vec3::vec3(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{
	}

	vec3::vec3(float val)
		: x(val), y(val), z(val)
	{
	}

	bool vec3::operator==(const vec3 &RHS) const
	{
		return (this->x == RHS.x) && (this->y == RHS.y) && (this->z == RHS.z);
	}

	bool vec3::operator!=(const vec3 &RHS) const
	{
		return (this->x != RHS.x) || (this->y != RHS.y) || (this->z != RHS.z);
	}

	vec3& vec3::operator=(const vec3 &RHS)
	{
		this->x = RHS.x;
		this->y = RHS.y;
		this->z = RHS.z;
		return *this;
	}

	vec3& vec3::operator-=(const vec3 &RHS)
	{
		this->x -= RHS.x;
		this->y -= RHS.y;
		this->z -= RHS.z;
		return *this;
	}

	vec3& vec3::operator+=(const vec3 &RHS)
	{
		this->x += RHS.x;
		this->y += RHS.y;
		this->z += RHS.z;
		return *this;
	}

	vec3& vec3::operator*=(const vec3 &RHS)
	{
		this->x *= RHS.x;
		this->y *= RHS.y;
		this->z *= RHS.z;
		return *this;
	}

	vec3& vec3::operator/=(const vec3 &RHS)
	{
		this->x /= RHS.x;
		this->y /= RHS.y;
		this->z /= RHS.z;
		return *this;
	}

	vec3& vec3::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	vec3& vec3::operator/=(float divisor)
	{
		float inverse = 1.0f / divisor;
		this->x *= inverse;
		this->y *= inverse;
		this->z *= inverse;
		return *this;
	}

	vec3 vec3::operator-(const vec3 &RHS) const
	{
		return vec3(x - RHS.x, y - RHS.y, z - RHS.z);
	}

	vec3 vec3::operator+(const vec3 &RHS) const
	{
		return vec3(x + RHS.x, y + RHS.y, z + RHS.z);
	}

	vec3 vec3::operator*(const vec3 &RHS) const
	{
		return vec3(x * RHS.x, y * RHS.y, z * RHS.z);
	}

	vec3 vec3::operator/(const vec3 &RHS) const
	{
		return vec3(x / RHS.x, y / RHS.y, z / RHS.z);
	}

	vec3 vec3::operator*(float scalar) const
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	vec3 vec3::operator/(float divisor) const
	{
		float inverse = 1.0f / divisor;
		return vec3(x * inverse, y * inverse, z * inverse);
	}

	vec3 vec3::operator-() const
	{
		return vec3(-x, -y, -z);
	}

	float vec3::operator[](unsigned int index) const
	{
		assert(index >= 0 && index < 3, "'index' must be in the range of [0, 2].");
		return *(&x + index);
	}

	float &vec3::operator[](unsigned int index)
	{
		assert(index >= 0 && index < 3, "'index' must be in the range of [0, 2].");
		return *(&x + index);
	}

	float vec3::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float vec3::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	void vec3::Normalize()
	{
		float invLength = 1.0f / this->Length();

		assert(!std::isinf(invLength), "Zero length vector cannot be normalized.");

		this->x *= invLength;
		this->y *= invLength;
		this->z *= invLength;
	}

	vec3 vec3::GetNormalized() const
	{
		float invLength = 1.0f / this->Length();

		assert(!std::isinf(invLength), "Zero length vector cannot be normalized.");

		return vec3(x * invLength, y * invLength, z * invLength);
	}

	vec2 vec3::ToVec2() const
	{
		return vec2(this->x, this->y);
	}

#pragma endregion

#pragma region vector4

	vec4::vec4()
	{
	}

	vec4::vec4(const vec2 &xy, float Z, float W)
		: x(xy.x), y(xy.y), z(Z), w(W)
	{
	}

	vec4::vec4(const vec3 &xyz, float W) 
		: x(xyz.x), y(xyz.y), z(xyz.z), w(W)
	{
	}

	vec4::vec4(float X, float Y, float Z, float W) 
		: x(X), y(Y), z(Z), w(W)
	{
	}

	vec4::vec4(float val)
		: x(val), y(val), z(val), w(val)
	{
	}

	bool vec4::operator==(const vec4 &RHS) const
	{
		return (this->x == RHS.x) && (this->y == RHS.y) && (this->z == RHS.z) && (this->w == RHS.w);
	}

	bool vec4::operator!=(const vec4 &RHS) const
	{
		return (this->x != RHS.x) || (this->y != RHS.y) || (this->z != RHS.z) || (this->w != RHS.w);
	}

	vec4& vec4::operator=(const vec4 &RHS)
	{
		this->x = RHS.x;
		this->y = RHS.y;
		this->z = RHS.z;
		this->w = RHS.w;
		return *this;
	}

	vec4& vec4::operator-=(const vec4 &RHS)
	{
		this->x -= RHS.x;
		this->y -= RHS.y;
		this->z -= RHS.z;
		this->w -= RHS.w;
		return *this;
	}

	vec4& vec4::operator+=(const vec4 &RHS)
	{
		this->x += RHS.x;
		this->y += RHS.y;
		this->z += RHS.z;
		this->w += RHS.w;
		return *this;
	}

	vec4& vec4::operator*=(const vec4 &RHS)
	{
		this->x *= RHS.x;
		this->y *= RHS.y;
		this->z *= RHS.z;
		this->w *= RHS.w;
		return *this;
	}

	vec4& vec4::operator/=(const vec4 &RHS)
	{
		this->x /= RHS.x;
		this->y /= RHS.y;
		this->z /= RHS.z;
		this->w /= RHS.w;
		return *this;
	}

	vec4& vec4::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		this->w *= scalar;
		return *this;
	}

	vec4& vec4::operator/=(float divisor)
	{
		float inverse = 1.0f / divisor;
		this->x *= inverse;
		this->y *= inverse;
		this->z *= inverse;
		this->w *= inverse;
		return *this;
	}

	vec4 vec4::operator-(const vec4 &RHS) const
	{
		return vec4(x - RHS.x, y - RHS.y, z - RHS.z, w - RHS.w);
	}

	vec4 vec4::operator+(const vec4 &RHS) const
	{
		return vec4(x + RHS.x, y + RHS.y, z + RHS.z, w + RHS.w);
	}

	vec4 vec4::operator*(const vec4 &RHS) const
	{
		return vec4(x * RHS.x, y * RHS.y, z * RHS.z, w * RHS.w);
	}

	vec4 vec4::operator/(const vec4 &RHS) const
	{
		return vec4(x / RHS.x, y / RHS.y, z / RHS.z, w / RHS.w);
	}

	vec4 vec4::operator*(float scalar) const
	{
		return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	vec4 vec4::operator/(float divisor) const
	{
		float inverse = 1.0f / divisor;
		return vec4(x * inverse, y * inverse, z * inverse, w * inverse);
	}

	vec4 vec4::operator-() const
	{
		return vec4(-x, -y, -z, -w);
	}

	float vec4::operator[](unsigned int index) const
	{
		assert(index >= 0 && index < 4, "'index' must be in the range of [0, 3].");
		return *(&x + index);
	}

	float &vec4::operator[](unsigned int index)
	{
		assert(index >= 0 && index < 4, "'index' must be in the range of [0, 3].");
		return *(&x + index);
	}

	float vec4::Length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	float vec4::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void vec4::Normalize()
	{
		float invLength = 1.0f / this->Length();

		assert(!std::isinf(invLength), "Zero length vector cannot be normalized.");

		this->x *= invLength;
		this->y *= invLength;
		this->z *= invLength;
		this->w *= invLength;
	}

	vec4 vec4::GetNormalized() const
	{
		float invLength = 1.0f / this->Length();

		assert(!std::isinf(invLength), "Zero length vector cannot be normalized.");

		return vec4(x * invLength, y * invLength, z * invLength, w * invLength);
	}

	vec3 vec4::ToVec3() const
	{
		return vec3(this->x, this->y, this->z);
	}

#pragma endregion

	float Dot(const vec2 &v1, const vec2 &v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	float Dot(const vec3 &v1, const vec3 &v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	float Dot(const vec4 &v1, const vec4 &v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
	}

	float Distance(const vec2 &v1, const vec2 &v2)
	{
		return (v1 - v2).Length();
	}

	float Distance(const vec3 &v1, const vec3 &v2)
	{
		return (v1 - v2).Length();
	}

	float Distance(const vec4 &v1, const vec4 &v2)
	{
		return (v1 - v2).Length();
	}

	vec3 Cross(const vec3 &v1, const vec3 &v2)
	{
		return vec3(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}
}
