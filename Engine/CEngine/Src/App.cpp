#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace CEngine;
using namespace CEngine::Core;
using namespace CEngine::Graphics;
using namespace CEngine::Input;

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		LOG("App -- Next State: %s", stateName.c_str());
		mNextState = iter->second.get();
	}
}

void App::Run(AppConfig appConfig)
{
	LOG("App -- Running");

	LOG("App -- Creating Window...");
	Window window;
	window.Initialize(GetModuleHandle(nullptr), appConfig.appName, appConfig.winWidth, appConfig.winHeight);

	// Initialize subsystems
	LOG("App -- Initializing engine system...");
	auto handle = window.GetWindowHandle();
	InputSystem::StaticInitialize(handle);
	GraphicsSystem::StaticInitialize(handle, false);
	SimpleDraw::StaticInitialize(appConfig.debugDrawLimit);
	DebugUI::StaticInitialize(handle, false, true);
	TextureManager::StaticInitialize(appConfig.textureRoot);
	ModelManager::StaticInitialize();

	// Initialize the starting state
	LOG("App -- Initializing app state...");
	ASSERT(mCurrentState, "App -- No app state found!");
	mCurrentState->Initialize();

	LOG("App -- Entering game loop...");
	mRunning = true;
	while (mRunning)
	{
		window.ProcessMessage();
		if (!window.IsActive())
		{
			Quit();
			continue;
		}

		auto inputSystem = InputSystem::Get();
		inputSystem->Update();

		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr); // Same to mCurrentState = mNextState; mNextState = nummptr, but the comment one is bad
			mCurrentState->Initialize();
		}

		auto deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);

		auto graphicSystem = GraphicsSystem::Get();
		graphicSystem->BeginRender();

		mCurrentState->Render();

		DebugUI::BeginRender();
		mCurrentState->DebugUI();
		DebugUI::EndRender();

		graphicSystem->EndRender();
	}

	LOG("App -- Terminating app state...");
	mCurrentState->Terminate();

	LOG("App -- Shutting down engine system...");
	ModelManager::StaticTerminate();
	TextureManager::StaticTerminate();
	DebugUI::StaticTerminate();
	SimpleDraw::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	InputSystem::StaticTerminate();

	LOG("App -- Terminating app window...");
	window.Terminate();
}

void App::Quit()
{
	mRunning = false;
}