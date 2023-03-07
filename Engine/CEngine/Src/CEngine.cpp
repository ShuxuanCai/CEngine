#include "Precompiled.h"
#include "CEngine.h"

CEngine::App& CEngine::MainApp()
{
	static App sApp; // static here: acess is local, lifetime is globals
	return sApp;
}

// Memory Layout:
// HD <-> RAM <-> Cache <-> CPU(Registers)