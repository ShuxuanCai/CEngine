#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	CEngine::AppConfig appConfig;
	appConfig.appName = L"Hello Shadow";
	appConfig.winWidth = 1280;
	appConfig.winHeight = 720;
	appConfig.debugDrawLimit = 1000000;
	appConfig.textureRoot = "../../Assets/Images";

	auto& app = CEngine::MainApp();
	app.AddState<GameState>("GameState");
	app.Run(appConfig);
	return 0;
}
