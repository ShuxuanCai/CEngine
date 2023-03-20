#pragma once

#include "Common.h"

namespace CEngine
{
	enum class ComponentId
	{
		Transform,
		Collider,
		Camera,
		PlayerController,
		FPSCameraController,
		FollowCameraController,
		Model,
		Mesh,
		Animator,
		Physics,
		RigidBody,
		Count
	};

	enum class ServiceId
	{
		Camera,
		Render,
		Physics,
		Terrain,
		Count
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() { return static_cast<uint32_t>(id); }\
	uint32_t GetTypeId() const override { return StaticGetTypeId(); }