#include "Precompiled.h"
#include "ColiderComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"

using namespace CEngine;

void ColiderComponent::Initialize()
{
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
    mCollisionShape = new btBoxShape(btVector3(mExtend.x, mExtend.y, mExtend.z));
}

void ColiderComponent::Terminate()
{
    mTransformComponent = nullptr;
    SafeReleasePhysics(mCollisionShape);
}

//void ColiderComponent::DebugUI()
//{
//    const auto& aabb = GetWorldAABB();
//    Graphics::SimpleDraw::AddAABB(aabb.Min(), aabb.Max(), Graphics::Colors::HotPink);
//}

btCollisionShape* ColiderComponent::GetCollisionShape()
{
    return mCollisionShape;
}

//Math::AABB ColiderComponent::GetLocalAABB() const
//{
//    return { mOrigin, mExtend };
//}
//
//Math::AABB ColiderComponent::GetWorldAABB() const
//{
//    return { mTransformComponent->position + mOrigin, mExtend };
//}