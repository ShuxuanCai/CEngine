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
	//std::vector<CEngine::Graphics::VertexPC> mVertices;

	CEngine::Graphics::Camera mCamera;

	CEngine::Graphics::MeshPC mCubeMesh;
	CEngine::Graphics::MeshPC mPlaneMesh;
	CEngine::Graphics::MeshPC mCylinderMesh;
	CEngine::Graphics::MeshPC mSphereMesh;

	CEngine::Graphics::VertexShader mVertexShader;
	CEngine::Graphics::PixelShader mPixelShader;

	CEngine::Graphics::ConstantBuffer mConstantBuffer;

	CEngine::Graphics::MeshBuffer mCubeMeshBuffer;
	CEngine::Graphics::MeshBuffer mPlaneMeshBuffer;
	CEngine::Graphics::MeshBuffer mCylinderMeshBuffer;
	CEngine::Graphics::MeshBuffer mSphereMeshBuffer;
};