#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;
using namespace CEngine::Physics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::LightSlateGray);

	// Camera Settings
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(300.0f);
	mCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// Physics World settings
	PhysicsWorld::Settings settings;
	settings.gravity = { 0.0f, -9.8f, 0.0f };
	settings.timeStep = 1.0f / 60.0f;
	settings.drag = 0.3f;
	settings.iterations = 1;
	mPhysicsWorld.Initilize(settings);

	mVecFrames.reserve(mMaxFrameSize);
	InitializeParticles(1000); //Just for experiment
}

void GameState::Terminate()
{
	mPhysicsWorld.Clear();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float kMoveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float kTurnSpeed = 1.0f;

	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
	}
	mPhysicsWorld.Update(deltaTime);
}

void GameState::Render()
{
	mPhysicsWorld.DebugDraw();

	SimpleDraw::AddGroundPlane(50.0f,Colors::White);

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Physics", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	float fps = ImGui::GetIO().Framerate; //Get frames
	const size_t frameSize = mVecFrames.size();
	if (frameSize > mMaxFrameSize) //Max seconds to show
	{
		for (size_t i = 1; i < frameSize; ++i)
		{
			mVecFrames[i - 1] = mVecFrames[i];
		}
		mVecFrames[frameSize - 1] = fps;
	}
	else
	{
		mVecFrames.push_back(fps);
	}
	ImGui::PlotLines("", &mVecFrames[0], static_cast<int>(frameSize), 0, NULL, 0.0f, 300.0f, ImVec2(250, 30));

	if (ImGui::Button("Particles!"))
	{
		UseRawParticles(1500);
	}

	if (ImGui::Button("Show!"))
	{
		mPhysicsWorld.Clear(true);
	}
	ImGui::Separator();

	ImGui::End();
}

void GameState::InitializeParticles(int maxParticles)
{
	mPhysicsWorld.Clear(true);
	for (int i = 0; i != maxParticles; ++i)
	{
		auto p = std::make_unique<Particle>();
		mPhysicsWorld.AddParticle(p);
	}
}

void GameState::UseRawParticles(int count)
{
	//mPhysicsWorld.Clear(true);
	const auto& particlesList = mPhysicsWorld.GetParticles();
	const size_t particleCount = particlesList.size();
	for (int i = 0; i != count; ++i)
	{
		auto& particle = particlesList[i % particleCount];
		particle->SetPosition({ 0.0f, 5.0f, 0.0f });

		particle->SetVelocity(Random::RandomVector3({ -0.05f, 0.1f, -0.05f }, { 0.05f, 0.4f, 0.05f }));
		particle->radius = 0.1f;
		particle->bounce = 0.3f;

	}
}
