#pragma once

#include "Common.h"

namespace CEngine::Graphics
{
	struct Transform
	{
		Math::Vector3 position = Math::Vector3::Zero;
		Math::Quaternion rotation = Math::Quaternion::Indentity;
		Math::Vector3 scale = Math::Vector3::One;

		Math::Matrix4 GetMatrix4() const
		{
			return
				Math::Matrix4::Scaling(scale) *
				Math::Matrix4::RotationX(rotation.x) *
				Math::Matrix4::RotationY(rotation.y) *
				Math::Matrix4::RotationZ(rotation.z) *
				Math::Matrix4::Translation(position);
		}
	};
}