#pragma once

#include "MeshTypes.h"

namespace CEngine::Graphics
{
	namespace MeshUtil
	{
		void ComputeNormal(Mesh& mesh)
		{
			for (auto& v : mesh.vertices)
			{
				v.normal = Math::Vector3::YAxis;
			}
		}
	}
}