#include "Precompiled.h"
#include "StandardEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "AnimationUtil.h"

using namespace CEngine;
using namespace CEngine::Graphics;

void StandardEffect::Initialize()
{
	mVertexShader.Initialize<Vertex>(L"../../Assets/Shaders/Standard.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");

	mTransformBuffer.Initialize();
	mBoneTransformBuffer.Initialize(256 * sizeof(Math::Matrix4));
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void StandardEffect::Terminate()
{
	mSampler.Terminate();

	mSettingBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mBoneTransformBuffer.Terminate();
	mTransformBuffer.Terminate();
	
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void StandardEffect::Begin()
{
	ASSERT(mCamera != nullptr, "StandardEffect - no camera set!");
	ASSERT(mDirectionalLight != nullptr, "StandardEffect - no light set!");

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mBoneTransformBuffer.BindVS(1);

	mLightBuffer.BindVS(2);
	mLightBuffer.BindPS(2);

	mMaterialBuffer.BindPS(3);

	mSettingBuffer.BindVS(4);
	mSettingBuffer.BindPS(4);

	mSampler.BindVS(0);
	mSampler.BindPS(0);
}

void StandardEffect::End()
{

}

void StandardEffect::Render(const RenderObject& renderObject)
{
	const auto& matWorld = renderObject.transform.GetMatrix4();
	const auto& matView = mCamera->GetViewMatrix();
	const auto& matProj = mCamera->GetProjectionMatrix();

	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = mCamera->GetPosition();
	transformData.bumpWeight = mBumpWeight;
	mTransformBuffer.Update(transformData);

	mLightBuffer.Update(*mDirectionalLight);
	mMaterialBuffer.Update(renderObject.material);

	if (renderObject.skeleton != nullptr)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransform(renderObject.modelId, boneTransforms, renderObject.animator);
		AnimationUtil::ApplyBoneOffset(renderObject.modelId, boneTransforms);
		for (auto& transform : boneTransforms)
		{
			transform = Math::Transpose(transform);
		}

		boneTransforms.resize(256);
		mBoneTransformBuffer.Update(boneTransforms.data());
	}

	SettingData settingData;
	if (mSettingData.useDiffuseMap == 0 || renderObject.diffuseMapId == 0)
		settingData.useDiffuseMap = 0; 
	if (mSettingData.useSpecularMap == 0 || renderObject.specularMapId == 0)
		settingData.useSpecularMap = 0;
	if (mSettingData.useBumpMap == 0 || renderObject.bumpMapId == 0)
		settingData.useBumpMap = 0;
	if (mSettingData.useNormalMap == 0 || renderObject.normalMapId == 0)
		settingData.useNormalMap = 0;
	//settingData.useSkinning = (renderObject.skeleton != nullptr);
	mSettingBuffer.Update(settingData);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapId, 0);
	tm->BindVS(renderObject.bumpMapId, 1);
	tm->BindPS(renderObject.specularMapId, 2);
	tm->BindPS(renderObject.normalMapId, 3);

	renderObject.meshBuffer.Render();
}

void StandardEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void StandardEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void StandardEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("StandardEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("BumpWeight", &mBumpWeight, 0.01f, 0.0f, 1.0f);

		bool useNormalMap = (mSettingData.useNormalMap == 1);
		ImGui::Checkbox("Use Normal Map", &useNormalMap);
		mSettingData.useNormalMap = useNormalMap ? 1 : 0;

		bool useDiffuseMap = (mSettingData.useDiffuseMap == 1);
		ImGui::Checkbox("Use Diffuse Map", &useDiffuseMap);
		mSettingData.useDiffuseMap = useDiffuseMap ? 1 : 0;

		bool useBumpMap = (mSettingData.useBumpMap == 1);
		ImGui::Checkbox("Use Bump Map", &useBumpMap);
		mSettingData.useBumpMap = useBumpMap ? 1 : 0;

		bool useSpecularMap = (mSettingData.useSpecularMap == 1);
		ImGui::Checkbox("Use Specular Map", &useSpecularMap);
		mSettingData.useSpecularMap = useSpecularMap ? 1 : 0;
	}
}