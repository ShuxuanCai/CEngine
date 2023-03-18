#pragma once

// Framework headers
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <Math/Inc/CMath.h>
#include <Physics/Inc/Physics.h>

// rapid json files
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

// bullet files
#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>

// Component headers
#include "Component.h"
#include "ColiderComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "FPSCameraControllerComponent.h"
#include "ModelComponent.h"
#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"
#include "AnimatorComponent.h"
#include "Service.h"
#include "TypeIds.h"

// Service headers
#include "CameraService.h"
#include "RenderService.h"
#include "PhysicsService.h"

// World headers
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameWorld.h"

#include "PhysicsDebugDrawer.h"

template <class T>
inline void SafeReleasePhysics(T*& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

inline btVector3 ConvertTobtVector3(const Vector3& vec)
{
	return { vec.x, vec.y, vec.z };
}

inline Vector3 ConvertToVector3(const btVector3& vec)
{
	return { vec.x(), vec.y(), vec.z() };
}

inline CEngine::Graphics::Color ConvertToColor(const btVector3& btColor)
{
	return { btColor.x(), btColor.y(), btColor.z(), 1.0f };
}

inline btTransform ConvertTobtTransform(const CEngine::Graphics::Transform& trans)
{
	return btTransform(btQuaternion(trans.rotation.x, trans.rotation.y, trans.rotation.z, trans.rotation.w),
		btVector3(trans.position.x, trans.position.y, trans.position.z));
}

inline CEngine::Graphics::Transform ConvertToTransform(const btTransform& trans)
{
	const auto& origin = trans.getOrigin();
	const auto& rotation = trans.getRotation();
	CEngine::Graphics::Transform retTrans;
	retTrans.position = Vector3(origin.x(), origin.y(), origin.z());
	retTrans.rotation = Quaternion(rotation.x(), rotation.y(), rotation.z(), rotation.w());
	return retTrans;
}

inline void ConvertToTransform(const btTransform& trans, CEngine::Graphics::Transform& transform)
{
	const auto& origin = trans.getOrigin();
	const auto& rotation = trans.getRotation();
	transform.position = Vector3(origin.x(), origin.y(), origin.z());
	transform.rotation = Quaternion(rotation.x(), rotation.y(), rotation.z(), rotation.w());
}