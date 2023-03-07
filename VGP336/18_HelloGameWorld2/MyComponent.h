#pragma once

#include <CEngine/Inc/CEngine.h>
#include "TypeIds.h"

// animal mount
// jumping
// TPSController
// AI behavior

class MyComponent final : public CEngine::Component
{
public:
	SET_TYPE_ID(ComponentId::MyComponent);

	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void DebugUI() override;
};