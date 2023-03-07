#pragma once

#include <CEngine/Inc/CEngine.h>

enum class ComponentId
{
	MyComponent = static_cast<uint32_t>(CEngine::ComponentId::Count),
	MyNextComponent,
	AnotherComponent
};

enum class ServiceId
{
	MyService = static_cast<uint32_t>(CEngine::ServiceId::Count),
	NextService,
	AnotherSercive
};