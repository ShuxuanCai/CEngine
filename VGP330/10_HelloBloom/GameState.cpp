#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetBumpWeight(0.2f);

	mGaussianBlurEffect.Initialize();
	mGaussianBlurEffect.SetSourceTexture(mBloomRenderTarget);
	mGaussianBlurEffect.BlurIterations() = 10;
	mGaussianBlurEffect.BlurSaturation() = 1.0f;
	
	//mBlurEffect.Initialize();
	//mBlurEffect.SetMode(PostProcessingEffect::Mode::Blur);
	
	mPostProcessingEffect.Initialize();
	mPostProcessingEffect.SetMode(PostProcessingEffect::Mode::None);
	mPostProcessingEffect.SetTexture(&mBaseRenderTarget, 0);
	mPostProcessingEffect.SetTexture(&mGaussianBlurEffect.GetResultTexture(), 1);

	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();
	mBaseRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	mBloomRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	auto tm = TextureManager::Get();
		
	mSunRenderObject.material.emissive = Colors::White;
	mSunRenderObject.material.power = 1.0f;
	mSunRenderObject.diffuseMapId = tm->LoadTexture("sun.jpg");
	mSunRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(512, 512, 5.0f));

	mEarthRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mEarthRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.power = 10.0f;
	mEarthRenderObject.diffuseMapId = tm->LoadTexture("earth.jpg");
	mEarthRenderObject.bumpMapId = tm->LoadTexture("earth_bump.jpg");
	mEarthRenderObject.specularMapId = tm->LoadTexture("earth_spec.jpg");
	mEarthRenderObject.normalMapId = tm->LoadTexture("earth_normal.jpg");
	mEarthRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(512, 512, 1.0f));

	mScreenQuad.meshBuffer.Initialize(MeshBuilder::CreateScreenQuad());
}

void GameState::Terminate()
{
	mScreenQuad.Terminate();
	mEarthRenderObject.Terminate();

	mBloomRenderTarget.Terminate();
	mBaseRenderTarget.Terminate();

	mPostProcessingEffect.Terminate();
	//mBlurEffect.Terminate();
	mGaussianBlurEffect.Terminate();
	mStandardEffect.Terminate();
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

	mFPS = 1.0f / deltaTime;

	// Update earth transform
	Vector3 earthPosition = { 0.0f, 0.0f, -mEarthOffset };
	mEarthRenderObject.transform.position = TransformCoord(earthPosition, Matrix4::RotationY(mEarthRevolution));
	mEarthRenderObject.transform.rotation.y = mEarthRotation;
}

void GameState::Render()
{
	mBaseRenderTarget.BeginRender();
	{
		mStandardEffect.Begin();
		mStandardEffect.Render(mSunRenderObject);
		mStandardEffect.Render(mEarthRenderObject);
		mStandardEffect.End();

		SimpleDraw::AddTransform(Matrix4::Identity());
		SimpleDraw::AddPlane({ 0.0f, -1.0f, 0.0f }, 30, 30, 0.5f, Colors::White);
		SimpleDraw::Render(mCamera);
	}
	mBaseRenderTarget.EndRender();

	mBloomRenderTarget.BeginRender();
	{
		// Swap in black material
		Material dummyMaterial;
		dummyMaterial.power = 1.0f;
		std::swap(mEarthRenderObject.material, dummyMaterial);

		mStandardEffect.Begin();
		mStandardEffect.Render(mSunRenderObject);
		mStandardEffect.Render(mEarthRenderObject);
		mStandardEffect.End();

		// Restore original material
		std::swap(mEarthRenderObject.material, dummyMaterial);
	}
	mBloomRenderTarget.EndRender();

	mGaussianBlurEffect.Begin();
	mGaussianBlurEffect.Render(mScreenQuad);
	mGaussianBlurEffect.End();

	/*RenderTarget* fromRT = &mBloomRenderTarget;
	RenderTarget* toRT = &mBlurRenderTarget;

	for (int i = 0; i < 20; ++i)
	{
		mBlurEffect.SetTexture(fromRT, 0);
		toRT->BeginRender();
			mBlurEffect.Begin();
			mBlurEffect.Render(mScreenQuad);
			mBlurEffect.End();
		toRT->EndRender();
		std::swap(fromRT, toRT);
	}*/

	/*mPostProcessingEffect.SetTexture(&mBaseRenderTarget, 0);
	mPostProcessingEffect.SetTexture(&mBlurRenderTarget, 1);*/
	mPostProcessingEffect.Begin();
	mPostProcessingEffect.Render(mScreenQuad);
	mPostProcessingEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f", mFPS);
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.0f, -1.0f, 1.0f);
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	if (ImGui::CollapsingHeader("Earth", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Earth", &mEarthRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Earth", &mEarthRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Earth", &mEarthRenderObject.material.specular.r);
		ImGui::DragFloat("Power##Earth", &mEarthRenderObject.material.power, 1.0f, 1.0f, 100.0f);

		ImGui::DragFloat("Offset##Earth", &mEarthOffset, 0.01f);
		ImGui::DragFloat("Rotation##Earth", &mEarthRotation, 0.01f);
		ImGui::DragFloat("Revolution##Earth", &mEarthRevolution, 0.01f);
	}

	mStandardEffect.DebugUI();
	mPostProcessingEffect.DebugUI();

	if (ImGui::CollapsingHeader("Blur Setting", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragInt("Blur Iterations", &mGaussianBlurEffect.BlurIterations(), 1, 1, 100);
		ImGui::DragFloat("Blur Saturation", &mGaussianBlurEffect.BlurSaturation(), 0.00f, 1.0f, 100.0f);
	}

	ImGui::End();

	ImGui::Begin("Render Targets", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Base");
	ImGui::Image(mBaseRenderTarget.GetRawData(), { 256, 144 });
	ImGui::Text("Bloom");
	ImGui::Image(mBloomRenderTarget.GetRawData(), { 256, 144 });
	ImGui::Text("Horizontal Blur");
	ImGui::Image(mGaussianBlurEffect.GetHorizontalBlurTexture().GetRawData(), { 256, 144 });
	ImGui::Text("Vertical Blur");
	ImGui::Image(mGaussianBlurEffect.GetVerticalBlurTexture().GetRawData(), { 256, 144 });
	ImGui::End();
}