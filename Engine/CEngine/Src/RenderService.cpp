#include "Precompiled.h"
#include "RenderService.h"
#include "ModelComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "AnimatorComponent.h"

#include "CameraService.h"
#include "GameWorld.h"
#include "GameObject.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Math;

void RenderService::Initialize()
{
	mCameraService = GetOwner().GetService<CameraService>();

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.4f, 0.4f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);
}

void RenderService::Terminate()
{
	mStandardEffect.Terminate();
	mShadowEffect.Terminate();
}

void RenderService::Update(float deltaTime)
{
	mFPS = 1.0f / deltaTime;
}

void RenderService::Render()
{
	const auto& camera = mCameraService->GetMain();
	mStandardEffect.SetCamera(camera);

	// apply transforms to models
	for (auto& entry : mRenderEntries)
	{
		Transform transform = *entry.transformComponent;
		const ModelComponent* model = entry.modelComponent;
		if (model != nullptr)
		{
			transform.rotation = transform.rotation + model->GetRotationCorrection();
		}
		for (auto& renderObject : entry.renderGroup)
		{
			renderObject.transform = transform;
		}
	}

	mShadowEffect.Begin();
	{
		for (auto& entry : mRenderEntries)
		{
			DrawRenderGroup(mShadowEffect, entry.renderGroup);
		}
	}
	mShadowEffect.End();

	mStandardEffect.Begin();
	{
		for (auto& entry : mRenderEntries)
		{
			DrawRenderGroup(mStandardEffect, entry.renderGroup);
		}
	}
	mStandardEffect.End();
}

void RenderService::DebugUI()
{
	ImGui::Text("FPS: %f", mFPS);
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	mStandardEffect.DebugUI();
	mShadowEffect.DebugUI();
}

void RenderService::Register(const ModelComponent* modelComponent)
{
	Entry& entry = mRenderEntries.emplace_back();

	auto& gameObject = modelComponent->GetOwner();
	entry.modelComponent = modelComponent;
	entry.animatorComponent = gameObject.GetComponent<AnimatorComponent>();
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
	const Animator* animator = nullptr;
	if (entry.animatorComponent != nullptr)
	{
		animator = &entry.animatorComponent->GetAnimator();
	}
	entry.renderGroup = CreatingRenderGroup(modelComponent->GetModelID(), animator);
}

void RenderService::Unregister(const ModelComponent* modelComponent)
{
	auto iter = std::find_if(
		mRenderEntries.begin(),
		mRenderEntries.end(),
		[&](const Entry& entry)
		{
			return entry.modelComponent == modelComponent;
		});
	if (iter != mRenderEntries.end())
	{
		Entry& entry = *iter;
		CleanUpRenderGroup(entry.renderGroup);
		mRenderEntries.erase(iter);
	}
}

void RenderService::Register(MeshComponent* meshComponent)
{
	Entry& entry = mRenderEntries.emplace_back();

	auto& gameObject = meshComponent->GetOwner();
	entry.meshComponent = meshComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
	entry.renderGroup.push_back(meshComponent->GetRenderObject());
}

void RenderService::Unregister(const MeshComponent* meshComponent)
{
	auto iter = std::find_if(
		mRenderEntries.begin(),
		mRenderEntries.end(),
		[&](const Entry& entry)
		{
			return entry.meshComponent == meshComponent;
		});
	if (iter != mRenderEntries.end())
	{
		Entry& entry = *iter;
		CleanUpRenderGroup(entry.renderGroup);
		mRenderEntries.erase(iter);
	}
}