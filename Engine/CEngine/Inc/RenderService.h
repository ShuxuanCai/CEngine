#pragma once

#include "Service.h"

namespace CEngine
{
	class CameraService;
	class ModelComponent;
	class MeshComponent;
	class TransformComponent;
	class AnimatorComponent;
	class TerrainService;

	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Render);

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;

		void DebugUI() override;
	
	private:
		friend class ModelComponent;
		friend class MeshComponent;

		void Register(const ModelComponent* modelComponent);
		void Unregister(const ModelComponent* modelComponent);
		void Register(MeshComponent* meshComponent);
		void Unregister(const MeshComponent* meshComponent);

		struct Entry
		{
			const AnimatorComponent* animatorComponent = nullptr;
			const ModelComponent* modelComponent = nullptr;
			const MeshComponent* meshComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
			Graphics::RenderGroup renderGroup;
		};

		using RenderEntries = std::vector<Entry>;
		RenderEntries mRenderEntries;

		const CameraService* mCameraService = nullptr;
		TerrainService* mTerrainService = nullptr;

		Graphics::DirectionalLight mDirectionalLight;
		Graphics::StandardEffect mStandardEffect;
		Graphics::ShadowEffect mShadowEffect;
		Graphics::TerrainEffect mTerrainEffect;

		float mFPS = 0.0f;
	};
}