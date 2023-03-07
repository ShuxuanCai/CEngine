#pragma once

namespace CEngine::Core
{
	class WindowMessageHandler
	{
	public:
		using Callback = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

		void Hook(HWND window, Callback cb);
		void Unhook();

		LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND mWindow = nullptr;
		Callback mPreviousCallback = nullptr;
	};
}

// function pointer
// ex
// int Foo(int i, float f, bool b); // int(int, float, bool)
// using FuncPtr = int(*)(int, float, bool);
// FuncPtr myFunc;
// myFunc = Foo;