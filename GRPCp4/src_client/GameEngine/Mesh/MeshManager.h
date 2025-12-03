#pragma once
#include "../GraphicsEngine/ResourceManager/ResourceManager.h"
#include "Mesh.h"

class MeshManager : public ResourceManager
{

public:


	MeshManager();
	~MeshManager();

	MeshPtr createMeshFromFile(const wchar_t* filePath);
	//MeshPtr createMeshFromData(const void* objData, size_t dataSize);
	Mesh* createOrGetMesh(int ID, const void* objData, size_t dataSize);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);
//	Resource* createResourceFromFileConcrete(const void* objData, size_t dataSize);

private: 
	std::unordered_map<int, Mesh*> meshCache;

};
