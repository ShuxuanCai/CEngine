#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Math;
using namespace CEngine::Math::Constants;

//namespace
//{
//	Color GetNextColor(int& index)
//	{
//		constexpr Color colorTable[] = {
//			Colors::Coral,
//			Colors::Yellow,
//			Colors::Aqua,
//			Colors::WhiteSmoke,
//			Colors::Magenta,
//			Colors::Azure,
//			Colors::MediumAquamarine,
//			Colors::Navy
//		};
//
//		index = (index + 1) % std::size(colorTable);
//		return colorTable[index];
//	}
//}
//
//MeshPC MeshBuilder::CreateCubePC(float size, Color color)
//{
//	int colorIndex = 0;
//	
//	MeshPC mesh;
//
//	mesh.vertices.push_back({ Vector3{ -size, +size, -size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ +size, +size, -size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ +size, -size, -size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ -size, +size, +size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ +size, +size, +size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ -size, -size, +size }, GetNextColor(colorIndex) });
//	mesh.vertices.push_back({ Vector3{ +size, -size, +size }, GetNextColor(colorIndex) });
//
//	mesh.indices =
//	{
//		0, 1, 2, 1, 3, 2,
//		1, 5, 3, 3, 5, 7,
//		5, 4, 7, 4, 6, 7,
//		4, 0, 6, 6, 0, 2,
//		2, 7, 6, 2, 3, 7,
//		0, 5, 1, 0, 4, 5
//	};
//
//	return mesh;
//}
//
//MeshPC MeshBuilder::CreatePlanePC(int columns, int rows, float spacing)
//{
//	MeshPC mesh;
//
//	float halfX = (columns - 1) * spacing * (-0.5f);
//	float halfZ = (rows - 1) * spacing * (-0.5f);
//
//	for (int r = 0; r < rows; ++r)
//	{
//		for (int c = 0; c < columns; ++c)
//		{
//			float x = c * spacing + halfX;
//			float z = r * spacing + halfZ;
//			mesh.vertices.push_back({ Vector3{x, 0.0f, z}, Colors::Blue });
//		}
//	}
//
//	for (int r = 0; r < rows - 1; ++r)
//	{
//		for (int c = 0; c < columns - 1; ++c)
//		{
//			mesh.indices.push_back((c + 0) + (r + 0) * columns);
//			mesh.indices.push_back((c + 0) + (r + 1) * columns);
//			mesh.indices.push_back((c + 1) + (r + 1) * columns);
//
//			mesh.indices.push_back((c + 0) + (r + 0) * columns);
//			mesh.indices.push_back((c + 1) + (r + 1) * columns);
//			mesh.indices.push_back((c + 1) + (r + 0) * columns);
//
//			/*const int bottomLeftIndex = (r * columns) + c;
//			mesh.indices.push_back(bottomLeftIndex);
//			mesh.indices.push_back(bottomLeftIndex + columns);
//			mesh.indices.push_back(bottomLeftIndex + columns + 1);*/
//		}
//	}
//
//	return mesh;
//}
//
//MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings, float height, float radius)
//{
//	MeshPC mesh;
//
//	const float ringsAvg = height / (rings - 1);
//	const float slicesAvg = Constants::TwoPi / slices;
//	
//	for (int r = 0; r < rings; ++r)
//	{
//		float y = r * ringsAvg;
//
//		for (int s = 0; s <= slices; ++s)
//		{
//			float x = -sin(s * slicesAvg) * radius;
//			float z = +cos(s * slicesAvg) * radius;
//
//			mesh.vertices.push_back({ {x,y,z}, Colors::Red });
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		for (int s = 0; s < slices; ++s)
//		{
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//													   
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
//		}
//	}
//
//	return mesh;
//}
//
//MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
//{
//	MeshPC mesh;
//
//	const float ringsAvg = Constants::Pi / (rings - 1);
//	const float slicesAvg = Constants::TwoPi / slices;
//
//	for (int r = 0; r < rings; ++r)
//	{
//		float phi = r * ringsAvg;
//		float y = -cos(phi) * radius;
//		float discRadius = sin(phi) * radius;
//
//		for (uint32_t s = 0; s <= slices; ++s)
//		{
//			float x = -sin(s * slicesAvg) * discRadius;
//			float z = +cos(s * slicesAvg) * discRadius;
//
//			mesh.vertices.push_back({ {x, y, z}, Colors::Blue });
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		for (int s = 0; s < slices; ++s)
//		{
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
//		}
//	}
//
//	return mesh;
//}
//
//MeshPX MeshBuilder::CreatPlanePX(uint32_t rows, uint32_t columns, float spacing)
//{
//	MeshPX mesh;
//	float xOffset = (columns - 1) * spacing * 0.5f;
//	float zOffset = (rows - 1) * spacing * 0.5f;
//	for (uint32_t c = 0; c < columns; ++c)
//	{
//		float v = static_cast<float>(c) / static_cast<float>(columns);
//		for (uint32_t r = 0; r < rows; ++r)
//		{
//			float x = c * spacing - xOffset;
//			float z = r * spacing - zOffset;
//
//			float u = static_cast<float>(r) / static_cast<float>(rows);
//			mesh.vertices.push_back({ Vector3(x, 0, z), u, v });
//		}
//
//	}
//	for (uint32_t y = 0; y < columns - 1; y++)
//	{
//		for (uint32_t x = 0; x < rows - 1; x++)
//		{
//			mesh.indices.push_back(y * rows + x);
//			mesh.indices.push_back((y + 1) * rows + x + 1);
//			mesh.indices.push_back((y + 1) * rows + x);
//			mesh.indices.push_back(y * rows + x);
//			mesh.indices.push_back(y * rows + x + 1);
//			mesh.indices.push_back((y + 1) * rows + x + 1);
//		}
//	}
//	return mesh;
//}
//
//MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
//{
//	MeshPX mesh;
//
//	const float ringsAvg = Math::Constants::Pi / (rings - 1);
//	const float slicesAvg = Math::Constants::TwoPi / slices;
//
//	const float vStep = 1.0f / (rings - 1);
//	const float uStep = 1.0f / slices;
//
//	for (int r = 0; r < rings; ++r)
//	{
//		float phi = r * ringsAvg;
//		float y = -cos(phi) * radius;
//		float discRadius = sin(phi) * radius;
//		float v = 1.0f - r * vStep;
//
//		for (int s = 0; s <= slices; ++s)
//		{
//			float x = -sin(s * slicesAvg) * discRadius;
//			float z = +cos(s * slicesAvg) * discRadius;
//			float u = s * uStep;
//
//			mesh.vertices.push_back({ {x,y,z}, u, v });
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		for (int s = 0; s < slices; ++s)
//		{
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
//		}
//	}
//
//	return mesh;
//}
//
//MeshPX MeshBuilder::CreateSkydome(int slices, int rings, float radius)
//{
//	MeshPX mesh;
//
//	const float ringsAvg = Math::Constants::Pi / (rings - 1);
//	const float slicesAvg = Math::Constants::TwoPi / slices;
//
//	const float vStep = 1.0f / (rings - 1);
//	const float uStep = 1.0f / slices;
//
//	for (int r = 0; r < rings; ++r)
//	{
//		float phi = r * ringsAvg;
//		float y = -cos(phi) * radius;
//		float discRadius = sin(phi) * radius;
//		float v = 1.0f - r * vStep;
//
//		for (int s = 0; s <= slices; ++s)
//		{
//			float x = -sin(s * slicesAvg) * discRadius;
//			float z = +cos(s * slicesAvg) * discRadius;
//			float u = s * uStep;
//
//			mesh.vertices.push_back({ {x,y,z}, u, v });
//		}
//	}
//
//	for (int r = 0; r < rings - 1; ++r)
//	{
//		for (int s = 0; s < slices; ++s)
//		{
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
//
//			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
//			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
//		}
//	}
//
//	return mesh;
//}
//
//MeshPX MeshBuilder::CreateScreenQuad()
//{
//	MeshPX mesh;
//	mesh.vertices.push_back({ {-1.0f, -1.0f, 0.0f}, 0.0f, 1.0f });
//	mesh.vertices.push_back({ {-1.0f, +1.0f, 0.0f}, 0.0f, 0.0f });
//	mesh.vertices.push_back({ {+1.0f, +1.0f, 0.0f}, 1.0f, 0.0f });
//	mesh.vertices.push_back({ {+1.0f, -1.0f, 0.0f}, 1.0f, 1.0f });
//	mesh.indices = { 0, 1, 2, 0, 2, 3 };
//	return mesh;
//}
//
////Mesh MeshBuilder::CreateCube(float size, Color color)
////{
////
////}
////
////Mesh MeshBuilder::CreateCylinder(int slices, int rings, float height, float radius)
////{
////
////}
//
//Mesh MeshBuilder::CreatePlane(int columns, int rows, float spacing)
//{
//	ASSERT(columns >= 2 && rows >= 2, "Invaild arguments for plane.");
//	ASSERT(spacing > 0.0f, "Invaild arguments for plane.");
//
//	Mesh mesh;
//
//	const size_t vertexCount = columns * rows;
//	const size_t indexCount = (columns - 1) * (rows - 1) * 6;
//	const float width = (columns - 1) * spacing;
//	const float length = (rows - 1) * spacing;
//	const float offsetX = width * -0.5f;
//	const float offsetZ = length * -0.5f;
//	const float uStep = 1.0f / (columns - 1);
//	const float vStep = 1.0f / (rows - 1);
//
//	mesh.vertices.reserve(vertexCount);
//	mesh.indices.reserve(indexCount);
//
//	for (uint32_t r = 0; r < rows; ++r)
//	{
//		for (uint32_t c = 0; c < columns; ++c)
//		{
//			const float x = (c * spacing) + offsetX;
//			const float y = 0.0f;
//			const float z = (r * spacing) + offsetZ;
//			const float u = c * uStep;
//			const float v = 1.0f - (r * vStep);
//
//
//			mesh.vertices.push_back(
//				{ {x,y,z},
//				Math::Vector3::YAxis,
//				Math::Vector3::XAxis,
//				u, v }
//			);
//		}
//	}
//
//	for (uint32_t r = 0; r < rows - 1; ++r)
//	{
//		for (uint32_t c = 0; c < columns - 1; ++c)
//		{
//			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
//			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
//			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
//
//			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
//			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
//			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
//		}
//	}
//
//	return mesh;
//}
//
//Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
//{
//	Mesh mesh;
//
//	const size_t columns = slices + 1;
//	const size_t rows = rings;
//	const size_t vertexCount = columns * rows;
//	const size_t indexCount = (columns - 1) * (rows - 1) * 6;
//
//	const float thetaStep = Math::Constants::TwoPi / slices;
//	const float phiStep = Math::Constants::Pi / (rings - 1);
//	const float uStep = 1.0f / (columns - 1);
//	const float vStep = 1.0f / (rows - 1);
//
//	mesh.vertices.reserve(vertexCount);
//	mesh.indices.reserve(indexCount);
//
//	for (uint32_t r = 0; r < rows; ++r)
//	{
//		for (uint32_t c = 0; c < columns; ++c)
//		{
//			const float t = c * thetaStep;
//			const float p = r * phiStep;
//			const float discRadius = radius * sin(p);
//			const float x = -sin(t) * discRadius;
//			const float y = -cos(p) * radius;
//			const float z = cos(t) * discRadius;
//			const Math::Vector3 normal = Math::Normalize(Vector3{ x,y,z });
//			const Math::Vector3 tangent = Math::Normalize(Vector3{ -normal.z,0.0f,normal.x });
//			const float u = c * uStep;
//			const float v = 1.0f - (r * vStep);
//
//			mesh.vertices.push_back({ {x,y,z},normal,tangent, u,v });
//		}
//	}
//
//	for (uint32_t r = 0; r < rows - 1; ++r)
//	{
//		for (uint32_t c = 0; c < columns - 1; ++c)
//		{
//			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
//			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
//			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
//
//			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
//			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
//			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
//		}
//	}
//
//	return mesh;
//}

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] =
		{
			Colors::Red,
			Colors::Green,
			Colors::Orange,
			Colors::Blue,
			Colors::Magenta,
			Colors::Cyan,
			Colors::LightGray,
			Colors::GreenYellow,
			Colors::LightSalmon,
			Colors::SpringGreen,
			Colors::Yellow,
			Colors::Firebrick
		};

		index %= std::size(colorTable);

		return colorTable[index++];
	}
}

#pragma region PC

#pragma region Cube PC

MeshPC MeshBuilder::CreateCubePC(float size)
{
	int colorIndex = 0;

	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, GetNextColor(colorIndex) }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, GetNextColor(colorIndex) }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, GetNextColor(colorIndex) }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, GetNextColor(colorIndex) }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, GetNextColor(colorIndex) }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, GetNextColor(colorIndex) }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, GetNextColor(colorIndex) }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, GetNextColor(colorIndex) }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color)
{
	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, color }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, color }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, color }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, color }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, color }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, color }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, color }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, color }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color1, Color color2)
{
	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, color1 }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, color2 }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, color1 }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, color2 }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, color2 }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, color1 }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, color2 }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, color1 }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color1, Color color2, Color color3, Color color4)
{
	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, color1 }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, color2 }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, color3 }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, color4 }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, color3 }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, color4 }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, color1 }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, color2 }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

#pragma endregion

#pragma region Plane PC

MeshPC MeshBuilder::CreatePlanePC(int columns, int rows, float spacing)
{
	int colorIndex = 0;

	MeshPC mesh;
	const float halfHeight = rows * spacing * 0.5f;
	const float halfWidth = columns * spacing * 0.5f;

	// Add Vertices
	for (int i = 0; i < rows + 1; ++i)
	{
		for (int j = 0; j < columns + 1; ++j)
		{
			mesh.vertices.push_back
			({
				Vector3
				{
					(j * spacing) - halfWidth,
					0,
					(i * spacing) - halfHeight
				},
				GetNextColor(colorIndex) });
		}
	}

	PlaneIndices(mesh, columns + 1, rows + 1);

	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int columns, int rows, float spacing, Color color)
{
	MeshPC mesh;
	const float halfHeight = rows * spacing * 0.5f;
	const float halfWidth = columns * spacing * 0.5f;

	// Add Vertices
	for (int i = 0; i < rows + 1; ++i)
	{
		for (int j = 0; j < columns + 1; ++j)
		{
			mesh.vertices.push_back
			({
				Vector3
				{
					(j * spacing) - halfWidth,
					0,
					(i * spacing) - halfHeight
				},
				color
				});
		}
	}

	PlaneIndices(mesh, columns + 1, rows + 1);

	return mesh;
}

#pragma endregion

#pragma region Cylinder PC

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
	int colorIndex = 0;

	MeshPC mesh;
	const float halfHeight = rings * 0.5f;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / rings);

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					sin(rotation),
					ring - halfHeight,
					-cos(rotation),
				},
				GetNextColor(colorIndex)
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	CreateCapVerticesPC(mesh, rings, colorIndex);
	CreateCapIndices(mesh, slices, rings);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings, float height, float radius)
{
	MeshPC mesh;

	const float ringsAvg = height / (rings - 1);
	const float slicesAvg = Constants::TwoPi / slices;
	
	for (int r = 0; r < rings; ++r)
	{
		float y = r * ringsAvg;

		for (int s = 0; s <= slices; ++s)
		{
			float x = -sin(s * slicesAvg) * radius;
			float z = +cos(s * slicesAvg) * radius;

			mesh.vertices.push_back({ {x,y,z}, Colors::Red });
		}
	}

	for (int r = 0; r < rings - 1; ++r)
	{
		for (int s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
													   
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
		}
	}

	return mesh;
}

#pragma endregion

#pragma region Sphere PC

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
	int colorIndex = 0;

	MeshPC mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi),
				},
				GetNextColor(colorIndex)
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius, Color color)
{
	MeshPC mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi),
				},
				color
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

#pragma endregion

MeshPC MeshBuilder::CreateDonutPC(int slices, int rings, float radius)
{
	int colorIndex = 0;

	MeshPC mesh;
	const float halfHeight = radius * 0.5f;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float ringRadius = sin(r / (rings - 1) * Pi) * radius;
		float phi = ring * (Pi / rings);

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					sin(rotation) * ringRadius,
					radius * cos(phi) * sin(ringRadius),
					cos(rotation) * ringRadius,
				}
			, GetNextColor(colorIndex)
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

void MeshBuilder::CreateCapVerticesPC(MeshPC& mesh, int rows, int& colorIndex)
{
	const float halfHeight = rows * 0.5f;

	mesh.vertices.push_back
	({
		Vector3
		{
			0.0f,
			0.0f - halfHeight,
			0.0f,
		}
	, GetNextColor(colorIndex)
		});

	mesh.vertices.push_back
	({
		Vector3
		{
			0.0f,
			rows - 1.0f - halfHeight,
			0.0f,
		}
	, GetNextColor(colorIndex)
		});
}

#pragma endregion

#pragma region PX

MeshPX MeshBuilder::CreateCubePX(float size)
{
	MeshPX mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0, 1 }); // Top Right Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 1, 1 }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 1, 0 }); // Bottom Left Close

	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0, 1 }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 1, 0 }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0, 0 }); // Top Left Close

	// BACK
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 0, 1 }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 1, 1 }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 1, 0 }); // Bottom Right Far

	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 0, 1 }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 1, 0 }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0, 0 }); // Top Right Far

	// RIGHT
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0, 1 }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 1, 1 }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 1, 0 }); // Bottom Right Close

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0, 1 }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 1, 0 }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0, 0 }); // Top Right Close

	// Left
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0, 1 }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 1, 1 }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 1, 0 }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0, 1 }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 1, 0 }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 0, 0 }); // Top Left Far

	// Top
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0, 1 }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 1, 1 }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 1, 0 }); // Top Left Close

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0, 1 }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 1, 0 }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 0, 0 }); // Top Left Far

	// Bottom
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0, 1 }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 1, 1 }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 1, 0 }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0, 1 }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 1, 0 }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 0, 0 }); // Bottom Left Close

	int i = 0;
	for (const auto& vertex : mesh.vertices)
	{
		mesh.indices.push_back(i);
		++i;
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSkyBox(float size)
{
	MeshPX mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0.5f, 0.33f }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 0.25f, 0.66f }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0.5f, 0.66f }); // Bottom Right Close

	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0.5f, 0.33f }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 0.25f, 0.66f }); // Bottom Left Close

	// BACK
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 1.0f, 0.33f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 0.75f, 0.66f }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 1.0f, 0.66f }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 1.0f, 0.33f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0.75f, 0.33f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 0.75f, 0.66f }); // Bottom Right Far

	// RIGHT
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0.75f, 0.33f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0.5f, 0.66f }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 0.75f, 0.66f }); // Bottom Right Far

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0.75f, 0.33f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0.5f, 0.33f }); // Top Right Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0.5f, 0.66f }); // Bottom Right Close

	// Left
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 0.0f, 0.66f }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 0.25f, 0.66f }); // Bottom Left Close

	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 0.0f, 0.33f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 0.0f, 0.66f }); // Bottom Left Far

	// Top
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0.5f,  0.0f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, 0.5f, 0.33f }); // Top Right Close

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, 0.5f,  0.0f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, 0.25f,  0.0f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, 0.25f, 0.33f }); // Top Left Close

	// Bottom
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0.5f, 0.66f }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 0.25f,  1.0f }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, 0.5f,  1.0f }); // Bottom Right Far

	mesh.vertices.push_back({ Vector3{  size, -size, -size }, 0.5f, 0.66f }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, 0.25f, 0.66f }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, 0.25f,  1.0f }); // Bottom Left Far

	int i = 0;
	for (const auto& vertex : mesh.vertices)
	{
		mesh.indices.push_back(i);
		++i;
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
	MeshPX mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi),
				},
				u, v
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

MeshPX MeshBuilder::CreateSkySpherePX(int slices, int rings, float radius)
{
	MeshPX mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * cos(rotation) * sin(phi),
					radius * cos(phi),
					radius * sin(rotation) * sin(phi),
				},
				u, v
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
	MeshPX mesh;
	mesh.vertices.push_back({ { -1.0f, -1.0f, 0.0f }, 0.0f, 1.0f });
	mesh.vertices.push_back({ { -1.0f, +1.0f, 0.0f }, 0.0f, 0.0f });
	mesh.vertices.push_back({ { +1.0f, +1.0f, 0.0f }, 1.0f, 0.0f });
	mesh.vertices.push_back({ { +1.0f, -1.0f, 0.0f }, 1.0f, 1.0f });
	mesh.indices = { 0, 1, 2, 0, 2, 3 };
	return mesh;
}

MeshPX MeshBuilder::CreatPlanePX(uint32_t rows, uint32_t columns, float spacing)
{
	MeshPX mesh;
	float xOffset = (columns - 1) * spacing * 0.5f;
	float zOffset = (rows - 1) * spacing * 0.5f;
	for (uint32_t c = 0; c < columns; ++c)
	{
		float v = static_cast<float>(c) / static_cast<float>(columns);
		for (uint32_t r = 0; r < rows; ++r)
		{
			float x = c * spacing - xOffset;
			float z = r * spacing - zOffset;

			float u = static_cast<float>(r) / static_cast<float>(rows);
			mesh.vertices.push_back({ Vector3(x, 0, z), u, v });
		}

	}
	for (uint32_t y = 0; y < columns - 1; y++)
	{
		for (uint32_t x = 0; x < rows - 1; x++)
		{
			mesh.indices.push_back(y * rows + x);
			mesh.indices.push_back((y + 1) * rows + x + 1);
			mesh.indices.push_back((y + 1) * rows + x);
			mesh.indices.push_back(y * rows + x);
			mesh.indices.push_back(y * rows + x + 1);
			mesh.indices.push_back((y + 1) * rows + x + 1);
		}
	}
	return mesh;
}

MeshPX MeshBuilder::CreateSkydome(int slices, int rings, float radius)
{
	MeshPX mesh;

	const float ringsAvg = Math::Constants::Pi / (rings - 1);
	const float slicesAvg = Math::Constants::TwoPi / slices;

	const float vStep = 1.0f / (rings - 1);
	const float uStep = 1.0f / slices;

	for (int r = 0; r < rings; ++r)
	{
		float phi = r * ringsAvg;
		float y = -cos(phi) * radius;
		float discRadius = sin(phi) * radius;
		float v = 1.0f - r * vStep;

		for (int s = 0; s <= slices; ++s)
		{
			float x = -sin(s * slicesAvg) * discRadius;
			float z = +cos(s * slicesAvg) * discRadius;
			float u = s * uStep;

			mesh.vertices.push_back({ {x,y,z}, u, v });
		}
	}

	for (int r = 0; r < rings - 1; ++r)
	{
		for (int s = 0; s < slices; ++s)
		{
			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
			mesh.indices.push_back((s + 0) + (r + 1) * (slices + 1));

			mesh.indices.push_back((s + 0) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 0) * (slices + 1));
			mesh.indices.push_back((s + 1) + (r + 1) * (slices + 1));
		}
	}

	return mesh;
}

#pragma endregion

#pragma region Standard

Mesh MeshBuilder::CreateCube(float size)
{
	Mesh mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector3::ZAxis, Vector3::XAxis, 0.5f, 0.33f }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector3::ZAxis, Vector3::XAxis, 0.25f, 0.66f }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector3::ZAxis, Vector3::XAxis, 0.5f, 0.66f }); // Bottom Right Close

	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector3::ZAxis, Vector3::XAxis, 0.5f, 0.33f }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector3::ZAxis, Vector3::XAxis, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector3::ZAxis, Vector3::XAxis, 0.25f, 0.66f }); // Bottom Left Close

	// BACK
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector3::ZAxis, -Vector3::XAxis, 1.0f, 0.33f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector3::ZAxis, -Vector3::XAxis, 0.75f, 0.66f }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector3::ZAxis, -Vector3::XAxis, 1.0f, 0.66f }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector3::ZAxis, -Vector3::XAxis, 1.0f, 0.33f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector3::ZAxis, -Vector3::XAxis, 0.75f, 0.33f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector3::ZAxis, -Vector3::XAxis, 0.75f, 0.66f }); // Bottom Right Far

	// RIGHT
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector3::XAxis, Vector3::ZAxis, 0.75f, 0.33f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector3::XAxis, Vector3::ZAxis, 0.5f, 0.66f }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector3::XAxis, Vector3::ZAxis, 0.75f, 0.66f }); // Bottom Right Far
																	   			   
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector3::XAxis, Vector3::ZAxis, 0.75f, 0.33f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector3::XAxis, Vector3::ZAxis, 0.5f, 0.33f }); // Top Right Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector3::XAxis, Vector3::ZAxis, 0.5f, 0.66f }); // Bottom Right Close

	// Left
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, -Vector3::XAxis, -Vector3::ZAxis, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, -Vector3::XAxis, -Vector3::ZAxis, 0.0f, 0.66f }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, -Vector3::XAxis, -Vector3::ZAxis, 0.25f, 0.66f }); // Bottom Left Close
															  				   
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, -Vector3::XAxis, -Vector3::ZAxis, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, -Vector3::XAxis, -Vector3::ZAxis, 0.0f, 0.33f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, -Vector3::XAxis, -Vector3::ZAxis, 0.0f, 0.66f }); // Bottom Left Far

	// Top
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector3::YAxis, Vector3::XAxis, 0.5f,  0.0f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector3::YAxis, Vector3::XAxis, 0.25f, 0.33f }); // Top Left Close
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector3::YAxis, Vector3::XAxis, 0.5f, 0.33f }); // Top Right Close
																	   
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector3::YAxis, Vector3::XAxis, 0.5f,  0.0f }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector3::YAxis, Vector3::XAxis, 0.25f,  0.0f }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector3::YAxis, Vector3::XAxis, 0.25f, 0.33f }); // Top Left Close

	// Bottom
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, -Vector3::YAxis, -Vector3::XAxis, 0.5f, 0.66f }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, -Vector3::YAxis, -Vector3::XAxis, 0.25f,  1.0f }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, -Vector3::YAxis, -Vector3::XAxis, 0.5f,  1.0f }); // Bottom Right Far
															  
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, -Vector3::YAxis, -Vector3::XAxis, 0.5f, 0.66f }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, -Vector3::YAxis, -Vector3::XAxis, 0.25f, 0.66f }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, -Vector3::YAxis, -Vector3::XAxis, 0.25f,  1.0f }); // Bottom Left Far

	int i = 0;
	for (const auto& vertex : mesh.vertices)
	{
		mesh.indices.push_back(i);
		++i;
	}

	return mesh;
}

Mesh MeshBuilder::CreatePlane(int columns, int rows, float spacing)
{
	int colorIndex = 0;

	Mesh mesh;

	const float halfHeight = rows * spacing * 0.5f;
	const float halfWidth = columns * spacing * 0.5f;

	// Add Vertices
	for (int i = 0; i < rows + 1; ++i)
	{
		float r = static_cast<float>(i);

		for (int j = 0; j < columns + 1; ++j)
		{
			float s = static_cast<float>(j);

			float uStep = 1.0f / (columns);
			float vStep = 1.0f / (rows);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			const float x = (j * spacing) - halfWidth;
			const float y = 0.0f;
			const float z = (r * spacing) - halfHeight;
			const Vector3 p = { x, 0.0f, z };
			const Vector3 n = Math::Vector3::YAxis;
			const Vector3 t = Math::Vector3::XAxis;

			mesh.vertices.push_back
			({
				p, n, t,
				u, v
				});
		}
	}

	PlaneIndices(mesh, columns + 1, rows + 1);

	return mesh;
}

Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
	Mesh mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			const float x = radius * sin(rotation) * sin(phi);
			const float y = radius * cos(phi);
			const float z = radius * cos(rotation) * sin(phi);
			const Vector3 p = { x, y, z };
			const Vector3 n = Normalize(p);
			const Vector3 t = Normalize({ -z, 0.0f, x });

			mesh.vertices.push_back
			({
				p, n, t,
				u, v
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

Mesh MeshBuilder::CreateSkySphere(int slices, int rings, float radius)
{
	Mesh mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			const float x = radius * -sin(rotation) * sin(phi);
			const float y = radius * cos(phi);
			const float z = radius * cos(rotation) * sin(phi);
			const Vector3 p = { x, y, z };
			const Vector3 n = Normalize(p);
			const Vector3 t = Normalize({ -z, 0.0f, x });

			mesh.vertices.push_back
			({
				p, n, t,
				u, v
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

#pragma endregion

#pragma	region Indices

void MeshBuilder::CubeIndices(MeshPC& mesh)
{
	mesh.indices =
	{
		// Front & Back
		0, 1, 2,
		3, 0, 2,
		4, 6, 5,
		4, 7, 6,

		// Left & Right
		3, 2, 6,
		7, 3, 6,
		4, 5, 1,
		4, 1, 0,

		// Top & Bottom
		0, 3, 7,
		0, 7, 4,
		1, 5, 6,
		1, 6, 2
	};
}

void MeshBuilder::PlaneIndices(MeshPC& mesh, int columns, int rows)
{
	for (int i = 0; i < rows - 1; ++i)
	{
		for (int j = 0; j < columns - 1; ++j)
		{
			const int bottomLeftIndex = (i * columns) + j;

			// Triangle 1
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);

			// Triangle 2
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);
			mesh.indices.push_back(bottomLeftIndex + 1);
		}
	}
}

void MeshBuilder::PlaneIndices(MeshPX& mesh, int columns, int rows)
{
	for (int i = 0; i < rows - 1; ++i)
	{
		for (int j = 0; j < columns - 1; ++j)
		{
			const int bottomLeftIndex = (i * columns) + j;

			// Triangle 1
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);

			// Triangle 2
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);
			mesh.indices.push_back(bottomLeftIndex + 1);
		}
	}
}

void MeshBuilder::PlaneIndices(Mesh& mesh, int columns, int rows)
{
	for (int i = 0; i < rows - 1; ++i)
	{
		for (int j = 0; j < columns - 1; ++j)
		{
			const int bottomLeftIndex = (i * columns) + j;

			// Triangle 1
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);

			// Triangle 2
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);
			mesh.indices.push_back(bottomLeftIndex + 1);
		}
	}
}

void MeshBuilder::CreateCapIndices(MeshPC& mesh, int columns, int rows)
{
	const int bottomVertex = columns * rows + rows;
	const int topVertex = columns * rows + rows + 1;

	for (int i = 0; i < rows - 1; ++i)
	{
		if (i == 0)
		{

			for (int j = 0; j < columns; ++j)
			{
				const int bottomLeftIndex = (i * columns) + j;

				mesh.indices.push_back(bottomLeftIndex);
				mesh.indices.push_back(bottomLeftIndex + 1);
				mesh.indices.push_back(bottomVertex);
			}
		}
		if (i == rows - 2)
		{
			for (int j = 0; j < columns; ++j)
			{
				const int bottomLeftIndex = (i * columns) + j;

				mesh.indices.push_back(bottomLeftIndex + columns + rows - 1);
				mesh.indices.push_back(topVertex);
				mesh.indices.push_back(bottomLeftIndex + columns + rows);
			}
		}
	}
}

#pragma endregion