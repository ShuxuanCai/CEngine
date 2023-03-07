#include "Precompiled.h"
#include "GameWorld.h"

#include "CameraService.h"
#include "RenderService.h"
#include "PhysicsService.h"

#include "TransformComponent.h"

using namespace CEngine;

namespace
{
	CustomService TryServiceMake;
}

void GameWorld::SetCustomServiceMake(CustomService customService)
{
	TryServiceMake = customService;
}

void GameWorld::Initialize(uint32_t capacity)
{
	ASSERT(!mInitialized, "GameWorld is already initialized!");
	mInitialized = true;

	for (auto& service : mServices)
	{
		service->Initialize();
	}

	mGameObjectSlots.resize(capacity);
	mFreeSlots.resize(capacity);
	std::iota(mFreeSlots.rbegin(), mFreeSlots.rend(), 0);
}

void GameWorld::Terminate()
{
	ASSERT(!mUpdating, "GameWorld can't terminate while updating");

	if (!mInitialized)
	{
		return;
	}

	for (auto gameObject : mUpdateLists)
	{
		DestroyGameObject(gameObject->GetHandle());
	}
	ProcessDestroyList();
	ASSERT(mUpdateLists.empty(), "GameWorld failed to clean up all game objects");

	for (auto& service : mServices)
	{
		service->Terminate();
	}

	mInitialized = false;
}

void GameWorld::Update(float deltaTime)
{
	if (Input::InputSystem::Get()->IsKeyPressed(Input::KeyCode::SPACE))
	{
		CreateGameObject("../../Assets/Templates/test_player.json");
	}

	mUpdating = true;
	for (auto& service : mServices)
	{
		service->Update(deltaTime);
	}

	for (size_t i = 0; i < mUpdateLists.size(); ++i)
	{
		GameObject* gameObject = mUpdateLists[i];
		gameObject->Update(deltaTime);
	}
	mUpdating = false;

	ProcessDestroyList();
}

void GameWorld::Render()
{
	for (auto& service : mServices)
	{
		service->Render();
	}
}

void GameWorld::DebugUI()
{
	ImGui::Begin("Services: ", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	for (auto& service : mServices)
	{
		service->DebugUI();
	}

	ImGui::End();
}

void GameWorld::LoadLevel(const std::filesystem::path& levelFile)
{
	static float shiftX = 0.0f;

	FILE* file = nullptr;
	auto err = fopen_s(&file, levelFile.u8string().c_str(), "r");
	ASSERT(err == 0 && file != nullptr, "GameWorld -- failed to open level file %s", levelFile.u8string().c_str());

	char readBuffer[65536];
	rapidjson::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));

	fclose(file);

	rapidjson::Document doc;
	doc.ParseStream(readStream);

	auto services = doc["Services"].GetObj();
	for (auto& service : services)
	{
		const char* serviceName = service.name.GetString();
		if (TryServiceMake(serviceName, service.value, *this))
		{

		}
		else if (strcmp(serviceName, "CameraService") == 0)
		{
			auto cameraService = AddService<CameraService>();
		}
		else if (strcmp(serviceName, "RenderService") == 0)
		{
			auto renderService = AddService<RenderService>();
		}
		else if (strcmp(serviceName, "PhysicsService") == 0)
		{
			auto physicsService = AddService<PhysicsService>();
		}
		else
		{
			ASSERT(false, "GameWorld -- Service %s not defined", serviceName);
		}
	}

	uint32_t capacity = static_cast<uint32_t>(doc["Capacity"].GetInt());
	Initialize(capacity);

	auto gameObjects = doc["GameObjects"].GetArray();
	for (auto& gameObject : gameObjects)
	{
		const char* templateFile = gameObject["Template"].GetString();
		auto obj = CreateGameObject(templateFile);
		if (obj != nullptr)
		{
			const char* name = gameObject["Name"].GetString();
			obj->SetName(name);

			if (gameObject.HasMember("Position"))
			{
				/*auto transform = obj->GetComponent<TransformComponent>();
				if (transform != nullptr)
				{
					const auto& pos = gameObject["Position"].GetArray();
					const float x = pos[0].GetFloat();
					const float y = pos[1].GetFloat();
					const float z = pos[2].GetFloat();
					transform->position = { x, y, z };
				}*/

				const auto& pos = gameObject["Position"].GetArray();
				const float x = pos[0].GetFloat();
				const float y = pos[1].GetFloat();
				const float z = pos[2].GetFloat();
				auto rigidBody = obj->GetComponent<RigidBodyComponent>();
				auto transform = obj->GetComponent<TransformComponent>();
				transform->position = { x, y, z };

				if (rigidBody != nullptr)
				{
					auto rb = rigidBody->GetRigidBody();
					rb->setWorldTransform(ConvertTobtTransform(*transform));
				}
			}
		}
	}
}

GameObject* GameWorld::CreateGameObject(const std::filesystem::path& templateFile)
{
	ASSERT(mInitialized, "GameWorld is not initialized");

	if (mFreeSlots.empty())
	{
		ASSERT(false, "GameWorld out of free slots");
		return nullptr;
	}

	const uint32_t freeSlot = mFreeSlots.back();
	mFreeSlots.pop_back();

	auto& slot = mGameObjectSlots[freeSlot];
	auto& newObject = slot.gameObject;
	newObject = std::make_unique<GameObject>();

	// attach components
	GameObjectFactory::Make(templateFile, *newObject);

	GameObjectHandle handle;
	handle.mIndex = freeSlot;
	handle.mGeneration = slot.generation;

	newObject->mWorld = this;
	newObject->mHandle = handle;
	newObject->Initialize();

	mUpdateLists.push_back(newObject.get());
	return newObject.get();
}

GameObject* GameWorld::GetGameObject(const GameObjectHandle& handle)
{
	if (!IsValid(handle))
	{
		return nullptr;
	}

	return mGameObjectSlots[handle.mIndex].gameObject.get();
}

void GameWorld::DestroyGameObject(const GameObjectHandle& handle)
{
	if (!IsValid(handle))
	{
		return;
	}

	auto& slot = mGameObjectSlots[handle.mIndex];
	slot.generation++;
	mToBeDestroyed.push_back(handle.mIndex);
}

bool GameWorld::IsValid(const GameObjectHandle& handle) const
{
	if (handle.mIndex < 0 || handle.mIndex >= mGameObjectSlots.size())
	{
		return false;
	}

	if (mGameObjectSlots[handle.mIndex].generation != handle.mGeneration)
	{
		return false;
	}

	return true;
}

void GameWorld::ProcessDestroyList()
{
	ASSERT(!mUpdating, "GameWorld can't destroy when updating objects");

	for (auto index : mToBeDestroyed)
	{
		auto& slot = mGameObjectSlots[index];

		GameObject* gameObject = slot.gameObject.get();
		ASSERT(!IsValid(gameObject->GetHandle()), "GameWorld object is still valid");

		mUpdateLists.erase(std::remove(mUpdateLists.begin(), mUpdateLists.end(), gameObject));

		gameObject->Terminate();

		slot.gameObject.reset();
		mFreeSlots.push_back(index);
	}

	mToBeDestroyed.clear();
}