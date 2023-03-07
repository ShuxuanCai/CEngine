#include "Precompiled.h"
#include "MeshComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "RenderService.h"

#include <Graphics/Inc/MeshBuilder.h>
#include <Graphics/Inc/TextureManager.h>

using namespace CEngine;
using namespace CEngine::Graphics;

void MeshComponent::Initialize()
{
	mRenderObject.meshBuffer.Initialize(mMesh);
	mRenderObject.material = mMaterial;
	if (!mDiffuseMap.empty())
	{
		mRenderObject.diffuseMapId = TextureManager::Get()->LoadTexture(mDiffuseMap);
	}
	if (!mBumpMap.empty())
	{
		mRenderObject.bumpMapId = TextureManager::Get()->LoadTexture(mBumpMap);
	}
	if (!mNormalMap.empty())
	{
		mRenderObject.normalMapId = TextureManager::Get()->LoadTexture(mNormalMap);
	}
	if (!mSpecularMap.empty())
	{
		mRenderObject.specularMapId = TextureManager::Get()->LoadTexture(mSpecularMap);
	}
	auto renderService = GetOwner().GetWorld().GetService<RenderService>();
	renderService->Register(this);
}

void MeshComponent::Terminate()
{
	mRenderObject.Terminate();
	auto renderService = GetOwner().GetWorld().GetService<RenderService>();
	renderService->Unregister(this);
}

void MeshComponent::CreateCube(float size)
{
	mMesh = MeshBuilder::CreateCube(size);
}

void MeshComponent::CreateSphere(int slices, int rings, float radius)
{
	mMesh = MeshBuilder::CreateSphere(slices, rings, radius);
}

void MeshComponent::CreatePlane(int columns, int rows, float size)
{
	mMesh = MeshBuilder::CreatePlane(columns, rows, size);
}

void MeshComponent::SetDiffuseMap(const char* fileName)
{
	mDiffuseMap = fileName;
}

void MeshComponent::SetBumpMap(const char* fileName)
{
	mBumpMap = fileName;
}

void MeshComponent::SetNormalMap(const char* fileName)
{
	mNormalMap = fileName;
}

void MeshComponent::SetSpecularMap(const char* fileName)
{
	mSpecularMap = fileName;
}

void MeshComponent::SetAmbientColor(const Graphics::Color& color)
{
	mMaterial.ambient = color;
}

void MeshComponent::SetDiffuseColor(const Graphics::Color& color)
{
	mMaterial.diffuse = color;
}

void MeshComponent::SetEmissiveColor(const Graphics::Color& color)
{
	mMaterial.emissive = color;
}

void MeshComponent::SetSpecularColor(const Graphics::Color& color)
{
	mMaterial.specular = color;
}

void MeshComponent::SetSpecularPower(float power)
{
	mMaterial.power = power;
}

Graphics::RenderObject& MeshComponent::GetRenderObject()
{
	return mRenderObject;
}

const Graphics::Mesh& MeshComponent::GetMesh() const
{
	return mMesh;
}