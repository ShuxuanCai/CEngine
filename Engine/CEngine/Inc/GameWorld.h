#pragma once

#include "GameObject.h"
#include "Service.h"

namespace CEngine
{
	using CustomService = std::function<bool(const char*, const rapidjson::Value&, GameWorld&)>;

	class GameWorld final
	{
	public:
		static void SetCustomServiceMake(CustomService customService);

		void Initialize(uint32_t capacity);
		void Terminate();

		void Update(float deltaTime);
		void Render();
		void DebugUI();

		template<class ServiceType>
		ServiceType* AddService()
		{
			static_assert(std::is_base_of_v<Service, ServiceType>, "GameWorld -- services must derive from Service");
			ASSERT(!mInitialized, "GameWorld -- cannot add services after gameworld is initialized");
			auto& newService = mServices.emplace_back(std::make_unique<ServiceType>());
			newService->mWorld = this;
			return static_cast<ServiceType*>(newService.get());
		}

		template<class ServiceType>
		ServiceType* GetService()
		{
			auto constThis = static_cast<const GameWorld*>(this);
			return const_cast<ServiceType*>(constThis->GetService<ServiceType>());
		}

		template<class ServiceType>
		const ServiceType* GetService() const
		{
			for (auto& service : mServices)
			{
				if (service->GetTypeId() == ServiceType::StaticGetTypeId())
				{
					return static_cast<ServiceType*>(service.get());
				}
			}

			return nullptr;
		}

		void LoadLevel(const std::filesystem::path& levelFile);
		GameObject* CreateGameObject(const std::filesystem::path& templateFile);
		GameObject* GetGameObject(const GameObjectHandle& handle);

		void DestroyGameObject(const GameObjectHandle& handle);

	private:
		bool IsValid(const GameObjectHandle& handle) const;
		void ProcessDestroyList();

		struct Slot
		{
			std::unique_ptr<GameObject> gameObject;
			uint32_t generation = 0;
		};

		using Services = std::vector<std::unique_ptr<Service>>;
		using GameObjectSlots = std::vector<Slot>;
		using GameObjectPtrs = std::vector<GameObject*>;

		Services mServices;

		GameObjectSlots mGameObjectSlots;
		std::vector<uint32_t> mFreeSlots;
		std::vector<uint32_t> mToBeDestroyed;

		GameObjectPtrs mUpdateLists;

		bool mInitialized = false;
		bool mUpdating = false;
	};
}