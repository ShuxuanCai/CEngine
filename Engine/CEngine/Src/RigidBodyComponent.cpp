#include "Precompiled.h"
#include "RigidBodyComponent.h"
#include "ColiderComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "PhysicsService.h"

using namespace CEngine;
using namespace CEngine::Graphics;

void RigidBodyComponent::Initialize()
{
	auto coliderComponent = GetOwner().GetComponent<ColiderComponent>();
	auto transformComponent = GetOwner().GetComponent<TransformComponent>();

	auto collisionShape = coliderComponent->GetCollisionShape();
	btVector3 localInertia(0.0f, 0.0f, 0.0f);
	if (IsDynamic())
	{
		collisionShape->calculateLocalInertia(mMass, localInertia);
	}

	Transform origin;
	origin.position = coliderComponent->GetOrigin();
	mMotionState = new btDefaultMotionState(ConvertTobtTransform(*transformComponent), ConvertTobtTransform(origin));
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, mMotionState, collisionShape, localInertia);
	mRigidBody = new btRigidBody(rbInfo);

	auto physicsService = GetOwner().GetWorld().GetService<PhysicsService>();
	physicsService->AddRigidBody(this);
}

void RigidBodyComponent::Terminate()
{
	auto physicsService = GetOwner().GetWorld().GetService<PhysicsService>();
	physicsService->RemoveRigidBody(this);

	if (mMotionState)
	{
		delete mMotionState;
	}
	mMotionState = nullptr;
	SafeReleasePhysics(mRigidBody);
}

void RigidBodyComponent::SetMass(float mass)
{
	mMass = mass;
}

bool RigidBodyComponent::IsDynamic() const
{
	return mMass > 0.0f;
}

btRigidBody* RigidBodyComponent::GetRigidBody()
{
	return mRigidBody;
}