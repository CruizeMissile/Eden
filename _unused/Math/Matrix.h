#pragma once

#include "Math/Vector.h"

namespace Math
{
	class Quat 
	{
	public:
		float x, y, z, w;
	};

	class Mat4
	{
	public:

		union
		{
			f32 f[16];
			//Vec4 v[4];
			//struct { Vec4 v1, v2, v3, v4; };
		};

		Mat4();
		Mat4(float headingDegrees, float pitchDegrees, float rollDegrees);
		Mat4(const Quat& rotation);
		Mat4(const Quat& rotation, const Vec3& translation);
		Mat4(const Quat& rotation, const Vec4& translation);
		Mat4(const Mat4& other);
		Mat4(const Vec3& right, const Vec3& up, const Vec3& forward, const Vec3& position);
		Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3);
		Mat4(float m00, float m01, float m02, float m03,
			 float m10, float m11, float m12, float m13,
			 float m20, float m21, float m22, float m23,
			 float m30, float m31, float m32, float m33);

		// Computes the inverse assuming standard homogeneous matrix format
		void fastInverse();
		void inverse();
		void transpose();
		float determinant() const;

		void scale(float scale);
		void scale(const Vec3& scale);
		void scale(const Vec4* scale);
		void scale(float scaleX, float scaleY, float scaleZ);

		void rotate(const Vec3& axis, float degress);
		void rotate(const Vec4& axis, float degress);
		void rotateX(float degrees);
		void rotateY(float degrees);
		void rotateZ(float degrees);

		void translate(const Vec3& translation);
		void translate(const Vec4& translation);
		void translate(float translateX, float translateY, float translateZ);



		static Mat4 Identity;
	};
}
