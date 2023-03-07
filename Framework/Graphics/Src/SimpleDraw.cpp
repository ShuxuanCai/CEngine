#include "Precompiled.h"
#include "SimpleDraw.h"

#include "BlendState.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Math;
using namespace CEngine::Math::Constants;

//namespace
//{
//	class SimpleDrawImpl
//	{
//	public:
//		void Initialize(uint32_t maxVertexCount);
//		void Terminate();
//
//		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color);
//		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, Color color);
//
//		void Render(const Camera& camera);
//
//	private:
//		VertexShader mVertexShader;
//		PixelShader mPixelShader;
//		ConstantBuffer mConstantBuffer;
//		MeshBuffer mMeshBuffer;
//		BlendState mAlphaBlendState;
//
//		std::unique_ptr<VertexPC[]> mLineVertices;
//		std::unique_ptr<VertexPC[]> mFaceVertices;
//		uint32_t mLineVertexCount = 0;
//		uint32_t mFaceVertexCount = 0;
//		uint32_t mMaxVertexCount = 0;
//	};
//
//
//	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
//	{
//		mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/SimpleDraw.fx");
//		mPixelShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx");
//		mConstantBuffer.Initialize(sizeof(Math::Matrix4));
//		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);
//		mAlphaBlendState.Initialize(BlendState::Mode::AlphaBlend);
//
//		mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
//		mFaceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
//		mLineVertexCount = 0;
//		mFaceVertexCount = 0;
//		mMaxVertexCount = maxVertexCount;
//	}
//
//	void SimpleDrawImpl::Terminate()
//	{
//		mAlphaBlendState.Terminate();
//		mMeshBuffer.Terminate();
//		mConstantBuffer.Terminate();
//		mPixelShader.Terminate();
//		mVertexShader.Terminate();
//	}
//
//	void SimpleDrawImpl::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color)
//	{
//		if (mLineVertexCount + 2 <= mMaxVertexCount)
//		{
//			mLineVertices[mLineVertexCount++] = VertexPC{ v0, color };
//			mLineVertices[mLineVertexCount++] = VertexPC{ v1, color };
//		}
//	}
//
//	void SimpleDrawImpl::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, Color color)
//	{
//		if (mFaceVertexCount + 3 <= mMaxVertexCount)
//		{
//			mFaceVertices[mFaceVertexCount++] = VertexPC{ v0, color };
//			mFaceVertices[mFaceVertexCount++] = VertexPC{ v1, color };
//			mFaceVertices[mFaceVertexCount++] = VertexPC{ v2, color };
//		}
//	}
//
//	void SimpleDrawImpl::Render(const Camera& camera)
//	{
//		auto matView = camera.GetViewMatrix();
//		auto matProj = camera.GetProjectionMatrix();
//		auto transform = Math::Transpose(matView * matProj);
//		mConstantBuffer.Update(&transform);
//		mConstantBuffer.BindVS(0);
//
//		mVertexShader.Bind();
//		mPixelShader.Bind();
//
//		mAlphaBlendState.Set();
//
//		mMeshBuffer.Update(mLineVertices.get(), mLineVertexCount);
//		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
//		mMeshBuffer.Render();
//
//		mMeshBuffer.Update(mFaceVertices.get(), mFaceVertexCount);
//		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
//		mMeshBuffer.Render();
//
//		BlendState::ClearState();
//
//		mLineVertexCount = 0;
//		mFaceVertexCount = 0;
//	}
//
//	std::unique_ptr<SimpleDrawImpl> sInstance;
//}
//
//void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
//{
//	sInstance = std::make_unique<SimpleDrawImpl>();
//	sInstance->Initialize(maxVertexCount);
//}
//
//void SimpleDraw::StaticTerminate()
//{
//	sInstance->Terminate();
//	sInstance.reset();
//}
//
//void SimpleDraw::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color)
//{
//	sInstance->AddLine(v0, v1, color);
//}
//
//void SimpleDraw::AddPlane(const Math::Vector3& center, int columns, int rows, float spacing, Color color)
//{
//	float halfX = (columns - 1) * spacing * (-0.5f);
//	float halfZ = (rows - 1) * spacing * (-0.5f);
//
//	std::vector<Vector3> vertices;
//
//	for (int r = 0; r < rows; ++r)
//	{
//		for (int c = 0; c < columns; ++c)
//		{
//			float x = c * spacing + halfX + center.x;
//			float y = center.y;
//			float z = r * spacing + halfZ + center.z;
//			vertices.push_back({x, y, z});
//		}
//	}
//
//	for (int r = 0; r < rows; ++r)
//	{
//		int leftPoint = r * rows;
//		int rightPoint = leftPoint + rows - 1;
//		sInstance->AddLine(vertices[leftPoint], vertices[rightPoint], color);
//	}
//
//	for (int c = 0; c < columns; ++c)
//	{
//		int bottomPoint = c;
//		int topPoint = columns * (columns - 1) + bottomPoint;
//		sInstance->AddLine(vertices[bottomPoint], vertices[topPoint], color);
//	}
//}
//
//void SimpleDraw::AddFilledPlane(const Math::Vector3& center, int columns, int rows, float spacing, Color color)
//{
//	float halfX = (columns - 1) * spacing * (-0.5f);
//	float halfZ = (rows - 1) * spacing * (-0.5f);
//
//	std::vector<Vector3> vertices;
//
//	for (int r = 0; r < rows; ++r)
//	{
//		for (int c = 0; c < columns; ++c)
//		{
//			float x = c * spacing + halfX + center.x;
//			float y = center.y;
//			float z = r * spacing + halfZ + center.z;
//			vertices.push_back({ x, y, z });
//		}
//	}
//
//	for (int r = 0; r < rows - 1; ++r)
//	{
//		for (int c = 0; c < columns - 1; ++c)
//		{
//			const int bottomLeftIndex = (r * columns) + c;
//			sInstance->AddFace(vertices[bottomLeftIndex], vertices[bottomLeftIndex + columns], vertices[bottomLeftIndex + columns + 1], color);
//			sInstance->AddFace(vertices[bottomLeftIndex], vertices[bottomLeftIndex + columns + 1], vertices[bottomLeftIndex + 1], color);
//		}
//	}
//}
//
//void SimpleDraw::AddTransform(const Math::Matrix4& transform)
//{
//	Vector3 x = { transform._11, transform._12, transform._13 };
//	Vector3 y = { transform._21, transform._22, transform._23 };
//	Vector3 z = { transform._31, transform._32, transform._33 };
//	Vector3 o = { 0.0f, 0.0f, 0.0f };
//
//	SimpleDraw::AddLine(o, x, Colors::Red);
//	SimpleDraw::AddLine(o, y, Colors::Green);
//	SimpleDraw::AddLine(o, z, Colors::Blue);
//}
//
//void SimpleDraw::AddAABB(const Vector3& center, const Vector3& extend, Color color)
//{
//	Vector3 backRightTop = extend;
//	Vector3 backLeftTop = { -extend.x, extend.y, extend.z };
//	Vector3 backRightBottom = { extend.x, -extend.y, extend.z };
//	Vector3 backLeftBottom = { -extend.x, -extend.y, extend.z };
//
//	Vector3 frontRightTop = { extend.x, extend.y, -extend.z };
//	Vector3 frontLeftTop = { -extend.x, extend.y, -extend.z };
//	Vector3 frontRightBottom = { extend.x, -extend.y, -extend.z };
//	Vector3 frontLeftBottom = { -extend.x, -extend.y, -extend.z };
//
//	sInstance->AddLine(center + frontRightTop, center + frontLeftTop, color);
//	sInstance->AddLine(center + frontRightTop, center + frontRightBottom, color);
//	sInstance->AddLine(center + frontLeftTop, center + frontLeftBottom, color);
//	sInstance->AddLine(center + frontLeftBottom, center + frontRightBottom, color);
//
//	sInstance->AddLine(center + backRightTop, center + frontRightTop, color);
//	sInstance->AddLine(center + backRightBottom, center + frontRightBottom, color);
//	sInstance->AddLine(center + backLeftBottom, center + frontLeftBottom, color);
//	sInstance->AddLine(center + backLeftTop, center + frontLeftTop, color);
//
//	sInstance->AddLine(center + backRightTop, center + backLeftTop, color);
//	sInstance->AddLine(center + backRightTop, center + backRightBottom, color);
//	sInstance->AddLine(center + backLeftTop, center + backLeftBottom, color);
//	sInstance->AddLine(center + backLeftBottom, center + backRightBottom, color);
//}
//
//void SimpleDraw::AddAABB(const Math::AABB& aabb, Color color)
//{
//	AddAABB(aabb.center, aabb.extend, color);
//}
//
//void SimpleDraw::AddFilledAABB(const Math::Vector3& center, const Math::Vector3& extend, Color color)
//{
//	Vector3 backRightTop = extend;
//	Vector3 backLeftTop = { -extend.x, extend.y, extend.z };
//	Vector3 backRightBottom = { extend.x, -extend.y, extend.z };
//	Vector3 backLeftBottom = { -extend.x, -extend.y, extend.z };
//
//	Vector3 frontRightTop = { extend.x, extend.y, -extend.z };
//	Vector3 frontLeftTop = { -extend.x, extend.y, -extend.z };
//	Vector3 frontRightBottom = { extend.x, -extend.y, -extend.z };
//	Vector3 frontLeftBottom = { -extend.x, -extend.y, -extend.z };
//
//	sInstance->AddFace(center + frontRightTop, center + frontLeftBottom, center + frontLeftTop, color);
//	sInstance->AddFace(center + frontRightTop, center + frontRightBottom, center + frontLeftBottom, color);
//
//	sInstance->AddFace(center + frontRightTop, center + backRightTop, center + backRightBottom, color);
//	sInstance->AddFace(center + frontRightTop, center + backRightBottom, center + frontRightBottom, color);
//
//	sInstance->AddFace(center + frontRightTop, center + backLeftTop, center + backRightTop, color);
//	sInstance->AddFace(center + frontRightTop, center + frontLeftTop, center + backLeftTop, color);
//
//	sInstance->AddFace(center + backLeftTop, center + backRightBottom, center + backRightTop, color);
//	sInstance->AddFace(center + backLeftTop, center + backLeftBottom, center + backRightBottom, color);
//
//	sInstance->AddFace(center + backLeftTop, center + frontLeftTop, center + backLeftBottom, color);
//	sInstance->AddFace(center + frontLeftTop, center + frontLeftBottom, center + backLeftBottom, color);
//
//	sInstance->AddFace(center + frontLeftBottom, center + frontRightBottom, center + backRightBottom, color);
//	sInstance->AddFace(center + frontLeftBottom, center + backRightBottom, center + backLeftBottom, color);
//}
//
//void SimpleDraw::AddFilledAABB(const Math::AABB& aabb, Color color)
//{
//	AddFilledAABB(aabb.center, aabb.extend, color);
//}
//
//void SimpleDraw::AddSphere(const Math::Vector3& center, int slices, int rings, float radius, Color color)
//{
//	const float ringsAvg = Constants::Pi / rings;
//	const float slicesAvg = Constants::TwoPi / slices;
//
//	std::vector<Vector3> vertices;
//
//	for (int r = 0; r < rings; ++r)
//	{
//		for (int s = 0; s < slices; ++s)
//		{
//			float phi = r * ringsAvg;
//			float discRadius = sin(phi) * radius;
//			float x = -sin(s * slicesAvg) * discRadius + center.x;
//			float y = -cos(phi) * radius + center.y;
//			float z = +cos(s * slicesAvg) * discRadius + center.z;
//
//			vertices.push_back({x, y, z});
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		for (int s = 0; s < slices - 1; ++s)
//		{
//			int i = s + (r * slices);
//			sInstance->AddLine(vertices[i], vertices[i + slices], color);
//			sInstance->AddLine(vertices[i], vertices[i + 1], color);
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		int i = (slices - 1) + (r * slices);
//		sInstance->AddLine(vertices[i], vertices[i + slices], color);
//		sInstance->AddLine(vertices[i], vertices[i - slices + 1], color);
//	}
//
//	for (int s = 0; s < slices - 1; ++s)
//	{
//		int i = s + ((rings - 1) * slices);
//		//sInstance->AddLine(vertices[i], vertices[i + slices - 1], color);
//		sInstance->AddLine(vertices[i], vertices[i + 1], color);
//	}
//}
//
//void SimpleDraw::AddSphere(const Math::Sphere& sphere, int slices, int rings, Color color)
//{
//	AddSphere(sphere.center, slices, rings, sphere.radius, color);
//}
//
//void SimpleDraw::AddFilledSphere(const Math::Vector3& center, int slices, int rings, float radius, Color color)
//{
//	const float ringsAvg = Constants::Pi / rings;
//	const float slicesAvg = Constants::TwoPi / slices;
//
//	std::vector<Vector3> vertices;
//
//	for (int r = 0; r < rings; ++r)
//	{
//		for (int s = 0; s < slices; ++s)
//		{
//			float phi = r * ringsAvg;
//			float discRadius = sin(phi) * radius;
//			float x = -sin(s * slicesAvg) * discRadius + center.x;
//			float y = -cos(phi) * radius + center.y;
//			float z = +cos(s * slicesAvg) * discRadius + center.z;
//
//			vertices.push_back({ x, y, z });
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		for (int s = 0; s < slices - 1; ++s)
//		{
//			int i = s + (r * slices);
//			sInstance->AddFace(vertices[i], vertices[i + slices], vertices[i + 1], color);
//			sInstance->AddFace(vertices[i + slices], vertices[i + slices + 1], vertices[i + 1], color);
//		}
//	}
//
//	/*int i = (slices - 1) + ((rings - 1) * slices);
//	sInstance->AddLine(vertices[0], vertices[i + slices], color);
//	sInstance->AddLine(vertices[0], vertices[i + 1], color);*/
//}
//
//void SimpleDraw::AddFilledSphere(const Math::Sphere& sphere, int slices, int rings, Color color)
//{
//	AddFilledSphere(sphere.center, slices, rings, sphere.radius, color);
//}
//
//void SimpleDraw::Render(const Camera& camera)
//{
//	sInstance->Render(camera);
//}

namespace
{
	class SimpleDrawImpl
	{
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();

		void AddLine(const Vector3& v0, const Vector3& v1, Color color);
		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, Color color);

		void Render(const Camera& camera);

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;
		BlendState mAlphaBlendState;

		std::unique_ptr<VertexPC[]> mLineVertices;
		std::unique_ptr<VertexPC[]> mFaceVertices;
		uint32_t mLineVertexCount = 0;
		uint32_t mFaceVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
	};

	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
	{
		mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/SimpleDraw.fx");
		mPixelShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx");
		mConstantBuffer.Initialize(sizeof(Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);
		mAlphaBlendState.Initialize(BlendState::Mode::AlphaBlend);

		mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mFaceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mLineVertexCount = 0;
		mFaceVertexCount = 0;
		mMaxVertexCount = maxVertexCount;
	}

	void SimpleDrawImpl::Terminate()
	{
		mAlphaBlendState.Terminate();
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}

	void SimpleDrawImpl::AddLine(const Vector3& v0, const Vector3& v1, Color color)
	{
		if (mLineVertexCount + 2 <= mMaxVertexCount)
		{
			mLineVertices[mLineVertexCount++] = VertexPC{ v0, color };
			mLineVertices[mLineVertexCount++] = VertexPC{ v1, color };
		}
	}

	void SimpleDrawImpl::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, Color color)
	{
		if (mFaceVertexCount + 3 <= mMaxVertexCount)
		{
			mFaceVertices[mFaceVertexCount++] = VertexPC{ v0, color };
			mFaceVertices[mFaceVertexCount++] = VertexPC{ v1, color };
			mFaceVertices[mFaceVertexCount++] = VertexPC{ v2, color };
		}
	}

	void SimpleDrawImpl::Render(const Camera& camera)
	{
		auto matView = camera.GetViewMatrix();
		auto matProj = camera.GetProjectionMatrix();
		auto transform = Transpose(matView * matProj);
		mConstantBuffer.Update(&transform);
		mConstantBuffer.BindVS(0);

		mVertexShader.Bind();
		mPixelShader.Bind();

		mAlphaBlendState.Set();

		mMeshBuffer.Update(mLineVertices.get(), mLineVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mMeshBuffer.Update(mFaceVertices.get(), mFaceVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Render();

		BlendState::ClearState();

		mLineVertexCount = 0;
		mFaceVertexCount = 0;
	}

	std::unique_ptr<SimpleDrawImpl> sInstance;
}

void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sInstance = std::make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}

void SimpleDraw::StaticTerminate()
{
	sInstance->Terminate();
	sInstance.reset();
}

void SimpleDraw::AddLine(const Vector3& v0, const Vector3& v1, Color color)
{
	sInstance->AddLine(v0, v1, color);
}

void SimpleDraw::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, Color color)
{
	sInstance->AddFace(v0, v1, v2, color);
}

void SimpleDraw::AddAABB(const Vector3& min, const Vector3& max, Color color)
{
	AddAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

void SimpleDraw::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, Color color)
{
	const Vector3 topRightF = { maxX, maxY, minZ };
	const Vector3 botRightF = { maxX, minY, minZ };
	const Vector3 topLeftF = { minX, maxY, minZ };
	const Vector3 botLeftF = { minX, minY, minZ };

	const Vector3 topRightB = { maxX, maxY, maxZ };
	const Vector3 botRightB = { maxX, minY, maxZ };
	const Vector3 topLeftB = { minX, maxY, maxZ };
	const Vector3 botLeftB = { minX, minY, maxZ };

	// Front
	SimpleDraw::AddLine(topRightF, botRightF, color);
	SimpleDraw::AddLine(botRightF, botLeftF, color);
	SimpleDraw::AddLine(botLeftF, topLeftF, color);
	SimpleDraw::AddLine(topLeftF, topRightF, color);

	// Back
	SimpleDraw::AddLine(topRightB, botRightB, color);
	SimpleDraw::AddLine(botRightB, botLeftB, color);
	SimpleDraw::AddLine(botLeftB, topLeftB, color);
	SimpleDraw::AddLine(topLeftB, topRightB, color);

	// Top
	SimpleDraw::AddLine(topRightB, topRightF, color);
	SimpleDraw::AddLine(topLeftF, topLeftB, color);

	// Bottom
	SimpleDraw::AddLine(botRightB, botRightF, color);
	SimpleDraw::AddLine(botLeftF, botLeftB, color);
}

void SimpleDraw::AddFilledAABB(const Vector3& min, const Vector3& max, Color color)
{
	AddFilledAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

void SimpleDraw::AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, Color color)
{
	const Vector3 topRightF = { maxX, maxY, minZ };
	const Vector3 botRightF = { maxX, minY, minZ };
	const Vector3 topLeftF = { minX, maxY, minZ };
	const Vector3 botLeftF = { minX, minY, minZ };

	const Vector3 topRightB = { maxX, maxY, maxZ };
	const Vector3 botRightB = { maxX, minY, maxZ };
	const Vector3 topLeftB = { minX, maxY, maxZ };
	const Vector3 botLeftB = { minX, minY, maxZ };

	// Front
	SimpleDraw::AddFace(topRightF, botRightF, botLeftF, color);
	SimpleDraw::AddFace(botLeftF, topLeftF, topRightF, color);

	// Back
	SimpleDraw::AddFace(topRightB, botLeftB, botRightB, color);
	SimpleDraw::AddFace(botLeftB, topRightB, topLeftB, color);

	// Top
	SimpleDraw::AddFace(topRightB, topRightF, topLeftF, color);
	SimpleDraw::AddFace(topLeftF, topLeftB, topRightB, color);

	// Bot
	SimpleDraw::AddFace(botRightB, botLeftF, botRightF, color);
	SimpleDraw::AddFace(botLeftF, botRightB, botLeftB, color);

	// Right
	SimpleDraw::AddFace(topRightB, botRightB, botRightF, color);
	SimpleDraw::AddFace(botRightF, topRightF, topRightB, color);

	// Left
	SimpleDraw::AddFace(topLeftF, botLeftF, botLeftB, color);
	SimpleDraw::AddFace(botLeftB, topLeftB, topLeftF, color);
}

void SimpleDraw::AddSphere(int slices, int rings, float radius, Color color)
{
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		const float r = static_cast<float>(ring);
		const float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s0 = static_cast<float>(slice);
			float rotation0 = (s0 / (slices)) * TwoPi;
			float s1 = static_cast<float>(slice + 1);
			float rotation1 = (s1 / (slices)) * TwoPi;

			v0 =
			{
				radius * sin(rotation0) * sin(phi),
				radius * cos(phi) + radius,
				radius * cos(rotation0) * sin(phi),
			};

			v1 =
			{
				radius * sin(rotation1) * sin(phi),
				radius * cos(phi) + radius,
				radius * cos(rotation1) * sin(phi),
			};

			SimpleDraw::AddLine(v0, v1, color);

			v0 =
			{
				radius * cos(phi),
				radius * cos(rotation0) * sin(phi) + radius,
				radius * sin(rotation0) * sin(phi),
			};

			v1 =
			{
				radius * cos(phi),
				radius * cos(rotation1) * sin(phi) + radius,
				radius * sin(rotation1) * sin(phi),
			};

			SimpleDraw::AddLine(v0, v1, color);
		}
	}
}

void SimpleDraw::AddGroundPlane(float size, Color color)
{
	const float halfSize = size * 0.5f;
	for (int i = 0; i <= size; ++i)
	{
		SimpleDraw::AddLine({ i - halfSize, 0.0f, -halfSize }, { i - halfSize, 0.0f, halfSize }, color);
		SimpleDraw::AddLine({ -halfSize, 0.0f, i - halfSize }, { halfSize, 0.0f, i - halfSize }, color);
	}
}

void SimpleDraw::AddTransform(const Matrix4 matrix)
{
	const Vector3 Side = { matrix._11, matrix._12, matrix._13 };
	const Vector3 Up = { matrix._21, matrix._22, matrix._23 };
	const Vector3 Look = { matrix._31, matrix._32, matrix._33 };
	const Vector3 Transform = { matrix._41, matrix._42, matrix._43 };

	SimpleDraw::AddLine(Transform, Transform + Side, Colors::Red);
	SimpleDraw::AddLine(Transform, Transform + Up, Colors::Green);
	SimpleDraw::AddLine(Transform, Transform + Look, Colors::Blue);
}

void SimpleDraw::Render(const Camera& camera)
{
	sInstance->Render(camera);
}