#pragma once

#include "Component.h"
#include <Graphics/Inc/MeshTypes.h>
#include <Graphics/Inc/RenderObject.h>

namespace CEngine
{
	class MeshComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Mesh);

		void Initialize() override;
		void Terminate() override;

		void CreateCube(float size);
		void CreateSphere(int slices, int rings, float radius);
		void CreatePlane(int columns, int rows, float size);

		void SetDiffuseMap(const char* fileName);
		void SetBumpMap(const char* fileName);
		void SetNormalMap(const char* fileName);
		void SetSpecularMap(const char* fileName);

		void SetAmbientColor(const Graphics::Color& color);
		void SetDiffuseColor(const Graphics::Color& color);
		void SetEmissiveColor(const Graphics::Color& color);
		void SetSpecularColor(const Graphics::Color& color);
		void SetSpecularPower(float power);

		Graphics::RenderObject& GetRenderObject();
		const Graphics::Mesh& GetMesh() const;

	protected:
		Graphics::Mesh mMesh;
		Graphics::Material mMaterial;
		Graphics::RenderObject mRenderObject;

		std::string mDiffuseMap;
		std::string mBumpMap;
		std::string mNormalMap;
		std::string mSpecularMap;
	};
}
