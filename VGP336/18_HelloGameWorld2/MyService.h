#pragma once

#include <CEngine/Inc/CEngine.h>
#include "TypeIds.h"

class MyService final : public CEngine::Service
{
public:
	SET_TYPE_ID(ServiceId::MyService);

	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

	void DebugUI() override;
};