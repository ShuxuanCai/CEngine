#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

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

	mVertices.push_back({ Vector3{  0.5f,  0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, 0.5f }, Colors::Red });

	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{  0.5f,  0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, 0.5f }, Colors::Red });
												   
	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, 0.5f }, Colors::Red });

	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, 0.5f }, Colors::Red });

	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Green });

	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Green });
												 
	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Green });

	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Green });

	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{  0.5f,  0.5f,  0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Yellow });

	mVertices.push_back({ Vector3{  0.5f,  0.5f,  0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Yellow });
												 
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{  0.5f,  0.5f,  0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f,  0.5f }, Colors::Yellow });

	mVertices.push_back({ Vector3{  0.5f,  0.5f,  0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Yellow });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f,  0.5f }, Colors::Yellow });

	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Blue });

	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Blue });
										  
	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f,  0.5f }, Colors::Blue });

	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::Blue });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f,  0.5f }, Colors::Blue });

	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::White });

	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, -0.5f }, Colors::White });

	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f,  0.5f,  0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::White });

	mVertices.push_back({ Vector3{  0.5f,  0.5f,  0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f, -0.5f,  0.5f }, Colors::White });
	mVertices.push_back({ Vector3{  0.5f,  0.5f, -0.5f }, Colors::White });

	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f,  0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Brown });

	mVertices.push_back({ Vector3{ -0.5f, -0.5f,  0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, -0.5f }, Colors::Brown });
								   
	mVertices.push_back({ Vector3{ -0.5f,  0.5f,  0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f,  0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Brown });

	mVertices.push_back({ Vector3{ -0.5f, -0.5f,  0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f,  0.5f }, Colors::Brown });
	mVertices.push_back({ Vector3{ -0.5f,  0.5f, -0.5f }, Colors::Brown });

	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoTransform.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void GameState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	static float rotation = 0.0f;
	rotation += 0.01f;
	Matrix4 world = Matrix4::RotationY(rotation);
	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(world * view * proj); // HLSL requires to be column-major

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void GameState::DebugUI()
{

}