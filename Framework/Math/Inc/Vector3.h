#pragma once

// 1 byte -> 8 bits
// int -> 4 bytes -> 32 bits
// float -> 4 bytes -> 32 bits
// char -> 1 byte -> 0 to 255 (256 values)
// bool -> 1 byte -> true/false, 0 or 1

// under 32 bits systems, address are in 32 bits -> pointer size
// store address range from 0 to 2^32 (4294967296)

// signed bit is not a good approach to store values in integer
// 2's complement

// float -> 32 bit
// [sign(1b)][exponent(8b)][mantissa923b)]
// +/- Base * 10 ^ Exp

// const allow initialization and block assignment


// Memory Alignment???
// sizeof(Vector3) -> 4 bytes * 3 = 12 bytes
// sizeof(Vector3) -> 4 bytes (x or y or z) using union

// explicit???

namespace CEngine::Math
{
	//template <class T>
	struct Vector3
	{
		union
		{
			struct { float x, y, z; };
			std::array<float, 3> v; // same as float v[3], but much better
		};

		// constexpr -> constant expression
		// expression is something that evaluates to a single value of a single type
		
		constexpr Vector3() noexcept : Vector3(0.0f) {}
		explicit constexpr Vector3(float f) noexcept : Vector3(f, f, f) {}
		constexpr Vector3(float x, float y, float z) 
			noexcept : x(x) // Initialization
			, y(y)
			, z(z)
		{
			// can not use this way (Initialization is much better than assignment)
			//x = 0.0f;  // assignment
			//y = 0.0f;
			//z = 0.0f;
		}		

		// Commonly used vectors
		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 XAxis;
		const static Vector3 YAxis;
		const static Vector3 ZAxis;

		constexpr Vector3 operator-() const { return { -x, -y, -z }; }
		constexpr Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		constexpr Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		constexpr Vector3 operator*(const float v) const { return Vector3(x * v, y * v, z * v); }
		constexpr Vector3 operator/(const float v) const { return Vector3(x / v, y / v, z / v); }

		Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z;  return *this; }
		Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z;  return *this; }
		Vector3& operator*=(const float& v) { x *= v; y *= v; z *= v;  return *this; }
		Vector3& operator/=(const float& v) { x /= v; y /= v; z /= v;  return *this; }
	};

	//void Test()
	//{
	//	Vector3 v;
	//	v.x = 3.14f; // or v.v[0]
	//}
}

