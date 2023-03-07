#pragma once

namespace CEngine::Graphics::DebugUI
{
	void StaticInitialize(HWND window, bool docking = false, bool multiViewport = false);
	void StaticTerminate();

	void BeginRender();
	void EndRender();
}