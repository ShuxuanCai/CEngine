#include "Precompiled.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsService.h"
#include "GameWorld.h"

using namespace CEngine;

void PhysicsComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();

	auto physicsService = GetOwner().GetWorld().GetService<PhysicsService>();
	physicsService->Register(this);
}

void PhysicsComponent::Terminate()
{
	auto physicsService = GetOwner().GetWorld().GetService<PhysicsService>();
	physicsService->Unregister(this);
	mRigidBodyComponent = nullptr;
	mTransformComponent = nullptr;
}

void PhysicsComponent::UpdatePhysics()
{
	if (mRigidBodyComponent != nullptr)
	{
		auto& rigidBodyTransform = mRigidBodyComponent->GetRigidBody()->getWorldTransform();
		ConvertToTransform(rigidBodyTransform, *mTransformComponent);
	}
}

void PhysicsComponent::DebugUI()
{

}