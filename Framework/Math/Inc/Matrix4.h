#pragma once

namespace CEngine::Math
{
	struct Matrix4
	{
		union
		{
			struct // row+column subscript
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			std::array<float, 16> v;
		};

		constexpr Matrix4() noexcept
			: Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)
		{}

		constexpr Matrix4(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44
		) noexcept
			: _11(_11), _12(_12), _13(_13), _14(_14)
			, _21(_21), _22(_22), _23(_23), _24(_24)
			, _31(_31), _32(_32), _33(_33), _34(_34)
			, _41(_41), _42(_42), _43(_43), _44(_44)
		{}

		const static Matrix4 Identity()
		{
			return { 1.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f };
		}

		constexpr Matrix4 GetMatrix4()
		{
			return { _11, _12, _13, _14,
					 _21, _22, _23, _24,
					 _31, _32, _33, _34,
					 _41, _42, _43, _44 };
		}

		static Matrix4 Translation(const Vector3& d)
		{
			return { 1.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 1.0f, 0.0f,
					 d.x , d.y , d.z , 1.0f };
		}

		static Matrix4 RotationX(float rad)
		{
			return { 1.0f, 0.0f     , 0.0f     , 0.0f,
					 0.0f, cos(rad) , sin(rad) , 0.0f,
					 0.0f, -sin(rad), cos(rad) , 0.0f,
					 0.0f, 0.0f     , 0.0f     , 1.0f };
		}

		static Matrix4 RotationY(float rad)
		{
			return { cos(rad), 0.0f, -sin(rad), 0.0f,
					 0.0f    , 1.0f, 0.0f     , 0.0f,
					 sin(rad), 0.0f, cos(rad) , 0.0f,
					 0.0f    , 0.0f, 0.0f     , 1.0f };
		}

		static Matrix4 RotationZ(float rad)
		{
			return { cos(rad) , sin(rad), 0.0f, 0.0f,
					 -sin(rad), cos(rad), 0.0f, 0.0f,
					 0.0f     , 0.0f    , 1.0f, 0.0f,
					 0.0f     , 0.0f    , 0.0f, 1.0f };
		}

		static Matrix4 Scaling(float s)
		{
			return {  s  , 0.0f, 0.0f, 0.0f,
					 0.0f,  s  , 0.0f, 0.0f,
					 0.0f, 0.0f,  s  , 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f };
		}

		static Matrix4 Scaling(const Vector3& s)
		{
			return { s.x , 0.0f, 0.0f, 0.0f,
					 0.0f, s.y , 0.0f, 0.0f,
					 0.0f, 0.0f, s.z , 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f };
		}

		constexpr Matrix4 operator*(float s) const
		{
			/*return { _11 * s, _12 * s, _13 * s, _14 * s,
			         _21 * s, _22 * s, _23 * s, _24 * s,
			         _31 * s, _32 * s, _33 * s, _34 * s,
			         _41 * s, _42 * s, _43 * s, _44 * s };*/

			Matrix4 m;
			for (int i = 0; i < 16; ++i)
			{
				m.v[i] = v[i] * s;
			}
			return m;
		}

		constexpr Matrix4 operator+(const Matrix4& rhs) const
		{
			Matrix4 m;
			for (int i = 0; i < 16; ++i)
			{
				m.v[i] = v[i] + rhs.v[i];
			}
			return m;
		}

		constexpr Matrix4 operator*(const Matrix4& rhs) const
		{
			Matrix4 m;
			m.v[0] = v[0] * rhs.v[0] + v[1] * rhs.v[4] + v[2] * rhs.v[8] + v[3] * rhs.v[12];
			m.v[1] = v[0] * rhs.v[1] + v[1] * rhs.v[5] + v[2] * rhs.v[9] + v[3] * rhs.v[13];
			m.v[2] = v[0] * rhs.v[2] + v[1] * rhs.v[6] + v[2] * rhs.v[10] + v[3] * rhs.v[14];
			m.v[3] = v[0] * rhs.v[3] + v[1] * rhs.v[7] + v[2] * rhs.v[11] + v[3] * rhs.v[15];
			m.v[4] = v[4] * rhs.v[0] + v[5] * rhs.v[4] + v[6] * rhs.v[8] + v[7] * rhs.v[12];
			m.v[5] = v[4] * rhs.v[1] + v[5] * rhs.v[5] + v[6] * rhs.v[9] + v[7] * rhs.v[13];
			m.v[6] = v[4] * rhs.v[2] + v[5] * rhs.v[6] + v[6] * rhs.v[10] + v[7] * rhs.v[14];
			m.v[7] = v[4] * rhs.v[3] + v[5] * rhs.v[7] + v[6] * rhs.v[11] + v[7] * rhs.v[15];
			m.v[8] = v[8] * rhs.v[0] + v[9] * rhs.v[4] + v[10] * rhs.v[8] + v[11] * rhs.v[12];
			m.v[9] = v[8] * rhs.v[1] + v[9] * rhs.v[5] + v[10] * rhs.v[9] + v[11] * rhs.v[13];
			m.v[10] = v[8] * rhs.v[2] + v[9] * rhs.v[6] + v[10] * rhs.v[10] + v[11] * rhs.v[14];
			m.v[11] = v[8] * rhs.v[3] + v[9] * rhs.v[7] + v[10] * rhs.v[11] + v[11] * rhs.v[15];
			m.v[12] = v[12] * rhs.v[0] + v[13] * rhs.v[4] + v[14] * rhs.v[8] + v[15] * rhs.v[12];
			m.v[13] = v[12] * rhs.v[1] + v[13] * rhs.v[5] + v[14] * rhs.v[9] + v[15] * rhs.v[13];
			m.v[14] = v[12] * rhs.v[2] + v[13] * rhs.v[6] + v[14] * rhs.v[10] + v[15] * rhs.v[14];
			m.v[15] = v[12] * rhs.v[3] + v[13] * rhs.v[7] + v[14] * rhs.v[11] + v[15] * rhs.v[15];
			return m;
		}

		static Matrix4 RotationAxis(const Vector3& axis, float rad);
		//static Matrix4 RotationQuaternion(const Quaternion& q);
	};
}