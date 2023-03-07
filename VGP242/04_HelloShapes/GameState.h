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
	std::vector<CEngine::Graphics::VertexPC> mVertices;

	CEngine::Graphics::VertexShader mVertexShader;
	CEngine::Graphics::PixelShader mPixelShader;

	CEngine::Graphics::MeshBuffer mMeshBuffer;
};