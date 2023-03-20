#pragma once

#include "Component.h"

namespace CEngine
{
	class CameraComponent;

	class FollowCameraControllerComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::FollowCameraController);

		void Initialize() override;
		void Update(float deltaTime) override;

		void SetTarget(GameObjectHandle* target) { mTarget = target; }

	private:
		CameraComponent* mCameraComponent = nullptr;
		GameObjectHandle* mTarget;
	};
}