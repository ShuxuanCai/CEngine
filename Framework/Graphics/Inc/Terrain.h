#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "MeshTypes.h"
#include "Texture.h"

namespace CEngine::Graphics
{
	class Terrain final
	{
	public:
		void Initialize(std::filesystem::path fileName, float heightScale);

		float GetHeight(const Math::Vector3& position) const;

		Mesh mesh;

		size_t mRows = 0;
		size_t mColumns = 0;
	};
}