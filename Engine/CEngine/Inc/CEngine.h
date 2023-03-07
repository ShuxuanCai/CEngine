#pragma once

#include "Common.h"

// App headers
#include "App.h"
#include "AppState.h"

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

namespace CEngine
{
	App& MainApp();
}