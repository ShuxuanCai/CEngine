#include <CEngine/Inc/CEngine.h>
#include "GameState.h"

using namespace CEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config = { L"CEngine Final" };
	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return 0;
}
