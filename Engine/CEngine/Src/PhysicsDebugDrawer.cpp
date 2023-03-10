#include "Precompiled.h"
#include "PhysicsDebugDrawer.h"

#include "GameWorld.h"
#include "CameraService.h"
#include <Graphics/Inc/SimpleDraw.h>

using namespace CEngine;
using namespace CEngine::Graphics;

void PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	SimpleDraw::AddLine(ConvertToVector3(from), ConvertToVector3(to), ConvertToColor(color));
}

void PhysicsDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

}

void PhysicsDebugDrawer::reportErrorWarning(const char* warningString)
{
	LOG("[Physics Warning] %s", warningString);
}

void PhysicsDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{

}

void PhysicsDebugDrawer::setDebugMode(int debugMode)
{
	mDebugMode = debugMode;
}

int PhysicsDebugDrawer::getDebugMode() const
{
	return mDebugMode;
}

void PhysicsDebugDrawer::SetGameWorld(GameWorld* gameWorld)
{
	mGameWorld = gameWorld;
}

void PhysicsDebugDrawer::Render()
{
	auto camera = mGameWorld->GetService<CameraService>();
	SimpleDraw::Render(camera->GetMain());
}