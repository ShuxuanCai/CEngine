#pragma once

#include "Sampler.h"
#include"ConstantBuffer.h"
#include "LightTypes.h"
#include "Material.h"
#include "PixelShader.h"
#include "VertexShader.h"

namespace CEngine::Graphics
{
	class Camera;
	class RenderObject;

	class StandardEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		//void SetCamera(const Camera* camera)
		//{
		//	if (camera)
		//	{
		//		// ...
		//	}
		//	else
		//	{

		//	}
		//}
		// So, using &, cause camera never be nullptr
		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetBumpWeight(float weight) { mBumpWeight = weight; }
		
		void UseDiffuseMap(bool use) { mSettingData.useDiffuseMap = use ? 1 : 0; }
		void UseSpecularMap(bool use) { mSettingData.useSpecularMap = use ? 1 : 0; }
		void UseBumpMap(bool use) { mSettingData.useBumpMap = use ? 1 : 0; }
		void UseNormalMap(bool use) { mSettingData.useNormalMap = use ? 1 : 0; }
		
		void DebugUI();

	private:
		struct TransformData
		{
			CEngine::Math::Matrix4 world;
			CEngine::Math::Matrix4 wvp;
			CEngine::Math::Vector3 viewPosition;
			float bumpWeight = 0.0f;
		};

		struct BoneTransformData
		{
			static constexpr size_t MaxBoneCount = 256;
			Math::Matrix4 boneTransforms[MaxBoneCount];
		};

		struct SettingData
		{
			int useDiffuseMap = 1;
			int useSpecularMap = 1;
			int useBumpMap = 1;
			int useNormalMap = 1;
			// [iiii][iiii][iiii][iiii]

			int useShadowMap = 1;
			int useSkinning = 0;
			float depthBias = 0.0f;
			float padding = {};
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using BoneTransformBuffer = ConstantBuffer;
		using LightBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingBuffer = TypedConstantBuffer<SettingData>;

		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		TransformBuffer mTransformBuffer;
		BoneTransformBuffer mBoneTransformBuffer;
		LightBuffer mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingBuffer mSettingBuffer;

		Sampler mSampler;
		SettingData mSettingData;

		float mBumpWeight = 0.0f;
	};
}