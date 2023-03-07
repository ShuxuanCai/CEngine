#pragma once

#include "Service.h"

namespace CEngine
{
	class ColiderComponent;
	class PhysicsComponent;
	class RigidBodyComponent;
	class TransformComponent;
	class PhysicsDebugDrawer;

	class PhysicsService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Physics);

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;

		void DebugUI() override;

		void SetGravity(float gravity);

	private:
		friend class PhysicsComponent;
		void Register(PhysicsComponent* physicsComponent);
		void Unregister(PhysicsComponent* physicsComponent);

		friend class RigidBodyComponent;
		void AddRigidBody(RigidBodyComponent* rigidbodyComponent);
		void RemoveRigidBody(RigidBodyComponent* rigidbodyComponent);

		struct Entry
		{
			ColiderComponent* coliderComponent = nullptr;
			PhysicsComponent* physicsComponent = nullptr;
			RigidBodyComponent* rigidbodyComponent = nullptr;
			TransformComponent* transformComponent = nullptr;
		};

		using PhysicsEntries = std::vector<Entry>;
		PhysicsEntries mPhysicsEntities;

		btBroadphaseInterface* mInterface = nullptr;
		btCollisionDispatcher* mDispatcher = nullptr;
		btDefaultCollisionConfiguration* mCollisionConfiguration = nullptr;
		btDiscreteDynamicsWorld* mDynamicsWorld = nullptr;
		btSequentialImpulseConstraintSolver* mSolver = nullptr;
		PhysicsDebugDrawer* mDebugDrawer = nullptr;

		bool mRenderDebugUI = false;
		float mGravity = -9.81f;
	};
}