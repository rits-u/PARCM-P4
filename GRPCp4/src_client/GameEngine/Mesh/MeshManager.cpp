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

MeshPtr MeshManager::createMesh(int ID, const void* objData, size_t dataSize)
{
	//if mesh already exists
	//auto it = meshCache.find(ID);
	//if (it != meshCache.end()) {
	//	return it->second;
	//}
	if (meshCache.contains(ID)) {
		return meshCache[ID];
	}

	

	//if not, create 
	MeshPtr mesh = std::make_shared<Mesh>(objData, dataSize);
	meshCache[ID] = mesh;
	return mesh;
}

MeshPtr MeshManager::getMesh(int ID) {
	//std::cout << "get Mesh: " << ID << std::endl;
	return meshCache[ID];
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
