#ifndef H_MATH_VECTOR_H
#define H_MATH_VECTOR_H

namespace edn
{
	class vec2
	{
	public:
		vec2();
		vec2(float X, float Y);
		explicit vec2(float val);

		bool operator==(const vec2& RHS) const;
		bool operator!=(const vec2& RHS) const;

		vec2& operator=(const vec2& RHS);
		vec2& operator-=(const vec2& RHS);
		vec2& operator+=(const vec2& RHS);
		vec2& operator*=(const vec2& RHS);
		vec2& operator/=(const vec2& RHS);
		vec2& operator*=(float scalar);
		vec2& operator/=(float divisor);

		vec2 operator-(const vec2& RHS) const;
		vec2 operator+(const vec2& RHS) const;
		vec2 operator*(const vec2& RHS) const;
		vec2 operator/(const vec2& RHS) const;
		vec2 operator*(float scalar) const;
		vec2 operator/(float divisor) const;

		vec2 operator-() const;

		float operator[](unsigned int index) const;
		float &operator[](unsigned int index);

		static vec2 Zero() { return		vec2(0.0f, 0.0f); }
		static vec2 UnitX() { return	vec2(1.0f, 0.0f); }
		static vec2 UnitY() { return	vec2(0.0f, 1.0f); }
		static vec2 AllOnes() { return	vec2(1.0f, 1.0f); }

		float Length() const;
		float LengthSquared() const;
		void Normalize();
		vec2 GetNormalized() const;

		float x = 0.0f;
		float y = 0.0f;

	private:
	};


	class vec3
	{
	public:
		vec3();
		vec3(const vec2 &xy, float Z);
		vec3(float X, float Y, float Z);
		explicit vec3(float val);

		bool operator==(const vec3 &RHS) const;
		bool operator!=(const vec3 &RHS) const;

		vec3& operator=(const vec3 &RHS);
		vec3& operator-=(const vec3 &RHS);
		vec3& operator+=(const vec3 &RHS);
		vec3& operator*=(const vec3 &RHS);
		vec3& operator/=(const vec3 &RHS);
		vec3& operator*=(float scalar);
		vec3& operator/=(float divisor);

		vec3 operator-(const vec3 &RHS) const;
		vec3 operator+(const vec3 &RHS) const;
		vec3 operator*(const vec3 &RHS) const;
		vec3 operator/(const vec3 &RHS) const;
		vec3 operator*(float scalar) const;
		vec3 operator/(float divisor) const;

		vec3 operator-() const;

		float operator[](unsigned int index) const;
		float &operator[](unsigned int index);

		static vec3 Zero() { return		vec3(0.0f, 0.0f, 0.0f); }
		static vec3 UnitX() { return	vec3(1.0f, 0.0f, 0.0f); }
		static vec3 UnitY() { return	vec3(0.0f, 1.0f, 0.0f); }
		static vec3 UnitZ() { return	vec3(0.0f, 0.0f, 1.0f); }
		static vec3 AllOnes() { return	vec3(1.0f, 1.0f, 1.0f); }

		float Length() const;
		float LengthSquared() const;
		void Normalize();
		vec3 GetNormalized() const;
		vec2 ToVec2() const;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

	private:
	};


	class vec4
	{
	public:
		vec4();
		vec4(const vec3 &xyz, float W);
		vec4(const vec2 &xy, float Y, float W);
		vec4(float X, float Y, float Z, float W);
		explicit vec4(float val);

		bool operator==(const vec4 &RHS) const;
		bool operator!=(const vec4 &RHS) const;

		vec4& operator=(const vec4 &RHS);
		vec4& operator-=(const vec4 &RHS);
		vec4& operator+=(const vec4 &RHS);
		vec4& operator*=(const vec4 &RHS);
		vec4& operator/=(const vec4 &RHS);
		vec4& operator*=(float scalar);
		vec4& operator/=(float divisor);

		vec4 operator-(const vec4 &RHS) const;
		vec4 operator+(const vec4 &RHS) const;
		vec4 operator*(const vec4 &RHS) const;
		vec4 operator/(const vec4 &RHS) const;
		vec4 operator*(float scalar) const;
		vec4 operator/(float divisor) const;
		vec4 operator-() const;

		float operator[](unsigned int index) const;
		float &operator[](unsigned int index);

		static vec4 Zero() { return		vec4(0.0f, 0.0f, 0.0f, 0.0f); }
		static vec4 UnitX() { return	vec4(1.0f, 0.0f, 0.0f, 0.0f); }
		static vec4 UnitY() { return	vec4(0.0f, 1.0f, 0.0f, 0.0f); }
		static vec4 UnitZ() { return	vec4(0.0f, 0.0f, 1.0f, 0.0f); }
		static vec4 UnitW() { return	vec4(0.0f, 0.0f, 0.0f, 1.0f); }
		static vec4 AllOnes() { return	vec4(1.0f, 1.0f, 1.0f, 1.0f); }

		float Length() const;
		float LengthSquared() const;
		void Normalize();
		vec4 GetNormalized() const;
		vec3 ToVec3() const;

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

	private:
	};

	float Dot(const vec2 &v1, const vec2 &v2);
	float Dot(const vec3 &v1, const vec3 &v2);
	float Dot(const vec4 &v1, const vec4 &v2);
	float Distance(const vec2 &v1, const vec2 &v2);
	float Distance(const vec3 &v1, const vec3 &v2);
	float Distance(const vec4 &v1, const vec4 &v2);
	vec3 Cross(const vec3 &v1, const vec3 &v2);
}

#endif