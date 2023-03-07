#pragma once

namespace CEngine::Math
{
	struct Vector4
	{
		union { float x; float r; };
		union { float y; float g; };
		union { float z; float b; };
		union { float w; float a; };
		
		constexpr Vector4() noexcept : Vector4(0.0f) {}
		explicit constexpr Vector4(float f) noexcept : Vector4(f, f, f, f) {}
		// explicit means not allow
		// Vector4 v = 1.0f; or v(1.0f);
		constexpr Vector4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) {}
	};
}