#pragma once

#include "Component.h"

namespace CEngine
{
	class TransformComponent;
	class ColiderComponent;

	class RigidBodyComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::RigidBody);

		void Initialize() override;
		void Terminate() override;

		void SetMass(float mass);

		bool IsDynamic() const;
		btRigidBody* GetRigidBody();

	private:
		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;
		bool mIsDynamic = false;
	};
}
