#include <CEngine/Inc/CEngine.h>

using namespace CEngine;

class HotPinkState : public AppState
{
public:
	void Initialize() override
	{
		auto graphicSystem = Graphics::GraphicsSystem::Get();
		graphicSystem->SetClearColor(Graphics::Colors::HotPink);
	}

	void Update(float deltaTime) override
	{
		auto inputSystem = Input::InputSystem::Get();
		if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
			MainApp().ChangeState("DarkBlue");
	}
};

class DarkBlueState : public AppState
{
public:
	void Initialize() override
	{
		auto graphicSystem = Graphics::GraphicsSystem::Get();
		graphicSystem->SetClearColor(Graphics::Colors::DarkBlue);
	}

	void Update(float deltaTime) override
	{
		auto inputSystem = Input::InputSystem::Get();
		if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
			MainApp().ChangeState("HotPink");
	}
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = CEngine::MainApp();
	app.AddState<HotPinkState>("HotPink");
	app.AddState<DarkBlueState>("DarkBlue");
	app.Run({ L"HelloDirectX", 1280, 720 });

	return 0;
}