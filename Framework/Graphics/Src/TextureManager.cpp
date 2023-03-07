#include "Precompiled.h"
#include "TextureManager.h"

using namespace CEngine;
using namespace CEngine::Graphics;

namespace
{
	std::unique_ptr<TextureManager> sInstance;
}

void TextureManager::StaticInitialize(std::filesystem::path root)
{
	ASSERT(sInstance == nullptr, "TextureManager -- System already has instance");
	sInstance = std::make_unique<TextureManager>();
	sInstance->SetRootDirectory(root);
}

void TextureManager::StaticTerminate()
{
	sInstance.reset();
}

TextureManager* TextureManager::Get()
{
	ASSERT(sInstance != nullptr, "TextureManager -- No system registed");
	return sInstance.get();
}

TextureManager::~TextureManager()
{
	for (auto& [id, texture] : mInventory)
		texture->Terminate();
	mInventory.clear();
}

TextureId TextureManager::LoadTexture(std::filesystem::path fileName, bool useRootPath)
{
	auto textureId = std::filesystem::hash_value(fileName);
	auto [iter, success] = mInventory.insert({ textureId, nullptr });
	if (success)
	{
		auto& texturePtr = iter->second;
		texturePtr = std::make_unique<Texture>();
		texturePtr->Initialize((useRootPath) ? mRootDirectory / fileName : fileName);
	}
	return textureId;

	// Not good way, do not use this way
	// Because .find and .emplace need to traverse twice
	//auto iter = mInventory.find(textureId);
	//if (iter == mInventory.end())
	//{
	//	auto texture = std::make_unique<Texture>();
	//	texture->Initialize(fileName);
	//	mInventory.emplace(textureId, std::move(texture));
	//}
	//return textureId;
}

void TextureManager::BindVS(TextureId id, uint32_t slot) const
{
	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
		iter->second->BindVS(slot);
}

void TextureManager::BindPS(TextureId id, uint32_t slot) const
{
	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
		iter->second->BindPS(slot);
}