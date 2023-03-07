#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.1f, -0.3f });
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
	
	earth.mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 0.0094f);
	sun.mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 0.065f);
	mercury.mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 0.003f);
	venus.mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 0.009f);
	mars.mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 0.0045f);
	moon.mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 0.00188f);
	mSkydomeMesh = MeshBuilder::CreateSkydome(100, 100, 5.0);
	
	earth.mPlanetMeshBuffer.Initialize(earth.mPlanetMesh);
	sun.mPlanetMeshBuffer.Initialize(sun.mPlanetMesh);
	mercury.mPlanetMeshBuffer.Initialize(mercury.mPlanetMesh);
	venus.mPlanetMeshBuffer.Initialize(venus.mPlanetMesh);
	mars.mPlanetMeshBuffer.Initialize(mars.mPlanetMesh);
	moon.mPlanetMeshBuffer.Initialize(moon.mPlanetMesh);
	mSkydomeMeshBuffer.Initialize(mSkydomeMesh);

	mVertexShader.Initialize<VertexPX>(L"../../Assets/Shaders/DoTexturing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));

	earth.mPlanetTexture.Initialize(L"../../Assets/Images/earth.jpg");
	sun.mPlanetTexture.Initialize(L"../../Assets/Images/sun.jpg");
	mercury.mPlanetTexture.Initialize(L"../../Assets/Images/mercury.jpg");
	venus.mPlanetTexture.Initialize(L"../../Assets/Images/venus.jpg");
	mars.mPlanetTexture.Initialize(L"../../Assets/Images/mars.jpg");
	moon.mPlanetTexture.Initialize(L"../../Assets/Images/moon.jpg");
	mSkydomeTexture.Initialize(L"../../Assets/Images/space.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameState::Terminate()
{
	mSampler.Terminate();

	mSkydomeTexture.Terminate();
	sun.mPlanetTexture.Terminate();
	earth.mPlanetTexture.Terminate();
	mercury.mPlanetTexture.Terminate();
	venus.mPlanetTexture.Terminate();
	mars.mPlanetTexture.Terminate();
	moon.mPlanetTexture.Terminate();

	mConstantBuffer.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();

	mSkydomeMeshBuffer.Terminate();
	sun.mPlanetMeshBuffer.Terminate();
	earth.mPlanetMeshBuffer.Terminate();
	mercury.mPlanetMeshBuffer.Terminate();
	venus.mPlanetMeshBuffer.Terminate();
	mars.mPlanetMeshBuffer.Terminate();
	moon.mPlanetMeshBuffer.Terminate();
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
	mSampler.BindPS(0);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();

	static float earthRotation = 0.0f;
	earthRotation += 0.008f;
	Matrix4 earthWorld = Matrix4::RotationY(earthRotation) * Matrix4::Translation({ 0.150f, 0.0f, 0.0f }) * Matrix4::RotationY(earthRotation);
	Matrix4 earthWvp = Transpose(earthWorld * view * proj);

	static float moonRotation = 0.0f;
	moonRotation += 0.1f;
	Matrix4 moonWorld = Matrix4::RotationY(moonRotation) * Matrix4::Translation({ 0.018f, 0.0f, 0.0f }) * Matrix4::RotationY(moonRotation) * Matrix4::Translation({ 0.150f, 0.0f, 0.0f }) * Matrix4::RotationY(earthRotation);
	Matrix4 moonWvp = Transpose(moonWorld * view * proj);

	static float mercuryRotation = 0.0f;
	mercuryRotation += 0.007f;
	Matrix4 mercuryWorld = Matrix4::RotationY(mercuryRotation) * Matrix4::Translation({ 0.1f, 0.0f, 0.0f }) * Matrix4::RotationY(mercuryRotation);
	Matrix4 mercuryWvp = Transpose(mercuryWorld * view * proj);

	static float venusRotation = 0.0f;
	venusRotation += 0.009f;
	Matrix4 venusWorld = Matrix4::RotationY(venusRotation) * Matrix4::Translation({ 0.12f, 0.0f, 0.0f }) * Matrix4::RotationY(venusRotation);
	Matrix4 venusWvp = Transpose(venusWorld * view * proj);

	static float marsRotation = 0.0f;
	marsRotation += 0.01f;
	Matrix4 marsWorld = Matrix4::RotationY(marsRotation) * Matrix4::Translation({ 0.18f, 0.0f, 0.0f }) * Matrix4::RotationY(marsRotation);
	Matrix4 marsWvp = Transpose(marsWorld * view * proj);

	static float SunRotation = 0.0f;
	SunRotation += 0.005f;
	Matrix4 sunWorld = Matrix4::RotationY(SunRotation);
	Matrix4 sunWvp = Transpose(sunWorld * view * proj);

	static float skydomeRotation = 0.0f;
	Matrix4 skydomeWorld = Matrix4::RotationY(skydomeRotation);
	Matrix4 skydomeWVP = Transpose(skydomeWorld * view * proj);

	mConstantBuffer.Update(&mercuryWvp);
	mercury.mPlanetTexture.BindPS(0);
	mercury.mPlanetMeshBuffer.Render();

	mConstantBuffer.Update(&venusWvp);
	venus.mPlanetTexture.BindPS(0);
	venus.mPlanetMeshBuffer.Render();

	mConstantBuffer.Update(&earthWvp);
	earth.mPlanetTexture.BindPS(0);
	earth.mPlanetMeshBuffer.Render();

	mConstantBuffer.Update(&moonWvp);
	moon.mPlanetTexture.BindPS(0);
	moon.mPlanetMeshBuffer.Render();

	mConstantBuffer.Update(&marsWvp);
	mars.mPlanetTexture.BindPS(0);
	mars.mPlanetMeshBuffer.Render();

	mConstantBuffer.Update(&sunWvp);
	sun.mPlanetTexture.BindPS(0);
	sun.mPlanetMeshBuffer.Render();

	mConstantBuffer.Update(&skydomeWVP);
	mSkydomeTexture.BindPS(0);
	mSkydomeMeshBuffer.Render();
}

void GameState::DebugUI()
{

}