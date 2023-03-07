#pragma once

namespace CEngine::Math
{
	struct Quaternion
	{
		float x, y, z, w;

		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		const static Quaternion Zero;
		const static Quaternion Indentity;

		Quaternion operator+(const Quaternion& rhs) const { return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
		Quaternion operator*(float s) const { return Quaternion(x * s, y * s, z * s, w * s); }
		Quaternion operator/(float s) const { return Quaternion(x / s, y / s, z / s, w / s); }

		Quaternion RotationAxis(const Vector3& axis, float rad);
		Quaternion MatrixToQuaternion(const Matrix4& m);
		Quaternion LookRotation(const Vector3& forward, const Vector3& up);
		Matrix4 MatrixRatationFromQuaternion(const Quaternion& q);

		static Quaternion Slerp(Quaternion q0, Quaternion q1, float t);
		static Quaternion Invert(const Quaternion& q);
		static Quaternion Conjugate(const Quaternion& q);
		static Quaternion QuaternionNormalize(const Quaternion& q);
	};
}