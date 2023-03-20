#pragma once

#include "Component.h"

namespace CEngine
{
	class AnimatorComponent;
	class TransformComponent;

	class PlayerControllerComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::PlayerController);

		enum AnimState
		{
			Idle = 0,
			Jump = 1
		};

		void Initialize() override;

		void Update(float deltaTime) override;
		void DebugUI() override;

	private:
		TransformComponent* mTransformComponent = nullptr;
		AnimatorComponent* mAnimatorComponent = nullptr;

		float mMoveSpeed = 0.0f;
	};
}