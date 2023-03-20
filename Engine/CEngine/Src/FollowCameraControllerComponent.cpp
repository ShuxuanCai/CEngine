#include "Precompiled.h"
#include "FollowCameraControllerComponent.h"

#include "CameraComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "TransformComponent.h"

using namespace CEngine;

void FollowCameraControllerComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
}

void FollowCameraControllerComponent::Update(float deltaTime)
{
	auto gameObject = GetOwner().GetWorld().GetGameObject(*mTarget);
	if (gameObject)
	{
		const auto transformComponent = gameObject->GetComponent<TransformComponent>();
		const auto transform = transformComponent->GetMatrix4();
		const auto position = Math::GetTranslation(transform);

		auto& camera = mCameraComponent->GetCamera();
		camera.SetPosition(position);
	}
}