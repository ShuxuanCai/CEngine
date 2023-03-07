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

	CEngine::Math::Vector3 mPosition = CEngine::Math::Vector3::Zero;
	CEngine::Graphics::Color mColor = CEngine::Graphics::Colors::White;
};