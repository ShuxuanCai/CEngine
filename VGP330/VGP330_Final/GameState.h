#pragma once

#include <CEngine/Inc/CEngine.h>

class GameState : public CEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	struct TransformData
	{
		CEngine::Math::Matrix4 wvp;
	};

	struct ReflectionTransformData
	{
		CEngine::Math::Matrix4 world;
		CEngine::Math::Matrix4 view;
		CEngine::Math::Matrix4 projection;
	};

	struct ReflectionBufferData
	{
		CEngine::Math::Matrix4 reflectionMatrix;
	};

	struct Foo // Memory aligment is based on the largest member variable - 8
	{
		double d; // 8
		bool b; // 1
		int i; // 4
	};

	struct PowerBufferData // 16
	{
		// CEngine::Math::Matrix4 m1; // 64
		// CEngine::Math::Matrix4 m2;
		// CEngine::Math::Vector3 f3;
		float power = 0.0f; // 4
		float padding[3] = {}; // 12
	};

	CEngine::Graphics::Camera mCamera;
	CEngine::Graphics::Camera mReflectionCamera;

	CEngine::Graphics::RenderTarget mBaseRenderTarget;
	CEngine::Graphics::RenderTarget mReflectRenderTarget;

	using TransformBuffer = CEngine::Graphics::TypedConstantBuffer<TransformData>;
	using ReflectionTransformDataBuffer = CEngine::Graphics::TypedConstantBuffer<ReflectionTransformData>;
	using ReflectionBuffer = CEngine::Graphics::TypedConstantBuffer<ReflectionBufferData>;
	using PowerBuffer = CEngine::Graphics::TypedConstantBuffer<PowerBufferData>;

	TransformBuffer mTransformBuffer;
	ReflectionTransformDataBuffer mReflectionTransformBuffer;
	ReflectionBuffer mReflectionBuffer;
	PowerBuffer mPowerBuffer;

	CEngine::Graphics::DirectionalLight mDirectionalLight;

	CEngine::Graphics::VertexShader mGroundVertexShader;
	CEngine::Graphics::PixelShader mGroundPixelShader;

	CEngine::Graphics::VertexShader mBaseVertexShader;
	CEngine::Graphics::PixelShader mBasePixelShader;

	CEngine::Graphics::Sampler mSampler;
	CEngine::Graphics::Material mMaterial;
	CEngine::Graphics::Texture mGroundTexture;
	CEngine::Graphics::Texture mTexture;

	CEngine::Graphics::MeshPX mGroundMesh;
	CEngine::Graphics::MeshBuffer mGroundMeshBuffer;

	CEngine::Graphics::Mesh mMesh;
	CEngine::Graphics::MeshBuffer mMeshBuffer;

	CEngine::Graphics::RenderObject mScreenQuad;

	CEngine::Math::Vector3 mRotation;
	float mFPS = 0.0f;
	float mHeight = 0.0f;
	float mPower = 0.0f;
};


