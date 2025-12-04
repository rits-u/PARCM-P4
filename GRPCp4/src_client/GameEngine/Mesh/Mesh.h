#pragma once

#include <string>
#include "../GraphicsEngine/RenderSystem/VertexBuffer.h"
#include "../GraphicsEngine/RenderSystem/IndexBuffer.h"
#include "../GraphicsEngine/ResourceManager/Resource.h"
#include "../Math/VertexMesh.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	Mesh(const void* objData, size_t objSize);
	~Mesh();


	std::vector<VertexMesh>& getVertices();
	std::vector<unsigned int>& getIndices();

public:
	VertexBufferPtr vb;
	IndexBufferPtr ib;

private:
	std::vector<VertexMesh> m_vertices;
	std::vector<unsigned int> m_indices;

private:
	std::string WStringToString(const std::wstring& wstr);

private:
	friend class DeviceContext;
};

