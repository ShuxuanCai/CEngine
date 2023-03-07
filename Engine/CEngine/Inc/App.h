#pragma once

namespace CEngine
{
	class AppState;

	struct AppConfig
	{
		std::wstring appName = L"CEngine";
		uint32_t winWidth = 1280;
		uint32_t winHeight = 720;
		uint32_t debugDrawLimit = 1000000;
		std::filesystem::path textureRoot = "../../Assets/Images";
	};

	class App final
	{
	public:
		// template has to write together
		template <class StateType>
		void AddState(std::string stateName)
		{
			static_assert(std::is_base_of_v<AppState, StateType>,
				"App -- 'StateType' must be derived from 'AppState'");

			// Find element and if there is not, add it: 
			// Do not use .find(), and (iter == .find()) -> O(log(n))
			// and .emplace() -> O(log(n))

			// Use .try_emplace() like below

			auto [iter, success] = mAppStates.try_emplace(std::move(stateName), nullptr);
			if (success)
			{
				auto& ptr = iter->second; // auto is std::unique_ptr<AppState>
				ptr = std::make_unique<StateType>();
				if (mCurrentState == nullptr)
				{
					LOG("App -- Current state: %s", iter->first.c_str());
					mCurrentState = ptr.get();
				}
			}
		}

		void ChangeState(const std::string& stateName);

		void Run(AppConfig appConfig);
		void Quit();

	private:
		using AppStateMap = std::map<std::string, std::unique_ptr<AppState>>; // map is a binary tree

		AppStateMap mAppStates;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;
		bool mRunning = false;
	};
}