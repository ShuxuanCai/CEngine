#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = CEngine::MainApp();
	app.AddState<GameState>("GameState");
	app.Run({ L"Hello Solar System", 1280, 720 });
	return 0;
}
