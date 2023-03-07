#include "GameState.h"

using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;

namespace
{
	Camera RenderReflection(const Camera& camera, float height)
	{
		Vector3 up, position, lookAt;

		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		position.x = camera.GetPosition().x;
		position.y = -camera.GetPosition().y + (height * 2.0f);
		position.z = camera.GetPosition().z;

		lookAt.x = camera.GetDirection().x;
		lookAt.y = -camera.GetDirection().y;
		lookAt.z = camera.GetDirection().z;

		Camera reflectionCamera;
		reflectionCamera.SetLookAt(up);
		reflectionCamera.SetDirection(lookAt);
		reflectionCamera.SetPosition(position);

		return reflectionCamera;
	}
}

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 25.0f, -100.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mReflectionCamera = RenderReflection(mCamera, mHeight);

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mMaterial.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mMaterial.diffuse = { 0.85f, 0.85f, 0.85f, 1.0f };
	mMaterial.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mMaterial.power = 10.0f;

	mPower = 0.15f;

	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();
	mReflectRenderTarget.Initialize(screenWidth, screenHeight, Texture::Format::RGBA_U32);

	mGroundMesh = MeshBuilder::CreatPlanePX(200, 200, 1.0f);
	mGroundMeshBuffer.Initialize(mGroundMesh);
	mMesh = MeshBuilder::CreateSphere(256, 256, 20.0f);
	mMeshBuffer.Initialize(mMesh);
	
	mGroundVertexShader.Initialize(L"../../Assets/Shaders/Reflection.fx", VertexPX::Format);
	mGroundPixelShader.Initialize(L"../../Assets/Shaders/Reflection.fx");

	mBaseVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", Vertex::Format);
	mBasePixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Clamp);
	mGroundTexture.Initialize("../../Assets/Images/white.jpg");
	mTexture.Initialize("../../Assets/Images/water.jpg");

	mPowerBuffer.Initialize();
	mReflectionBuffer.Initialize();
	mReflectionTransformBuffer.Initialize();
	mTransformBuffer.Initialize();
	mScreenQuad.meshBuffer.Initialize(MeshBuilder::CreateScreenQuad());
}

void GameState::Terminate()
{
	mScreenQuad.Terminate();
	mTransformBuffer.Terminate();
	mReflectionTransformBuffer.Terminate();
	mReflectionBuffer.Terminate();
	mPowerBuffer.Terminate();

	mTexture.Terminate();
	mGroundTexture.Terminate();
	mSampler.Terminate();

	mBasePixelShader.Terminate();
	mBaseVertexShader.Terminate();
	mGroundPixelShader.Terminate();
	mGroundVertexShader.Terminate();

	mMeshBuffer.Terminate();
	mGroundMeshBuffer.Terminate();
	mReflectRenderTarget.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float turnSpeed = 1.0f;
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

	mFPS = 1.0f / deltaTime;
}

void GameState::Render()
{
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();

	static float rotation = 0.0f;
	rotation += 0.01f;
	Matrix4 matWorld = Matrix4::RotationY(rotation) * Matrix4::Translation({ 0.0f, 20.0f + mHeight, 0.0f });

	TransformData transformData;
	transformData.wvp = Transpose(matWorld * matView * matProj);
	mTransformBuffer.Update(transformData);
	mTransformBuffer.BindVS(0);

	mBaseVertexShader.Bind();
	mBasePixelShader.Bind();
	mTexture.BindPS(0);
	mSampler.BindPS(0);
	mMeshBuffer.Render();

	mReflectionCamera = RenderReflection(mCamera, mHeight);
	ReflectionTransformData reflectionTransformData;
	ReflectionBufferData reflectionBufferData;
	matProj = mReflectionCamera.GetProjectionMatrix();
	matWorld = Matrix4::Translation({ 0.0f, 0.0f, 0.0f }) * Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	reflectionTransformData.world = Transpose(matWorld);
	reflectionTransformData.view = Transpose(matView);
	reflectionTransformData.projection = Transpose(matProj);
	mReflectionTransformBuffer.Update(reflectionTransformData);
	mReflectionTransformBuffer.BindVS(0);

	Matrix4 matReflection = mReflectionCamera.GetViewMatrix();
	reflectionBufferData.reflectionMatrix = Transpose(matReflection);
	mReflectionBuffer.Update(reflectionBufferData);
	mReflectionBuffer.BindVS(1);
	mReflectRenderTarget.BindPS(1);

	PowerBufferData powerBufferData;
	powerBufferData.power = mPower;
	mPowerBuffer.BindVS(2);
	mPowerBuffer.BindPS(2);
	mPowerBuffer.Update(powerBufferData);

	mGroundVertexShader.Bind();
	mGroundPixelShader.Bind();
	mGroundTexture.BindPS(0);
	mGroundMeshBuffer.Render();

	mReflectRenderTarget.BeginRender();
	mTransformBuffer.BindVS(0);
	mBaseVertexShader.Bind();
	mBasePixelShader.Bind();
	mTexture.BindPS(0);
	mSampler.BindPS(0);
	mMeshBuffer.Render();
	mReflectRenderTarget.EndRender();
}

void GameState::DebugUI()
{
	ImGui::Begin("Reflection", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f", mFPS);

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Rotation", &mRotation.y, 0.01f);
		ImGui::DragFloat("Height", &mHeight, 0.01f);
		ImGui::DragFloat("Power", &mPower, 0.01f, 0.0f, 0.5f);
	}

	static bool normalMap = true;
	static bool specularMap = true;

	ImGui::End();
}