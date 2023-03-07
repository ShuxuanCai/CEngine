#pragma once

#include "Colors.h"

using namespace CEngine::Math;

namespace CEngine::Graphics
{
	/*class Camera;

	namespace SimpleDraw
	{
		void StaticInitialize(uint32_t maxVertexCount);
		void StaticTerminate();

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color);

		void AddPlane(const Math::Vector3& center, int columns, int rows, float spacing, Color color);
		void AddFilledPlane(const Math::Vector3& center, int columns, int rows, float spacing, Color color);

		void AddTransform(const Math::Matrix4& transform);
		
		void AddAABB(const Math::Vector3& center, const Math::Vector3& extend, Color color);
		void AddAABB(const Math::AABB& aabb, Color color);

		void AddFilledAABB(const Math::Vector3& center, const Math::Vector3& extend, Color color);
		void AddFilledAABB(const Math::AABB& aabb, Color color);

		void AddSphere(const Math::Vector3& center, int slices, int rings, float radius, Color color);
		void AddSphere(const Math::Sphere& sphere, int slices, int rings, Color color);

		void AddFilledSphere(const Math::Vector3& center, int slices, int rings, float radius, Color color);
		void AddFilledSphere(const Math::Sphere& sphere, int slices, int rings, Color color);

		void Render(const Camera& camera);
	}*/

	class Camera;

	namespace SimpleDraw
	{
		void StaticInitialize(uint32_t maxVertexCount);
		void StaticTerminate();

		void AddLine(const Vector3& v0, const Vector3& v1, Color color);
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, Color color);

		void AddAABB(const Vector3& min, const Vector3& max, Color color);
		void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, Color color);

		void AddFilledAABB(const Vector3& min, const Vector3& max, Color color);
		void AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, Color color);

		void AddSphere(int slices, int rings, float radius, Color color);

		void AddGroundPlane(float size, Color color);

		void AddTransform(const Matrix4 matrix);

		void Render(const Camera& camera);
	}
}