#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <locale>
#include <codecvt>

#include "../GraphicsEngine/GraphicsEngine.h"
//#include "../Math/VertexMesh.h"
//#include "../InputSystem/InputSystem.h"

Mesh::Mesh(const wchar_t* fullPath) : Resource(fullPath)
{
	//std::cout << "mesh start" << std::endl;
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warning;
	std::string error;

	std::string inputFile = WStringToString(fullPath);

	bool res = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, inputFile.c_str());
	//std::cout << "loaded obj" << std::endl;

	if (!error.empty() || !res || shapes.size() > 1)
		throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> vertices;
	std::vector<unsigned int> indices;


	
	for (size_t s = 0; s < shapes.size(); s++)
	{
	
		size_t index_offset = 0;

		vertices.reserve(shapes[s].mesh.indices.size());
		indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				// position
				float vx = attributes.vertices[index.vertex_index * 3 + 0];
				float vy = attributes.vertices[index.vertex_index * 3 + 1];
				float vz = attributes.vertices[index.vertex_index * 3 + 2];

				// texcoord
				float tx = 0.0f;
				float ty = 0.0f;

				if (index.texcoord_index >= 0 &&
					index.texcoord_index * 2 + 1 < attributes.texcoords.size())
				{
					tx = attributes.texcoords[index.texcoord_index * 2 + 0];
					ty = attributes.texcoords[index.texcoord_index * 2 + 1];
				}

				vertices.emplace_back(Vector3D(vx, vy, vz), Vector2D(tx, ty));

				indices.push_back((unsigned int)indices.size());
			}

			index_offset += num_face_verts;
		}
	}

	// Store CPU-side data
	m_vertices = std::move(vertices);
	m_indices = std::move(indices);

	//std::cout << "mesh ok" << std::endl;


}


Mesh::~Mesh()
{
}

std::vector<VertexMesh>& Mesh::getVertices()
{
	return this->m_vertices;
}

std::vector<unsigned int>& Mesh::getIndices()
{
	return this->m_indices;
}

std::string Mesh::WStringToString(const std::wstring& wstr)
{
	if (wstr.empty()) return {};

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string strTo(size_needed - 1, 0); // exclude null terminator
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &strTo[0], size_needed, nullptr, nullptr);
	return strTo;
}
