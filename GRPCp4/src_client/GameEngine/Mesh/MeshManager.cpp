#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* filePath)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(filePath));
}

MeshPtr MeshManager::createOrGetMesh(int ID, const void* objData, size_t dataSize)
{
	//if mesh already exists
	auto it = meshCache.find(ID);
	if (it != meshCache.end()) {
		return it->second;
	}

	//if not, create 
	MeshPtr mesh = std::make_shared<Mesh>(objData, dataSize);
	meshCache[ID] = mesh;
	return mesh;
}



Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	//std::cout << "dumadaan ba" << std::endl;
	Mesh* mesh = nullptr;
	try
	{
		//std::cout << "tried mesh" << std::endl;
		mesh = new Mesh(filePath);
	}
	catch (...) {}

	return mesh;
}
