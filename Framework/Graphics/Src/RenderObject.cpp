#include "Precompiled.h"
#include "RenderObject.h"
#include "ModelManager.h"

using namespace CEngine::Graphics;

void RenderObject::Terminate()
{
	diffuseMapId = 0;
	specularMapId = 0;
	bumpMapId = 0;
	normalMapId = 0;
	meshBuffer.Terminate();
}

RenderGroup CEngine::Graphics::CreatingRenderGroup(ModelID id, const Animator* animator)
{
	auto model = ModelManager::Get()->GetModel(id);
	RenderGroup renderGroup;
	renderGroup.reserve(model->meshData.size());

	auto TryLoadTexture = [](const auto& textureName) -> TextureId
	{
		if (textureName.empty())
			return 0;

		return TextureManager::Get()->LoadTexture(textureName, false);
	};
	for (auto& meshData : model->meshData)
	{
		auto& renderObject = renderGroup.emplace_back();
		auto& materialData = model->materialData[meshData.materialIndex];
		renderObject.material = materialData.material;
		renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
		renderObject.bumpMapId = TryLoadTexture(materialData.bumpMapName);
		renderObject.normalMapId = TryLoadTexture(materialData.normalMapName);
		renderObject.specularMapId = TryLoadTexture(materialData.specularMapName);

		renderObject.meshBuffer.Initialize(meshData.mesh);

		renderObject.modelId = id;
		renderObject.skeleton = model->skeleton.get();
		renderObject.animator = animator;
	}

	return renderGroup;
}

void CEngine::Graphics::CleanUpRenderGroup(RenderGroup& renderGroup)
{
	for (auto& renderObject : renderGroup)
	{
		renderObject.Terminate();
	}
}