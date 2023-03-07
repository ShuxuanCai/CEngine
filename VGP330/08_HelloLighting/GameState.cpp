#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	
	mMesh = MeshBuilder::CreateSphere(256, 256, 1.0f);

	mEarthRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mEarthRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.power = 10.0f;

	auto tm = TextureManager::Get();
	mEarthRenderObject.diffuseMapId = tm->LoadTexture("earth.jpg");
	mEarthRenderObject.bumpMapId = tm->LoadTexture("earth_bump.jpg");
	mEarthRenderObject.specularMapId = tm->LoadTexture("earth_spec.jpg");
	mEarthRenderObject.normalMapId = tm->LoadTexture("earth_normal.jpg");

	mEarthRenderObject.meshBuffer.Initialize(mMesh);
	mStandardEffect.SetBumpWeight(0.2f);
}

void GameState::Terminate()
{
	mEarthRenderObject.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	mFPS = 1.0f / deltaTime;
}

void GameState::Render()
{
	mStandardEffect.Begin();
	mStandardEffect.Render(mEarthRenderObject);
	mStandardEffect.End();

	/*for (const auto& v : mMesh.vertices)
		SimpleDraw::AddLine(v.position, v.position + v.normal, Colors::Blue);*/

	SimpleDraw::AddTransform(Matrix4::Identity());

	SimpleDraw::AddPlane({ 0.0f, -1.0f, 0.0f }, 10, 10, 0.5f, Colors::Blue);
	SimpleDraw::AddFilledPlane({ 0.0f, -1.0f, 0.0f }, 10, 10, 0.5f, Colors::Blue);

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f", mFPS);
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.0f, -1.0f, 1.0f);
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	if (ImGui::CollapsingHeader("Earth", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Earth", &mEarthRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Earth", &mEarthRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Earth", &mEarthRenderObject.material.specular.r);
		ImGui::DragFloat("Power##Earth", &mEarthRenderObject.material.power, 1.0f, 1.0f, 100.0f);

		ImGui::DragFloat3("Position", &mEarthRenderObject.transform.position.x, 0.01f);
		ImGui::DragFloat3("Rotation", &mEarthRenderObject.transform.rotation.x, 0.01f);
	}

	mStandardEffect.DebugUI();

	ImGui::End();
}