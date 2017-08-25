#include <math.h>
#include <cassert>

namespace Math
{
	

#pragma region Vec2

	inline Vec2::Vec2()
		: x(0.0f)
		, y(0.0f)
	{
	}

	inline Vec2::Vec2(const Vec2& other)
		: x(other.x)
		, y(other.y)
	{
	}

	inline Vec2::Vec2(float value)
		: x(value)
		, y(value)
	{
	}

	inline Vec2::Vec2(float x, float y)
		: x(x)
		, y(y)
	{
	}

	inline Vec2& Vec2::operator = (float value)
	{
		x = value;
		y = value;
		return *this;
	}

	inline Vec2& Vec2::operator = (const Vec2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	inline Vec2 Vec2::operator - () const
	{
		return Vec2(-x, -y);
	}

	inline Vec2 Vec2::operator + (const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	inline Vec2 Vec2::operator - (const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	inline Vec2 Vec2::operator * (const Vec2& other) const
	{
		return Vec2(x * other.x, y * other.y);
	}

	inline Vec2 Vec2::operator / (const Vec2& other) const
	{
		//assert((other.x != 0 || other.y != 0) && "[Vec2] divide by zero");
		return Vec2(x / other.x, y / other.y);
	}

	inline Vec2 Vec2::operator + (float value) const
	{
		return Vec2(x + value, y + value);
	}

	inline Vec2 Vec2::operator - (float value) const
	{
		return Vec2(x - value, y - value);
	}

	inline Vec2 Vec2::operator * (float value) const
	{
		return Vec2(x * value, y * value);
	}

	inline Vec2 Vec2::operator / (float value) const
	{
		//assert(value != 0 && "[Vec2] divide by zero");
		return Vec2(x / value, y / value);
	}

	inline Vec2 operator + (float value, const Vec2& other)
	{
		return Vec2(value + other.x, value + other.y);
	}

	inline Vec2 operator - (float value, const Vec2& other)
	{
		return Vec2(value - other.x, value - other.y);
	}

	inline Vec2 operator * (float value, const Vec2& other)
	{
		return Vec2(value * other.x, value * other.y);
	}

	inline Vec2 operator / (float value, const Vec2& other)
	{
		//assert((other.x != 0 || other.y != 0) && "[Vec2] divide by zero");
		return Vec2(value / other.x, value / other.y);
	}

	inline Vec2& Vec2::operator += (const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline Vec2& Vec2::operator -= (const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline Vec2& Vec2::operator *= (const Vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	inline Vec2& Vec2::operator /= (const Vec2& other)
	{
		//assert((other.x != 0 || other.y != 0) && "[Vec2] divide by zero");
		x /= other.x;
		y /= other.y;
		return *this;
	}

	inline Vec2& Vec2::operator += (float value)
	{
		x += value;
		y += value;
		return *this;
	}

	inline Vec2& Vec2::operator -= (float value)
	{
		x -= value;
		y -= value;
		return *this;
	}

	inline Vec2& Vec2::operator *= (float value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	inline Vec2& Vec2::operator /= (float value)
	{
		//assert(value != 0 && "[Vec2] divide by zero");
		x /= value;
		y /= value;
		return *this;
	}

	inline Vec2& Vec2::operator ++ ()
	{
		x++;
		y++;
		return *this;
	}

	inline Vec2& Vec2::operator -- ()
	{
		x--;
		y--;
		return *this;
	}

	inline Vec2 Vec2::operator ++ (int)
	{
		auto result = Vec2(*this);
		++*this;
		return result;
	}

	inline Vec2 Vec2::operator -- (int)
	{
		auto result = Vec2(*this);
		--*this;
		return result;
	}

	inline bool Vec2::operator == (const Vec2& other) const
	{
		return x == other.x && y == other.y;
	}

	inline bool Vec2::operator != (const Vec2& other) const
	{
		return (x != other.x) || (y != other.y);
	}

	inline float Vec2::operator [] (u32 index) const
	{
		//assert(index < 2 && "'index' must be in the range of [0, 1]");
		return *(&x + index);
	}

	inline float& Vec2::operator [] (u32 index)
	{
		//assert(index < 2 && "'index' must be in the range of [0, 1]");
		return *(&x + index);
	}

	inline float* Vec2::operator * ()
	{
		return reinterpret_cast<float*>(this);
	}

	inline const float* Vec2::operator * () const
	{
		return reinterpret_cast<const float*>(this);
	}

#pragma endregion

#pragma region Vec3

	// ------------------------------------------------------------------------------------------------
	// Vector 3
	inline Vec3::Vec3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{
	}

	inline Vec3::Vec3(const Vec3& other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
	}

	inline Vec3::Vec3(float value)
		: x(value)
		, y(value)
		, z(value)
	{
	}

	inline Vec3::Vec3(const Vec2& v2, float z)
		: x(v2.x)
		, y(v2.y)
		, z(z)
	{
	}

	inline Vec3::Vec3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	inline Vec3& Vec3::operator = (float value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}

	inline Vec3& Vec3::operator = (const Vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	inline Vec3 Vec3::operator - () const
	{
		return Vec3(-x, -y, -z);
	}

	inline Vec3 Vec3::operator + (const Vec3& other) const
	{
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	inline Vec3 Vec3::operator - (const Vec3& other) const
	{
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	inline Vec3 Vec3::operator * (const Vec3& other) const
	{
		return Vec3(x * other.x, y * other.y, z * other.z);
	}

	inline Vec3 Vec3::operator / (const Vec3& other) const
	{
		//assert((other.x != 0 || other.y != 0 || other.z != 0) && "[Vec3] divide by zero");
		return Vec3(x / other.x, y / other.y, z / other.z);
	}

	inline Vec3 Vec3::operator + (float value) const
	{
		return Vec3(x + value, y + value, z + value);
	}

	inline Vec3 Vec3::operator - (float value) const
	{
		return Vec3(x - value, y - value, z - value);
	}

	inline Vec3 Vec3::operator * (float value) const
	{
		return Vec3(x * value, y * value, z * value);
	}

	inline Vec3 Vec3::operator / (float value) const
	{
		//assert(value != 0 && "[Vec3] divide by zero");
		return Vec3(x / value, y / value, z / value);
	}

	inline Vec3 operator + (float value, const Vec3& other)
	{
		return Vec3(value + other.x, value + other.y, value + other.z);
	}

	inline Vec3 operator - (float value, const Vec3& other)
	{
		return Vec3(value - other.x, value - other.y, value - other.z);
	}

	inline Vec3 operator * (float value, const Vec3& other)
	{
		return Vec3(value * other.x, value * other.y, value * other.z);
	}

	inline Vec3 operator / (float value, const Vec3& other)
	{
		//assert((other.x != 0 || other.y != 0 || other.z != 0) && "[Vec3] divide by zero");
		return Vec3(value / other.x, value / other.y, value / other.z);
	}

	inline Vec3& Vec3::operator += (const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline Vec3& Vec3::operator -= (const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vec3& Vec3::operator *= (const Vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	inline Vec3& Vec3::operator /= (const Vec3& other)
	{
		//assert((other.x != 0 || other.y != 0 || other.z != 0) && "[Vec3] divide by zero");
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	inline Vec3& Vec3::operator += (float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	inline Vec3& Vec3::operator -= (float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	inline Vec3& Vec3::operator *= (float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	inline Vec3& Vec3::operator /= (float value)
	{
		//assert(value != 0 && "[Vec3] divide by zero");
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	inline Vec3& Vec3::operator ++ ()
	{
		x++;
		y++;
		z++;
		return *this;
	}

	inline Vec3& Vec3::operator -- ()
	{
		x--;
		y--;
		z--;
		return *this;
	}

	inline Vec3 Vec3::operator ++ (int)
	{
		auto result = Vec3(*this);
		++*this;
		return result;
	}

	inline Vec3 Vec3::operator -- (int)
	{
		auto result = Vec3(*this);
		--*this;
		return result;
	}

	inline bool Vec3::operator == (const Vec3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	inline bool Vec3::operator != (const Vec3& other) const
	{
		return (x != other.x) || (y != other.y);
	}

	inline float Vec3::operator [] (u32 index) const
	{
		//assert(index < 3 && "'index' must be in the range of [0, 2]");
		return *(&x + index);
	}

	inline float& Vec3::operator [] (u32 index)
	{
		//assert(index < 3 && "'index' must be in the range of [0, 2]");
		return *(&x + index);
	}

	inline float* Vec3::operator * ()
	{
		return reinterpret_cast<float*>(this);
	}

	inline const float* Vec3::operator * () const
	{
		return reinterpret_cast<const float*>(this);
	}

#pragma endregion

#pragma region Vec4

	// ------------------------------------------------------------------------------------------------
	// Vector 4
	inline Vec4::Vec4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
	}

	inline Vec4::Vec4(const Vec4& other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
		, w(other.w)
	{
	}

	inline Vec4::Vec4(float value)
		: x(value)
		, y(value)
		, z(value)
		, w(value)
	{
	}

	inline Vec4::Vec4(const Vec2& v2, float z, float w)
		: x(v2.x)
		, y(v2.y)
		, z(z)
		, w(w)
	{
	}

	inline Vec4::Vec4(const Vec3& v3, float w)
		: x(v3.x)
		, y(v3.y)
		, z(v3.z)
		, w(w)
	{
	}

	inline Vec4::Vec4(float x, float y, float z, float w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
	}

	inline Vec4& Vec4::operator = (float value)
	{
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}

	inline Vec4& Vec4::operator = (const Vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	inline Vec4 Vec4::operator - () const
	{
		return Vec4(-x, -y, -z, -w);
	}

	inline Vec4 Vec4::operator + (const Vec4& other) const
	{
		return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	inline Vec4 Vec4::operator - (const Vec4& other) const
	{
		return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	inline Vec4 Vec4::operator * (const Vec4& other) const
	{
		return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	inline Vec4 Vec4::operator / (const Vec4& other) const
	{
		//assert((other.x != 0 || other.y != 0 || other.z != 0 || other.w != 0) && "[Vec4] divide by zero");
		return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
	}

	inline Vec4 Vec4::operator + (float value) const
	{
		return Vec4(x + value, y + value, z + value, w + value);
	}

	inline Vec4 Vec4::operator - (float value) const
	{
		return Vec4(x - value, y - value, z - value, w - value);
	}

	inline Vec4 Vec4::operator * (float value) const
	{
		return Vec4(x * value, y * value, z * value, w * value);
	}

	inline Vec4 Vec4::operator / (float value) const
	{
		//assert(value != 0 && "[Vec4] divide by zero");
		return Vec4(x / value, y / value, z / value, w / value);
	}

	inline Vec4 operator + (float value, const Vec4& other)
	{
		return Vec4(value + other.x, value + other.y, value + other.z, value + other.w);
	}

	inline Vec4 operator - (float value, const Vec4& other)
	{
		return Vec4(value - other.x, value - other.y, value - other.z, value - other.w);
	}

	inline Vec4 operator * (float value, const Vec4& other)
	{
		return Vec4(value * other.x, value * other.y, value * other.z, value * other.w);
	}

	inline Vec4 operator / (float value, const Vec4& other)
	{
		//assert((other.x != 0 || other.y != 0 || other.z != 0 || other.w != 0) && "[Vec4] divide by zero");
		return Vec4(value / other.x, value / other.y, value / other.z, value / other.w);
	}

	inline Vec4& Vec4::operator += (const Vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	inline Vec4& Vec4::operator -= (const Vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	inline Vec4& Vec4::operator *= (const Vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	inline Vec4& Vec4::operator /= (const Vec4& other)
	{
		//assert((other.x != 0 || other.y != 0 || other.z != 0 || other.w != 0) && "[Vec4] divide by zero");
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	inline Vec4& Vec4::operator += (float value)
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}

	inline Vec4& Vec4::operator -= (float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}

	inline Vec4& Vec4::operator *= (float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	inline Vec4& Vec4::operator /= (float value)
	{
		//assert(value != 0 && "[Vec4] divide by zero");
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	inline Vec4& Vec4::operator ++ ()
	{
		x++;
		y++;
		z++;
		w++;
		return *this;
	}

	inline Vec4& Vec4::operator -- ()
	{
		x--;
		y--;
		z--;
		w--;
		return *this;
	}

	inline Vec4 Vec4::operator ++ (int)
	{
		auto result = Vec4(*this);
		++*this;
		return result;
	}

	inline Vec4 Vec4::operator -- (int)
	{
		auto result = Vec4(*this);
		--*this;
		return result;
	}

	inline bool Vec4::operator == (const Vec4& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	inline bool Vec4::operator != (const Vec4& other) const
	{
		return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
	}

	inline float  Vec4::operator [] (u32 index) const
	{
		//assert(index < 3 && "'index' must be in the range of [0, 3]");
		return *(&x + index);
	}

	inline float& Vec4::operator [] (u32 index)
	{
		//assert(index < 3 && "'index' must be in the range of [0, 3]");
		return *(&x + index);
	}

	inline float* Vec4::operator * ()
	{
		return reinterpret_cast<float*>(this);
	}

	inline const float* Vec4::operator * () const
	{
		return reinterpret_cast<const float*>(this);
	}

#pragma endregion

	// ------------------------------------------------------------------------------------------------
	// Vector Functions

	

	// ------------------------------------------------------------------------------------------------
	// Helper functions

	inline float clamp(float value, float min, float max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}

	inline float min(float value, float min)
	{
		if (value < min)
			return min;
		return value;
	}

	inline float max(float value, float max)
	{
		if (value > max)
			return max;
		return value;
	}
}
