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
	CEngine::Graphics::Camera mCamera;
	CEngine::Graphics::DirectionalLight mDirectionalLight;

	CEngine::Graphics::StandardEffect mStandardEffect;
	CEngine::Graphics::PostProcessingEffect mPostProcessingEffect;

	CEngine::Graphics::RenderTarget mRenderTarget;

	CEngine::Graphics::Mesh mMesh;
	CEngine::Graphics::RenderObject mEarthRenderObject;
	CEngine::Graphics::RenderObject mScreenQuad;

	float mFPS = 0.0f;
};