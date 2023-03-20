#include "Precompiled.h"
#include "PlayerControllerComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "TerrainService.h"

using namespace CEngine;
using namespace CEngine::Input;
using namespace CEngine::Math;

void PlayerControllerComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mAnimatorComponent = GetOwner().GetComponent<AnimatorComponent>();
}

void PlayerControllerComponent::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? mMoveSpeed : mMoveSpeed * 10.0f;
	const float turnSpeed = 0.1f;

	Matrix4 transform = mTransformComponent->GetMatrix4();
	Vector3 velocity = Vector3::Zero;

	if (inputSystem->IsKeyDown(KeyCode::W))
		velocity = GetUp(transform) * moveSpeed;
	if (inputSystem->IsKeyDown(KeyCode::S))
		velocity = GetUp(transform) * -moveSpeed;
	if (inputSystem->IsKeyDown(KeyCode::D))
		velocity = GetRight(transform) * moveSpeed;
	if (inputSystem->IsKeyDown(KeyCode::A))
		velocity = GetRight(transform) * -moveSpeed;

	Vector3 position = GetTranslation(transform);
	position += velocity * deltaTime;

	// Rotation
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		auto mouseX = inputSystem->GetMouseMoveX() * deltaTime;
	}
}

void PlayerControllerComponent::DebugUI()
{

}
