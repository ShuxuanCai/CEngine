#pragma once

#include "TypeIds.h"

namespace CEngine
{
	class Event
	{
	public:
		uint32_t GetTypeId() const { return mTypeId; }

	protected:
		Event(uint32_t typeId)
			: mTypeId(typeId)
		{}

	private:
		uint32_t mTypeId;
	};
}