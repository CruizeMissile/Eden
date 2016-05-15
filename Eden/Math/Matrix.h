#pragma once

namespace edn
{
	class vec2;
	class vec3;
	class vec4;
	class mat4;
	class quat;

	class mat3
	{
	public:
		enum //Indexes
		{
			RightX = 0, UpX = 3, ForwardX = 6, 
			RightY = 1, UpY = 4, ForwardY = 7,
			RightZ = 2, UpZ = 5, ForwardZ = 8
		};

		mat3();
		mat3(const quat &rotation);
		//- Extracts the rotational component from the 4x4 matrix
		mat3(const mat4 &mat);
		mat3(const vec3 &right, const vec3 &up, const vec3 &forward);
		mat3(float f0, float f3, float f6, 
			float f1, float f4, float f7, 
			float f2, float f5, float f8);
		~mat3() = default;

		mat3 &operator=(const mat3 &M);
		mat3 &operator*=(const mat3 &M);
		mat3 &operator*=(float scalar);
		mat3 &operator+=(const mat3 &M);
		mat3 &operator-=(const mat3 &M);
		mat3 operator*(const mat3 &M) const;
		mat3 operator+(const mat3 &M) const;
		mat3 operator-(const mat3 &M) const;
		vec3 operator*(const vec3 &V) const;
		mat3 operator*(float scalar) const;
		mat3 operator/(float scalar) const;
		mat3 operator-() const;
		float operator[](unsigned int index) const;
		float &operator[](unsigned int index);

		void SetIdentity();
		void Transpose();
		void Inverse();
		void Flood(float value);
		mat3 GetTranspose() const;
		mat3 GetInverse() const;
		float GetDet() const;

		void Scale(float scaleX, float scaleY, float scaleZ);
		void Scale(const vec3 &scale);
		void Scale(float scale);

		void Rotate(float axisX, float axisY, float axisZ, float degrees);
		void Rotate(const vec3 &axis, float degrees);
		void RotateX(float degrees);
		void RotateY(float degrees);
		void RotateZ(float degrees);

		void SetRightVec(const vec3 &V);
		void SetRightVec(float x, float y, float z);
		void SetUpVec(const vec3 &V);
		void SetUpVec(float x, float y, float z);
		void SetForwardVec(const vec3 &V);
		void SetForwardVec(float x, float y, float z);

		vec3 GetRightVec() const;
		vec3 GetUpVec() const;
		vec3 GetForwardVec() const;

		static mat3 Identity();

		void Set(float f0, float f3, float f6,
			float f1, float f4, float f7,
			float f2, float f5, float f8);

		float data[9];

	private:
	};

	class mat4
	{
	public:
		enum //Indexes
		{
			RightX = 0, UpX = 4, ForwardX = 8,  TransX = 12,
			RightY = 1, UpY = 5, ForwardY = 9,  TransY = 13,
			RightZ = 2, UpZ = 6, ForwardZ = 10, TransZ = 14,
			W0     = 3, W1  = 7, W2       = 11,	W3   = 15
		};

		mat4();
		mat4(const quat &rotation);
		mat4(const quat &rotation, const vec3 &translation);
		mat4(const mat3 &rotation);
		mat4(const mat3 &rotation, const vec3 &translation);
		mat4(const vec3 &right, const vec3 &up, const vec3 &forward, const vec4 &translation);
		mat4(float f0, float f4, float f8, float f12, 
			float f1, float f5, float f9, float f13, 
			float f2, float f6, float f10, float f14, 
			float f3, float f7, float f11, float f15);
		~mat4() = default;

		mat4 &operator=(const mat4 &M);
		mat4 &operator*=(const mat4 &M);
		mat4 &operator*=(float scalar);
		mat4 &operator+=(const mat4 &M);
		mat4 &operator-=(const mat4 &M);
		mat4 operator*(const mat4 &M) const;
		mat4 operator+(const mat4 &M) const;
		mat4 operator-(const mat4 &M) const;
		vec4 operator*(const vec4 &V) const;
		mat4 operator*(float scalar) const;
		mat4 operator/(float scalar) const;
		mat4 operator-() const;
		float operator[](unsigned int index) const;
		float &operator[](unsigned int index);

		void SetIdentity();
		void Transpose();
		void Inverse();
		//- Computes the inverse assuming standard homogeneous matrix format
		//- [ R		T ]
		//- [ 0 0 0 1 ]
		void FastInverse();
		void Flood(float value);
		mat4 GetTranspose() const;
		mat4 GetInverse() const;
		//- Computes the inverse assuming standard homogeneous matrix format
		//- [ R		T ]
		//- [ 0 0 0 1 ]
		mat4 GetFastInverse() const;

		void Scale(float scaleX, float scaleY, float scaleZ);
		void Scale(const vec3 &scale);
		void Scale(float scale);

		void Rotate(float axisX, float axisY, float axisZ, float degrees);
		void Rotate(const vec3 &axis, float degrees);
		void RotateX(float degrees);
		void RotateY(float degrees);
		void RotateZ(float degrees);

		void Translate(const vec3 &translation);
		void Translate(float translationX, float translationY, float translationZ);

		void FrustumProjection(float fovyDegrees, float aspect, float zNear, float zFar);
		void FrustumProjection(float fovyDegrees, float aspect, float zNear, float zFar, mat4 &outInverse);
		void OrthoProjection(float top, float bottom, float left, float right, float near, float far);
		void OrthoProjection(float top, float bottom, float left, float right, float near, float far, mat4 &outInverse);
		void LookAt(const vec3 &position, const vec3 &target, const vec3 &upVector);

		void SetRightVec(const vec3 &V);
		void SetRightVec(float x, float y, float z);
		void SetUpVec(const vec3 &V);
		void SetUpVec(float x, float y, float z);
		void SetForwardVec(const vec3 &V);
		void SetForwardVec(float x, float y, float z);
		void SetTranslationVec(const vec3 &V);
		void SetTranslationVec(float x, float y, float z);

		vec3 GetRightVec() const;
		vec3 GetUpVec() const;
		vec3 GetForwardVec() const;
		vec3 GetTranslationVec() const;

		static mat4 Identity();

		void Set(float f0, float f4, float f8, float f12,
			float f1, float f5, float f9, float f13,
			float f2, float f6, float f10, float f14,
			float f3, float f7, float f11, float f15);

		float data[16];

	private:
	};
}
