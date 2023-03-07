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

	Color color;
	mCubeMesh = MeshBuilder::CreateCubePC(0.5f, color);
	mPlaneMesh = MeshBuilder::CreatePlanePC(5, 5, 0.5f);
	mCylinderMesh = MeshBuilder::CreateCylinderPC(100, 100, 1.0f, 0.5f);
	mSphereMesh = MeshBuilder::CreateSpherePC(100, 100, 0.5f);

	mCubeMeshBuffer.Initialize(mCubeMesh);
	mPlaneMeshBuffer.Initialize(mPlaneMesh);
	mCylinderMeshBuffer.Initialize(mCylinderMesh);
	mSphereMeshBuffer.Initialize(mSphereMesh);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoTransform.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void GameState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mCubeMeshBuffer.Terminate();
	mPlaneMeshBuffer.Terminate();
	mCylinderMeshBuffer.Terminate();
	mSphereMeshBuffer.Terminate();
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

	mConstantBuffer.BindVS(0);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();

	static float rotation = 0.0f;
	rotation += 0.01f;
	Matrix4 cubeWorld = Matrix4::RotationY(rotation) * Matrix4::Translation({ -4.0f, 0.0f, 0.0f });
	Matrix4 planeWorld = Matrix4::RotationY(rotation) * Matrix4::Translation({ -2.0f, 0.0f, 0.0f });
	Matrix4 cylinderWorld = Matrix4::RotationY(rotation) * Matrix4::Translation({ 0.0f, 0.0f, 0.0f });
	Matrix4 sphereWorld = Matrix4::RotationY(rotation) * Matrix4::Translation({ 2.0f, 0.0f, 0.0f });
	//Matrix4 wvp = Transpose(world * view * proj); // HLSL requires to be column-major

	Matrix4 wvp1 = Transpose(cubeWorld * view * proj);
	Matrix4 wvp2 = Transpose(planeWorld * view * proj);
	Matrix4 wvp3 = Transpose(cylinderWorld * view * proj);
	Matrix4 wvp4 = Transpose(sphereWorld * view * proj);

	mConstantBuffer.Update(&wvp1);
	mCubeMeshBuffer.Render();

	mConstantBuffer.Update(&wvp2);
	mPlaneMeshBuffer.Render();

	mConstantBuffer.Update(&wvp3);
	mCylinderMeshBuffer.Render();

	mConstantBuffer.Update(&wvp4);
	mSphereMeshBuffer.Render();
}

void GameState::DebugUI()
{

}