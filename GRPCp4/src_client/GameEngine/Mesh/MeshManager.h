#pragma once
#include "../GraphicsEngine/ResourceManager/ResourceManager.h"
#include "../GraphicsEngine/Prerequisites.h"
//#include "Mesh.h"

class MeshManager : public ResourceManager
{

public:
	MeshManager();
	~MeshManager();

	MeshPtr createMeshFromFile(const wchar_t* filePath);
	MeshPtr createMesh(int ID, const void* objData, size_t dataSize);
	MeshPtr getMesh(int ID);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);

private:
	std::unordered_map<int, MeshPtr> meshCache;

};
