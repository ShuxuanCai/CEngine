#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = CEngine::MainApp();
	app.AddState<GameState>("GameState");
	app.Run({ L"Hello Cube", 1280, 720 });
	return 0;
}
