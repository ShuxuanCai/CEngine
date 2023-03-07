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
	using Handles = std::vector<CEngine::GameObjectHandle>;

	CEngine::GameWorld mGameWorld;
	Handles mHandles;

	bool mPause = false;
};