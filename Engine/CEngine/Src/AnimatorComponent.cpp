#include "Precompiled.h"
#include "AnimatorComponent.h"
#include "ModelComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

using namespace CEngine;

void AnimatorComponent::Initialize()
{
	auto modelComponent = GetOwner().GetComponent<ModelComponent>();
	mAnimator.Initialize(modelComponent->GetModelID());
	mAnimator.PlayAnimation(0, true);
}

void AnimatorComponent::Update(float deltaTime)
{
	mAnimator.Update(deltaTime);
}

void AnimatorComponent::DebugUI()
{

}