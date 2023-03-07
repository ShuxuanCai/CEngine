#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Skeleton.h"
#include "Animator.h"
#include "ModelManager.h"

namespace CEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;

		Material material;

		TextureId diffuseMapId;
		TextureId specularMapId;
		TextureId bumpMapId;
		TextureId normalMapId;

		MeshBuffer meshBuffer;

		ModelID modelId = 0;
		const Skeleton* skeleton = nullptr;
		const Animator* animator = nullptr;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreatingRenderGroup(ModelID id, const Animator* animator = nullptr);
	void CleanUpRenderGroup(RenderGroup& renderGroup);

	template <class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (auto& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}
