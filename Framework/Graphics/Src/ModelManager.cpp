#include "Precompiled.h"
#include "ModelManager.h"
#include "ModelIO.h"

using namespace CEngine::Graphics;

namespace
{
	std::unique_ptr<ModelManager> sModelManager;
}

void ModelManager::StaticInitialize()
{
	ASSERT(sModelManager == nullptr, "ModelManager -- System already initialized!");
	sModelManager = std::make_unique<ModelManager>();
}

void ModelManager::StaticTerminate()
{
	sModelManager.reset();
}

ModelManager* ModelManager::Get()
{
	ASSERT(sModelManager != nullptr, "ModelManager -- Is not initialized!");
	return sModelManager.get();
}

ModelID ModelManager::GetModelID(std::filesystem::path fileName)
{
	return std::filesystem::hash_value(fileName);
}

ModelID ModelManager::LoadModel(std::filesystem::path fileName)
{
	const auto modelID = GetModelID(fileName);
	auto [iter, success] = mIncentory.insert({ modelID, nullptr });
	if (success)
	{
		auto& modelPtr = iter->second;
		modelPtr = std::make_unique<Model>();
		ModelIO::LoadModel(fileName.c_str(), *modelPtr);
		ModelIO::LoadMaterial(fileName.c_str(), *modelPtr);
		ModelIO::LoadSkeleton(fileName.c_str(), *modelPtr);
		ModelIO::LoadAnimation(fileName.c_str(), *modelPtr);
	}

	return modelID;
}

void ModelManager::AddAnimation(ModelID id, std::filesystem::path fileName)
{
	auto model = mIncentory.find(id);
	if (model != mIncentory.end())
	{
		ModelIO::LoadAnimation(fileName.c_str(), *model->second);
	}
}

const Model* ModelManager::GetModel(ModelID id)
{
	auto model = mIncentory.find(id);
	if (model != mIncentory.end())
	{
		return model->second.get();
	}
	return nullptr;
}