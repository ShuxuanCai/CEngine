#pragma once

#include "Component.h"

namespace CEngine
{
	class TransformComponent;

	class ColiderComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Collider);

		void Initialize() override;
		void Terminate() override;
		//void DebugUI() override;

		btCollisionShape* GetCollisionShape();
		//void SetCenter(const Math::Vector3& center) { mCenter = center; }
		void SetExtend(const Math::Vector3& extend) { mExtend = extend; }
		void SetOrigin(const Math::Vector3& origin) { mOrigin = origin; }
		const Vector3& GetOrigin() { return mOrigin; }

		/*Math::AABB GetLocalAABB() const;
		Math::AABB GetWorldAABB() const;*/

	private:
		const TransformComponent* mTransformComponent = nullptr;
		btCollisionShape* mCollisionShape = nullptr;
		//Math::Vector3 mCenter = Math::Vector3::Zero;
		Math::Vector3 mExtend = Math::Vector3::One;
		Math::Vector3 mOrigin = Math::Vector3::One;
	};
}