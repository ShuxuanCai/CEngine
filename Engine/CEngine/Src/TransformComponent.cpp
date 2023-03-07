#include "Precompiled.h"
#include "TransformComponent.h"

using namespace CEngine;

void TransformComponent::DebugUI()
{
	Graphics::SimpleDraw::AddTransform(GetMatrix4());
}