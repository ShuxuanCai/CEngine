#pragma once

namespace CEngine::Math
{
	struct OBB
	{
		Vector3 center = Vector3::Zero;			// Translation
		Vector3 extend = Vector3::One;			// Scale
		Quaternion rot = Quaternion::Indentity;  // Rotation
	};
}