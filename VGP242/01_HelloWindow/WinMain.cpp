#include <Core/Inc/Core.h>

// int   - 4 bytes - 32 bits - Encoding uses 2's complement
// float - 4 bytes - 32 bits - Encoding uses IEEE 754
// bool  - 1 byte  - 8 bits  - Can have unique addresses
// char  - 1 byte  - 8 bits  - Encoding uses ASCII
// wchar - 2 bytes - 16 bits - Encoding uses UNICODE
// UNICODE is all the languages and all the types(ex: emo), memory depends on what it is.

//char c = 'p';
//const char* name = "Chris";
//const wchar_t (check recording)

// Type: 
// - Memory layout (How much? What format?)
// - Operatuins

// With the 'class' keyword, you can define your own type.
// e.g.
// class FOO
// {
// public:
// 	 void DoA();
// 	 void MoveB();
// private:
// 	 int i;
// 	 boool b;
// }
// sizeof(FOO) = (need to see member variable) 4 + 1 + 3 = 8
// -> [iiii][iiii][iiii][iiii]
//    [bbbb][pppp][pppp][pppp]

// COM - Component Object Model:
// 1. COM manages it's own memory
// - Instead of using new/delete, call CreateXXX function to instantiate 
// objects, when done, call Release to decrement ref count.
// 2. COM objects are interface based.

// interface - a list of public pure virtual function declarations
// e.g.
// struct IMusicPlayer
// {
// 	  virtual void Play() = 0;		// these three are pure virtual functions
// 	  virtual void Stop() = 0;
// 	  virtual void Rewind() = 0;
// };

// In DirectX(in D3D11 Interrfaces), there are two interfances using usually:
// Device(Create stuff) and Context(Do stuff)

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	CEngine::Core::Window myWindow;
	myWindow.Initialize(instance, L"Hello Window", 1200, 720);

	while (true)
	{
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
			break;

		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}

	myWindow.Terminate();
	return 0;
}