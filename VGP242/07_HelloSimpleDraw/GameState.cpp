#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{

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
}

void GameState::Render()
{
	SimpleDraw::AddTransform(Matrix4::Identity());

	/*SimpleDraw::AddPlane({ 0.0f, -1.0f, 0.0f }, 10, 10, 0.5f, Colors::Blue);
	SimpleDraw::AddAABB({ -1.5f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, Colors::Yellow);
	SimpleDraw::AddSphere({ 1.0f, 1.0f, 0.0f }, 50, 50, 1.0f, Colors::Red);
	
	SimpleDraw::AddFilledPlane({ 0.0f, -1.0f, 0.0f }, 10, 10, 0.5f, mColor);
	SimpleDraw::AddFilledAABB({ -1.5f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, mColor);
	SimpleDraw::AddFilledSphere({ 1.0f, 1.0f, 0.0f }, 50, 50, 1.0f, mColor);*/

	SimpleDraw::AddPlane(mPosition, 10, 10, 0.5f, Colors::Blue);
	SimpleDraw::AddAABB(mPosition, { 1.0f, 1.0f, 1.0f }, Colors::Yellow);
	SimpleDraw::AddSphere(mPosition, 50, 50, 1.0f, Colors::Red);

	SimpleDraw::AddFilledPlane(mPosition, 10, 10, 0.5f, mColor);
	SimpleDraw::AddFilledAABB(mPosition, { 1.0f, 1.0f, 1.0f }, mColor);
	SimpleDraw::AddFilledSphere(mPosition, 50, 50, 1.0f, mColor);

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::DragFloat3("Position", &mPosition.x, 0.01f);
	ImGui::ColorEdit4("Color", &mColor.r);
	ImGui::End();
}