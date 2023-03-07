#pragma once

#include "Component.h"

namespace CEngine
{
	class ModelComponent;

	class AnimatorComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Animator);

		void Initialize() override;
		void Update(float deltaTime) override;
		void DebugUI() override;

		Graphics::Animator& GetAnimator() { return mAnimator; }
		const Graphics::Animator& GetAnimator() const { return mAnimator; }

	private:
		Graphics::Animator mAnimator;
	};
}