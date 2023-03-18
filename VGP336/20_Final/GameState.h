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
	void InitializeParticles(int maxParticles);

	void UseRawParticles(int count);

	CEngine::Graphics::Camera mCamera;
	CEngine::Physics::PhysicsWorld mPhysicsWorld;

	std::vector<CEngine::Physics::Particle*> mParticles;

	CEngine::Graphics::MeshPX mMeshPlane;
	CEngine::Graphics::MeshBuffer mMeshBuffer;
	CEngine::Graphics::VertexShader mVertexShader;
	CEngine::Graphics::PixelShader mPixelShader;
	CEngine::Graphics::Texture mTexture;
	CEngine::Graphics::Sampler mSampler;
	CEngine::Graphics::ConstantBuffer mConstantBuffer;

	// ImGui
	std::vector<float> mVecFrames;
	const size_t mMaxFrameSize = 100;
};