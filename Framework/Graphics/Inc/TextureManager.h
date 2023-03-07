#pragma once

#include "Texture.h"

namespace CEngine::Graphics
{
	using TextureId = std::size_t;

	class TextureManager
	{
	public:
		static void StaticInitialize(std::filesystem::path root);
		static void StaticTerminate();
		static TextureManager* Get();

	public:
		TextureManager() = default;
		~TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

		void SetRootDirectory(std::filesystem::path rood) { mRootDirectory = std::move(rood); }

		TextureId LoadTexture(std::filesystem::path fileName, bool useRootPath = true);

		void BindVS(TextureId id, uint32_t slot) const;
		void BindPS(TextureId id, uint32_t slot) const;

	private:
		using Inventory = std::unordered_map<TextureId, std::unique_ptr<Texture>>;
		Inventory mInventory;
		std::filesystem::path mRootDirectory;
	};
}

// array, linked list - sequential containers  random access(O(1))
// map, dictionary, hash tables - associative array

// arr[0]   Index/element pair
// arr[56]

// Contact List
// [Peter] - 111222333
// [Chris] - 898989898    key/element pair

// std::map - binary tree   O(log(N))

// std::unordered_map - hash tables, O(1), O(XN)
// "Peter Chan" (10 bytes) -> hashing -> turn to int (4 bytes)
// "Chris Cai" (9 bytes) -> hashing -> turn to int (4 bytes)
