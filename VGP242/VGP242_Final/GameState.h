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
	struct PlanetInfo
	{
		CEngine::Graphics::MeshPX mPlanetMesh;
		CEngine::Graphics::MeshBuffer mPlanetMeshBuffer;
		CEngine::Graphics::Texture mPlanetTexture;
	};

	CEngine::Graphics::Camera mCamera;
	
	PlanetInfo earth;
	PlanetInfo sun;
	PlanetInfo mercury;
	PlanetInfo venus;
	PlanetInfo mars;
	PlanetInfo moon;

	CEngine::Graphics::MeshPX mSkydomeMesh;

	CEngine::Graphics::VertexShader mVertexShader;
	CEngine::Graphics::PixelShader mPixelShader;

	CEngine::Graphics::ConstantBuffer mConstantBuffer;

	CEngine::Graphics::MeshBuffer mSkydomeMeshBuffer;

	CEngine::Graphics::Texture mSkydomeTexture;
	CEngine::Graphics::Sampler mSampler;

};