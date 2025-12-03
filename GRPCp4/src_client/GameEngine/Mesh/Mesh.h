#pragma once

#include "../GraphicsEngine/ResourceManager/Resource.h"
#include <d3d11.h>
#include <Windows.h>
#include <string>
#include "../GraphicsEngine/RenderSystem/VertexBuffer.h"
#include "../GraphicsEngine/RenderSystem/IndexBuffer.h"
//#include "InputListener.h"
#include "../Math/VertexMesh.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	Mesh(const void* objData, size_t objSize);
	~Mesh();


	std::vector<VertexMesh>& getVertices();
	std::vector<unsigned int>& getIndices();

private:
	std::vector<VertexMesh> m_vertices;
	std::vector<unsigned int> m_indices;

private:
	void loadObjFromStream(std::string objStream);
	std::string WStringToString(const std::wstring& wstr);

private:
	friend class DeviceContext;
};

