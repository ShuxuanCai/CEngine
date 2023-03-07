#include "Precompiled.h"
#include "PhysicsService.h"
#include "ColiderComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"
#include "CameraService.h"
#include "PhysicsDebugDrawer.h"

#include "GameWorld.h"
#include "GameObject.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Math;

void PhysicsService::Initialize()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mInterface = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguration);
	mDebugDrawer = new PhysicsDebugDrawer();
	mDebugDrawer->SetGameWorld(&GetOwner());
	mDynamicsWorld->setDebugDrawer(mDebugDrawer);
	mDynamicsWorld->setGravity(btVector3(0, mGravity, 0));
}

void PhysicsService::Terminate()
{
	SafeReleasePhysics(mDebugDrawer);
	SafeReleasePhysics(mDynamicsWorld);
	SafeReleasePhysics(mSolver);
	SafeReleasePhysics(mInterface);
	SafeReleasePhysics(mDispatcher);
	SafeReleasePhysics(mCollisionConfiguration);
}

void PhysicsService::Update(float deltaTime)
{
	mDynamicsWorld->stepSimulation(deltaTime, 10);
	for (auto& entry : mPhysicsEntities)
	{
		entry.physicsComponent->UpdatePhysics();
	}
}

void PhysicsService::DebugUI()
{
	if (ImGui::Checkbox("Render Physics", &mRenderDebugUI))
	{

	}

	if (mRenderDebugUI)
	{
		int debugMode = mDebugDrawer->getDebugMode();
		bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe) > 0;
		if (ImGui::Checkbox("[DBG] DrawWireFrame", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawWireframe : debugMode & ~btIDebugDraw::DBG_DrawWireframe;
		}
		isEnabled = (debugMode & btIDebugDraw::DBG_DrawAabb) > 0;
		if (ImGui::Checkbox("[DBG] DrawAABB", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawAabb : debugMode & ~btIDebugDraw::DBG_DrawAabb;
		}
		isEnabled = (debugMode & btIDebugDraw::DBG_DrawNormals) > 0;
		if (ImGui::Checkbox("[DBG] DrawNormals", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawNormals : debugMode & ~btIDebugDraw::DBG_DrawNormals;
		}
		mDebugDrawer->setDebugMode(debugMode);

		/*for (auto& entry : mPhysicsEntities)
		{
			entry.physicsComponent->DebugUI();
			entry.coliderComponent->DebugUI();
			entry.rigidbodyComponent->DebugUI();
		}*/

		auto camera = GetOwner().GetService<CameraService>();
		SimpleDraw::Render(camera->GetMain());
		mDynamicsWorld->debugDrawWorld();
		mDebugDrawer->Render();
	}
}

void PhysicsService::SetGravity(float gravity)
{
	mGravity = gravity;
	if (mDynamicsWorld != nullptr)
	{
		mDynamicsWorld->setGravity(btVector3(0, mGravity, 0));
	}
}

void PhysicsService::Register(PhysicsComponent* physicsComponent)
{
	Entry& entry = mPhysicsEntities.emplace_back();

	auto& gameObject = physicsComponent->GetOwner();
	entry.physicsComponent = physicsComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
	entry.coliderComponent = gameObject.GetComponent<ColiderComponent>();
	entry.rigidbodyComponent = gameObject.GetComponent<RigidBodyComponent>();
}

void PhysicsService::Unregister(PhysicsComponent* physicsComponent)
{
	auto iter = std::find_if(
		mPhysicsEntities.begin(),
		mPhysicsEntities.end(),
		[&](const Entry& entry)
		{
			return entry.physicsComponent == physicsComponent;
		});
	if (iter != mPhysicsEntities.end())
	{
		mPhysicsEntities.erase(iter);
	}
}

void PhysicsService::AddRigidBody(RigidBodyComponent* rigidbodyComponent)
{
	if (rigidbodyComponent->GetRigidBody() != nullptr)
	{
		mDynamicsWorld->addRigidBody(rigidbodyComponent->GetRigidBody());
	}
}

void PhysicsService::RemoveRigidBody(RigidBodyComponent* rigidbodyComponent)
{
	if (rigidbodyComponent->GetRigidBody() != nullptr)
	{
		mDynamicsWorld->removeRigidBody(rigidbodyComponent->GetRigidBody());
	}
}