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
	void CameraContral(float deltaTime);

	CEngine::Graphics::Camera mCamera;
	CEngine::Graphics::DirectionalLight mDirectionalLight;

	CEngine::Graphics::StandardEffect mStandardEffect;
	CEngine::Graphics::ShadowEffect mShadowEffect;

	CEngine::Graphics::RenderGroup mCharacter;
	CEngine::Graphics::ModelID mCharacterModelID;
	CEngine::Graphics::Animator mCharacterAnimator;
	CEngine::Graphics::RenderObject mGroundRenderObject;

	CEngine::Graphics::Animation mBallAnimation;

	bool mDrawSkeleton = false;
	float mFPS = 0.0f;
	bool mPause = false;
};