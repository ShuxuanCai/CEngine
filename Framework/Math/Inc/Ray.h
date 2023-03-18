#pragma once

namespace CEngine::Math
{
	struct Ray
	{
		Vector3 origin = Vector3::Zero;
		Vector3 direction = Vector3::ZAxis;
	};
}