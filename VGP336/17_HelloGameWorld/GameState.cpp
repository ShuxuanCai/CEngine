#include "GameState.h"

using namespace CEngine;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.AddService<PhysicsService>();
	mGameWorld.AddService<RenderService>();
	mGameWorld.Initialize(100);

	mGameWorld.CreateGameObject("../../Assets/Templates/fps_camera.json");
	mGameWorld.CreateGameObject("../../Assets/Templates/test_player.json");
	mGameWorld.CreateGameObject("../../Assets/Templates/ground.json");
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