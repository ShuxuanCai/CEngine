#pragma once

#include "Common.h"

namespace CEngine
{
	class TransformComponent final
		: public Component
		, public Graphics::Transform
	{
	public:
		SET_TYPE_ID(ComponentId::Transform);

		void DebugUI() override;
	};
}