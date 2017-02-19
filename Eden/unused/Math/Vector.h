#pragma once
#include "Core/Platform.h"
#include "Core/Types.h"

namespace Math
{
	class Vec2;
	class Vec3;
	class Vec4;

	// ------------------------------------------------------------------------------------------------
	// Vector 2
	EDN_ALIGN16 class Vec2
	{
	public:
		float x, y;

		Vec2();
		Vec2(const Vec2& other);
		Vec2(float value); // explicit ?
		Vec2(float x, float y);

		Vec2& operator = (float value);
		Vec2& operator = (const Vec2& other);

		Vec2 operator - () const;
		Vec2 operator + (const Vec2& other) const;
		Vec2 operator - (const Vec2& other) const;
		Vec2 operator * (const Vec2& other) const;
		Vec2 operator / (const Vec2& other) const;

		Vec2 operator + (float value) const;
		Vec2 operator - (float value) const;
		Vec2 operator * (float value) const;
		Vec2 operator / (float value) const;

		friend Vec2 operator + (float value, const Vec2& other);
		friend Vec2 operator - (float value, const Vec2& other);
		friend Vec2 operator * (float value, const Vec2& other);
		friend Vec2 operator / (float value, const Vec2& other);

		Vec2& operator += (const Vec2& other);
		Vec2& operator -= (const Vec2& other);
		Vec2& operator *= (const Vec2& other);
		Vec2& operator /= (const Vec2& other);

		Vec2& operator += (float value);
		Vec2& operator -= (float value);
		Vec2& operator *= (float value);
		Vec2& operator /= (float value);

		Vec2& operator ++ ();
		Vec2& operator -- ();
		Vec2 operator ++ (int);
		Vec2 operator -- (int);

		bool operator == (const Vec2& other) const;
		bool operator != (const Vec2& other) const;

		float  operator [] (u32 index) const;
		float& operator [] (u32 index);

		float*       operator * ();
		const float* operator * () const;

		static const Vec2 Zero;
		static const Vec2 X;
		static const Vec2 Y;
		static const Vec2 One;
	};

	// ------------------------------------------------------------------------------------------------
	// Vector 3
	EDN_ALIGN16 class Vec3
	{
	public:
		union
		{
			struct { float x, y, z; };
			Vec2 xy;
		};

		Vec3();
		Vec3(const Vec3& other);
		Vec3(float value); // explicit ?
		Vec3(const Vec2& v2, float z);
		Vec3(float x, float y, float z);

		Vec3& operator = (float value);
		Vec3& operator = (const Vec3& other);

		Vec3 operator - () const;
		Vec3 operator + (const Vec3& other) const;
		Vec3 operator - (const Vec3& other) const;
		Vec3 operator * (const Vec3& other) const;
		Vec3 operator / (const Vec3& other) const;

		Vec3 operator + (float value) const;
		Vec3 operator - (float value) const;
		Vec3 operator * (float value) const;
		Vec3 operator / (float value) const;

		friend Vec3 operator + (float value, const Vec3& other);
		friend Vec3 operator - (float value, const Vec3& other);
		friend Vec3 operator * (float value, const Vec3& other);
		friend Vec3 operator / (float value, const Vec3& other);

		Vec3& operator += (const Vec3& other);
		Vec3& operator -= (const Vec3& other);
		Vec3& operator *= (const Vec3& other);
		Vec3& operator /= (const Vec3& other);

		Vec3& operator += (float value);
		Vec3& operator -= (float value);
		Vec3& operator *= (float value);
		Vec3& operator /= (float value);

		Vec3& operator ++ ();
		Vec3& operator -- ();
		Vec3 operator ++ (int);
		Vec3 operator -- (int);

		bool operator == (const Vec3& other) const;
		bool operator != (const Vec3& other) const;

		float  operator [] (u32 index) const;
		float& operator [] (u32 index);

		float*       operator * ();
		const float* operator * () const;

		static const Vec3 Zero;
		static const Vec3 X;
		static const Vec3 Y;
		static const Vec3 Z;
		static const Vec3 One;
	};

	// ------------------------------------------------------------------------------------------------
	// Vector 4
	EDN_ALIGN16 class Vec4
	{
	public:
		union
		{
			struct { float x, y, z, w; };
			Vec2 xy;
			Vec3 xyz;
		};

		Vec4();
		Vec4(const Vec4& other);
		Vec4(float value); // explicit ?
		Vec4(const Vec2& v2, float z, float w);
		Vec4(const Vec3& v3, float z);
		Vec4(float x, float y, float z, float w);

		Vec4& operator = (float value);
		Vec4& operator = (const Vec4& other);

		Vec4 operator - () const;
		Vec4 operator + (const Vec4& other) const;
		Vec4 operator - (const Vec4& other) const;
		Vec4 operator * (const Vec4& other) const;
		Vec4 operator / (const Vec4& other) const;

		Vec4 operator + (float value) const;
		Vec4 operator - (float value) const;
		Vec4 operator * (float value) const;
		Vec4 operator / (float value) const;

		friend Vec4 operator + (float value, const Vec4& other);
		friend Vec4 operator - (float value, const Vec4& other);
		friend Vec4 operator * (float value, const Vec4& other);
		friend Vec4 operator / (float value, const Vec4& other);

		Vec4& operator += (const Vec4& other);
		Vec4& operator -= (const Vec4& other);
		Vec4& operator *= (const Vec4& other);
		Vec4& operator /= (const Vec4& other);

		Vec4& operator += (float value);
		Vec4& operator -= (float value);
		Vec4& operator *= (float value);
		Vec4& operator /= (float value);

		Vec4& operator ++ ();
		Vec4& operator -- ();
		Vec4 operator ++ (int);
		Vec4 operator -- (int);

		bool operator == (const Vec4& other) const;
		bool operator != (const Vec4& other) const;

		float  operator [] (u32 index) const;
		float& operator [] (u32 index);

		float*       operator * ();
		const float* operator * () const;

		static const Vec4 Zero;
		static const Vec4 X;
		static const Vec4 Y;
		static const Vec4 Z;
		static const Vec4 W;
		static const Vec4 One;
	};

	// ------------------------------------------------------------------------------------------------
	// Vector Functions

}

#include "Vector.inl"