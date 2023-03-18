#pragma once
#include "CMath.h"

namespace CEngine::Math::Random
{
	int RandomInt(int min = 0, int max = std::numeric_limits<int>::max());
	float RandomFloat(float min = 0.0f, float max = 1.0f);

	CEngine::Math::Vector2 RandomVector2(const CEngine::Math::Vector2& min, const CEngine::Math::Vector2& max);

	//CEngine::Math::Vector2 RandomUnitCircle();

	CEngine::Math::Vector3 RandomVector3(const CEngine::Math::Vector3& min, const CEngine::Math::Vector3& max);

}