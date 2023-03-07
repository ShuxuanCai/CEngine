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
	CEngine::Graphics::ShadowEffect mShadowEffect;

	CEngine::Graphics::RenderGroup mCharacter;
	CEngine::Graphics::RenderObject mGroundRenderObject;

	CEngine::Graphics::Animation mBallAnimation;

	float mFPS = 0.0f;
	bool mPause = false;
};