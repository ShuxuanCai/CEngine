#pragma once

#include "Common.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"

#include "Random.h"

#include "Constant.h"

#include "AABB.h"
#include "Sphere.h"
#include "OBB.h"
#include "Plane.h"
#include "Ray.h"

namespace CEngine::Math
{
	// TODO: Add your free functions here
	// use constexpr whenever possible, otherwise use inline
	// normalize, cross, dot...

	template <class T>
	constexpr T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <class T>
	constexpr T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <class T>
	constexpr T Clamp(T value, T min, T max)
	{
		return Max(min, Min(max, value));
	}

	template <class T>
	constexpr T Lerp(T a, T b, float t)
	{
		return a + (b - a) * t;
	}

	template <class T>
	constexpr T Abs(T value)
	{
		return value >= 0 ? value : -value;
	}

	template <class T>
	constexpr T Sqr(T value)
	{
		return value * value;
	}

	constexpr float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline float Magnitude(const Vector3& v)
	{
		return sqrt(MagnitudeSqr(v));
	}

	inline float Magnitude(const Quaternion& q) 
	{ 
		return sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w)); 
	}

	constexpr float DistanceSqr(const Vector3& a, const Vector3& b)
	{
		return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}

	inline float Distance(const Vector3& a, const Vector3& b)
	{
		return sqrt(DistanceSqr(a, b));
	}

	inline Vector3 Normalize(const Vector3& v)
	{
		return v / Magnitude(v);
	}

	inline Quaternion Normalize(const Quaternion& q) 
	{ 
		return q / Magnitude(q); 
	}

	inline Quaternion Lerp(Quaternion q0, Quaternion q1, float t) 
	{ 
		return q0 * (1.0f - t) + (q1 * t); 
	}

	constexpr Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 n;
		n.x = a.y * b.z - a.z * b.y;
		n.y = a.z * b.x - a.x * b.z;
		n.z = a.x * b.y - a.y * b.x;
		return n;
	}



	constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		float den = (v.x * m.v[3]) + (v.y * m.v[7]) + (v.z * m.v[11]) + m.v[15];
		float c = 1; // ???
		if (den != 0)
			c = 1.0f / den;
		Vector3 v3;
		v3.x = c * ((v.x * m.v[0]) + (v.y * m.v[4]) + (v.z * m.v[8]) + m.v[12]);
		v3.y = c * ((v.x * m.v[1]) + (v.y * m.v[5]) + (v.z * m.v[9]) + m.v[13]);
		v3.z = c * ((v.x * m.v[2]) + (v.y * m.v[6]) + (v.z * m.v[10]) + m.v[14]);
		return v3;
	}

	constexpr Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
	{
		Vector3 v3;
		v3.x = (v.x * m.v[0]) + (v.y * m.v[4]) + (v.z * m.v[8]);
		v3.y = (v.x * m.v[1]) + (v.y * m.v[5]) + (v.z * m.v[9]);
		v3.z = (v.x * m.v[2]) + (v.y * m.v[6]) + (v.z * m.v[10]);
		return v3;
	}

	constexpr float Determinant(const Matrix4& m)
	{
		float firstVal = m.v[0] * (m.v[5] * (m.v[10] * m.v[15] - m.v[11] * m.v[14]) - m.v[6] * (m.v[9] * m.v[15] - m.v[11] * m.v[13]) + m.v[7] * (m.v[9] * m.v[14] - m.v[10] * m.v[13]));
		float secondVal = m.v[1] * (m.v[4] * (m.v[10] * m.v[15] - m.v[11] * m.v[14]) - m.v[6] * (m.v[8] * m.v[15] - m.v[11] * m.v[12]) + m.v[7] * (m.v[8] * m.v[14] - m.v[10] * m.v[12]));
		float thirdVal = m.v[2] * (m.v[4] * (m.v[9] * m.v[15] - m.v[11] * m.v[13]) - m.v[5] * (m.v[8] * m.v[15] - m.v[11] * m.v[12]) + m.v[7] * (m.v[8] * m.v[13] - m.v[9] * m.v[12]));
		float fourthVal = m.v[3] * (m.v[4] * (m.v[9] * m.v[14] - m.v[10] * m.v[13]) - m.v[5] * (m.v[8] * m.v[14] - m.v[10] * m.v[12]) + m.v[6] * (m.v[8] * m.v[13] - m.v[9] * m.v[12]));
		float val = firstVal - secondVal + thirdVal - fourthVal;
		return val;
	}

	constexpr Matrix4 Transpose(const Matrix4& m)
	{
		return { m.v[0], m.v[4], m.v[8], m.v[12], m.v[1], m.v[5], m.v[9], m.v[13], m.v[2], m.v[6], m.v[10], m.v[14], m.v[3], m.v[7], m.v[11], m.v[15] };
	}

	constexpr Matrix4 Adjoint(const Matrix4& m)
	{
		Matrix4 mat;
		mat.v[0] = (m.v[5] * (m.v[10] * m.v[15] - m.v[11] * m.v[14]) - m.v[6] * (m.v[9] * m.v[15] - m.v[11] * m.v[13]) + m.v[7] * (m.v[9] * m.v[14] - m.v[10] * m.v[13]));
		mat.v[1] = -(m.v[4] * (m.v[10] * m.v[15] - m.v[11] * m.v[14]) - m.v[6] * (m.v[8] * m.v[15] - m.v[11] * m.v[12]) + m.v[7] * (m.v[8] * m.v[14] - m.v[10] * m.v[12]));
		mat.v[2] = (m.v[4] * (m.v[9] * m.v[15] - m.v[11] * m.v[13]) - m.v[5] * (m.v[8] * m.v[15] - m.v[11] * m.v[12]) + m.v[7] * (m.v[8] * m.v[13] - m.v[9] * m.v[12]));
		mat.v[3] = -(m.v[4] * (m.v[9] * m.v[14] - m.v[10] * m.v[13]) - m.v[5] * (m.v[8] * m.v[14] - m.v[10] * m.v[12]) + m.v[6] * (m.v[8] * m.v[13] - m.v[9] * m.v[12]));
		mat.v[4] = -(m.v[1] * (m.v[10] * m.v[15] - m.v[11] * m.v[14]) - m.v[2] * (m.v[9] * m.v[15] - m.v[11] * m.v[13]) + m.v[3] * (m.v[9] * m.v[14] - m.v[10] * m.v[13]));
		mat.v[5] = (m.v[0] * (m.v[10] * m.v[15] - m.v[11] * m.v[14]) - m.v[2] * (m.v[8] * m.v[15] - m.v[11] * m.v[12]) + m.v[3] * (m.v[8] * m.v[14] - m.v[10] * m.v[12]));
		mat.v[6] = -(m.v[0] * (m.v[9] * m.v[15] - m.v[11] * m.v[13]) - m.v[1] * (m.v[8] * m.v[15] - m.v[11] * m.v[12]) + m.v[3] * (m.v[8] * m.v[13] - m.v[9] * m.v[12]));
		mat.v[7] = (m.v[0] * (m.v[9] * m.v[14] - m.v[10] * m.v[13]) - m.v[1] * (m.v[8] * m.v[14] - m.v[10] * m.v[12]) + m.v[2] * (m.v[8] * m.v[13] - m.v[9] * m.v[12]));
		mat.v[8] = (m.v[1] * (m.v[6] * m.v[15] - m.v[7] * m.v[14]) - m.v[2] * (m.v[5] * m.v[15] - m.v[7] * m.v[13]) + m.v[3] * (m.v[5] * m.v[14] - m.v[6] * m.v[13]));
		mat.v[9] = -(m.v[0] * (m.v[6] * m.v[15] - m.v[7] * m.v[14]) - m.v[2] * (m.v[4] * m.v[15] - m.v[7] * m.v[12]) + m.v[3] * (m.v[4] * m.v[14] - m.v[6] * m.v[12]));
		mat.v[10] = (m.v[0] * (m.v[5] * m.v[15] - m.v[7] * m.v[13]) - m.v[1] * (m.v[4] * m.v[15] - m.v[7] * m.v[12]) + m.v[3] * (m.v[4] * m.v[13] - m.v[5] * m.v[12]));
		mat.v[11] = -(m.v[0] * (m.v[5] * m.v[14] - m.v[6] * m.v[13]) - m.v[1] * (m.v[4] * m.v[14] - m.v[6] * m.v[12]) + m.v[2] * (m.v[4] * m.v[13] - m.v[5] * m.v[12]));
		mat.v[12] = -(m.v[1] * (m.v[6] * m.v[11] - m.v[7] * m.v[10]) - m.v[2] * (m.v[5] * m.v[11] - m.v[7] * m.v[9]) + m.v[3] * (m.v[5] * m.v[10] - m.v[6] * m.v[9]));
		mat.v[13] = (m.v[0] * (m.v[6] * m.v[11] - m.v[7] * m.v[10]) - m.v[2] * (m.v[4] * m.v[11] - m.v[7] * m.v[8]) + m.v[3] * (m.v[4] * m.v[10] - m.v[6] * m.v[8]));
		mat.v[14] = -(m.v[0] * (m.v[5] * m.v[11] - m.v[7] * m.v[9]) - m.v[1] * (m.v[4] * m.v[11] - m.v[7] * m.v[8]) + m.v[3] * (m.v[4] * m.v[9] - m.v[5] * m.v[8]));
		mat.v[15] = (m.v[0] * (m.v[5] * m.v[10] - m.v[6] * m.v[9]) - m.v[1] * (m.v[4] * m.v[10] - m.v[6] * m.v[8]) + m.v[2] * (m.v[4] * m.v[9] - m.v[5] * m.v[8]));
		Matrix4 mat2 = Transpose(mat);
		return mat2;
	}

	constexpr Matrix4 Inverse(const Matrix4& m)
	{
		Matrix4 mat;
		mat = Adjoint(m) * (1 / Determinant(m));
		return mat;
	}

	inline Vector3 GetRight(const Matrix4& m)
	{
		return { m._11, m._12, m._13 };
	}

	inline Vector3 GetUp(const Matrix4& m)
	{
		return { m._21, m._22, m._23 };
	}

	inline Vector3 GetForwards(const Matrix4& m)
	{
		return { m._31, m._32, m._33 };
	}

	inline Vector3 GetTranslation(const Matrix4& m)
	{
		return { m._41, m._42, m._43 };
	}

	inline Matrix4 RotationAxis(const Vector3& axis, float rad);
	inline Matrix4 RotationQuaternion(const Math::Quaternion& q);

	bool Intersect(const Ray& ray, const Plane& plane, float& distance);
	bool IsContained(const Vector3& point, const AABB& aabb);
	bool IsContained(const Vector3& point, const OBB& obb);
	bool GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal);
}