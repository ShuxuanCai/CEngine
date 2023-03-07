#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Math;

void GameState::Initialize()
{
	// NDC - Normalized Device Coordinate
	//
	//          +-----------------+
	//         /                 /|
	//   1.0  +-----------------+ |
	//	      |        ^        | |
	//	      |        |        | |
	//	      | <------+------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0
	//

	mVertices.push_back({ Vector3{-0.005f, 0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{ 0.005f,-0.25f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{-0.005f,-0.25f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });

	mVertices.push_back({ Vector3{ 0.005f, 0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{ 0.005f,-0.25f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{-0.005f, 0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });

	mVertices.push_back({ Vector3{ 0.75f,-0.25f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{-0.75f,-0.25f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{  0.0f, 0.75f, 0.0f }, Color{ 0.0f, 1.0f, 1.0f, 1.0f } });

	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{ 0.25f,-0.75f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });

	mVertices.push_back({ Vector3{ 0.25f,-0.75f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{-0.25f,-0.75f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });


	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoSomething.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoSomething.fx");
}

void GameState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	/*auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
	{
		MainApp().ChangeState("Heart");

		mVertices.clear();
		mVertices.push_back({ Vector3{  0.5f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.5f, -0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f, -0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{  0.5f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f, -0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{ 0.25f,   0.5f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.5f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{-0.25f,   0.5f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f,  0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{  0.0f,  -1.0f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f, -0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.5f, -0.25f, 0.0f }, Color{ 1.0f, 0.0f, 0.0f, 1.0f } });
	}

	if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
	{
		MainApp().ChangeState("Diomand");

		mVertices.clear();
		mVertices.push_back({ Vector3{  0.5f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 0.9f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f,-0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.9f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 0.9f, 1.0f } });

		mVertices.push_back({ Vector3{  0.5f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
		mVertices.push_back({ Vector3{ 0.375f, 0.5f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });

		mVertices.push_back({ Vector3{ -0.5f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
		mVertices.push_back({ Vector3{-0.375f, 0.5f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });

		mVertices.push_back({ Vector3{ 0.375f, 0.5f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f,  0.0f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
		mVertices.push_back({ Vector3{-0.375f, 0.5f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f, 1.0f } });
	}

	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("Sailboat");

		mVertices.clear();
		mVertices.push_back({ Vector3{-0.005f, 0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ 0.005f,-0.25f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{-0.005f,-0.25f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{ 0.005f, 0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ 0.005f,-0.25f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{-0.005f, 0.75f, 0.0f }, Color{ 0.0f, 0.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{ 0.75f,-0.25f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{-0.75f,-0.25f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{  0.0f, 0.75f, 0.0f }, Color{ 0.0f, 1.0f, 1.0f, 1.0f } });

		mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ 0.25f,-0.75f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });

		mVertices.push_back({ Vector3{ 0.25f,-0.75f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{-0.25f,-0.75f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f, 1.0f } });
		mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Color{ 1.0f, 1.0f, 0.0f, 1.0f } });
	}*/
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mMeshBuffer.Render();
}

void GameState::DebugUI()
{

}


// Add 04_HelloShapes project
// - Copy code from 03_HelloTriangle
// - Update to use DoSomething.fx shaders
// - Create multiple meshes and vertex buffers
//	- Draw a heart
//	- Draw a triforce
//	- Draw something with more than 5 triangles
// - Use input check so you can change between them