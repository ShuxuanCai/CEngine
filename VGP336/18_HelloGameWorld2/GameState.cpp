#include "GameState.h"
#include "MyService.h"
#include "MyComponent.h"

using namespace CEngine;
using namespace CEngine::Graphics;

namespace
{
	bool CustomGameMake(const char* componentName, const rapidjson::Value& value, GameObject& gameObject)
	{
		if (strcmp(componentName, "MyComponent") == 0)
		{
			auto myComponent = gameObject.AddComponent<MyComponent>();
			return true;
		}

		return false;
	}

	bool CustomServiceMake(const char* serviceName, const rapidjson::Value& value, GameWorld& gameWorld)
	{
		if (strcmp(serviceName, "MyService") == 0)
		{
			auto myService = gameWorld.AddService<MyService>();
			return true;
		}

		return false;
	}
}

void GameState::Initialize()
{
	GameObjectFactory::SetCustomMake(CustomGameMake);
	GameWorld::SetCustomServiceMake(CustomServiceMake);
	mGameWorld.LoadLevel("../../Assets/Templates/test_level.json");
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	mGameWorld.DebugUI();/*
	SimpleDraw::Render(mCamera);
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Separator();

	if (ImGui::Button("Add Object"))
	{
		auto gameObject = mGameWorld.CreateGameObject("");
		gameObject->SetName(std::to_string(mHandles.size()).c_str());
		mHandles.push_back(gameObject->GetHandle());
	}

	for (auto handle : mHandles)
	{
		auto gameObject = mGameWorld.GetGameObject(handle);
		if (gameObject != nullptr)
		{
			if (ImGui::CollapsingHeader(gameObject->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				auto transformComponent = gameObject->GetComponent<TransformComponent>();
				if (transformComponent != nullptr)
				{
					if (ImGui::DragFloat3("Position##", &transformComponent->position.x, 0.01f));
					{

					}

					if (ImGui::Button((std::string("Remove Object##") + gameObject->GetName()).c_str()))
					{
						mGameWorld.DestroyGameObject(handle);
					}
				}
			}
		}
	}

	ImGui::End();*/
}