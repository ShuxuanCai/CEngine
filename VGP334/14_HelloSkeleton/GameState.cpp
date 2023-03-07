#include "GameState.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Input;
using namespace CEngine::Math;
using namespace CEngine::Graphics::AnimationUtil;

enum class AnimationState : int
{
	Aiming_Idle,     	//0
	Walk,               //1
	Walk_B,		        //2
	Turn_L,		        //3
	Jump		        //4
};

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);

	auto tm = TextureManager::Get();
	auto mm = ModelManager::Get();

	mCharacterModelID = mm->LoadModel("../../Assets/Models/Character/Ch35_nonPBR.model");
	mm->AddAnimation(mCharacterModelID, "../../Assets/Models/Character/rifle_aiming_idle.model");
	mm->AddAnimation(mCharacterModelID, "../../Assets/Models/Character/walking.model");
	mm->AddAnimation(mCharacterModelID, "../../Assets/Models/Character/walking_backwards.model");
	mm->AddAnimation(mCharacterModelID, "../../Assets/Models/Character/turn_left.model");
	mm->AddAnimation(mCharacterModelID, "../../Assets/Models/Character/rifle_jump.model");

	mCharacter = CreatingRenderGroup(mCharacterModelID, &mCharacterAnimator);
	mCharacterAnimator.Initialize(mCharacterModelID);
	mCharacterAnimator.PlayAnimation((int)AnimationState::Aiming_Idle, true);

	mGroundRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGroundRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.power = 10.0f;
	mGroundRenderObject.diffuseMapId = tm->LoadTexture("concrete.jpeg");
	mGroundRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(25, 25, 1.0f));
}

void GameState::Terminate()
{
	CleanUpRenderGroup(mCharacter);
	mGroundRenderObject.Terminate();

	mShadowEffect.Terminate();
	mStandardEffect.Terminate();
}

int animationIndex = 0;
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	CameraContral(deltaTime);

	mCharacterAnimator.Update(deltaTime);
	
	mFPS = 1.0f / deltaTime;

	if (inputSystem->IsKeyPressed(KeyCode::UP))
	{
		mCharacterAnimator.PlayAnimation((int)AnimationState::Walk, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::DOWN))
	{
		mCharacterAnimator.PlayAnimation((int)AnimationState::Walk_B, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::LEFT))
	{
		mCharacterAnimator.PlayAnimation((int)AnimationState::Jump, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::RIGHT))
	{
		mCharacterAnimator.PlayAnimation((int)AnimationState::Turn_L, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::ENTER))
	{
		mCharacterAnimator.PlayAnimation((int)AnimationState::Aiming_Idle, true, 2.0f);
	}
}

void GameState::Render()
{
	mShadowEffect.Begin();
		DrawRenderGroup(mShadowEffect, mCharacter);
	mShadowEffect.End();

	mStandardEffect.Begin();
		if (mDrawSkeleton)
		{
			BoneTransforms boneTransforms;
			AnimationUtil::ComputeBoneTransform(mCharacterModelID, boneTransforms, &mCharacterAnimator);
			//AnimationUtil::CalculteBoneAnimationTransforms(*skeleton, mCharacterAnimator, boneTransforms);
			AnimationUtil::DrawSkeleton(mCharacterModelID, boneTransforms);
		}
		else
		{
			DrawRenderGroup(mStandardEffect, mCharacter);
		}
		mStandardEffect.Render(mGroundRenderObject);
	mStandardEffect.End();

	SimpleDraw::AddTransform(Matrix4::Identity());
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f %s", mFPS, mPause ? "(paused!)" : "");
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.0f, -1.0f, 1.0f);
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	if (ImGui::Checkbox("Show Skeleton", &mDrawSkeleton))
	{

	}

	mStandardEffect.DebugUI();
	mShadowEffect.DebugUI();

	ImGui::End();
}

void GameState::CameraContral(float deltaTime)
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
	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
		mPause = !mPause;
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}