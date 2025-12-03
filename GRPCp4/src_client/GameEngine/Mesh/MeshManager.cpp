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

//MeshPtr MeshManager::createMeshFromData(const void* objData, size_t dataSize)
//{
//	return std::static_pointer_cast<Mesh>(createResourceFromFile(objData, dataSize));
//}

Mesh* MeshManager::createOrGetMesh(int ID, const void* objData, size_t dataSize)
{
	//if mesh already exists
	auto it = meshCache.find(ID);
	if (it != meshCache.end()) {
		return it->second;
	}

	//if not, create 
	Mesh* newMesh = new Mesh(objData, dataSize); // custom constructor using memory buffer
	meshCache[ID] = newMesh;
	return newMesh;
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

//Resource* MeshManager::createResourceFromFileConcrete(const void* objData, size_t dataSize)
//{
//	Mesh* mesh = nullptr;
//	try
//	{
//		//std::cout << "tried mesh" << std::endl;
//		mesh = new Mesh(objData, dataSize);
//	}
//	catch (...) {}
//
//	return mesh;
//}

//Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* filePath, void* shaderByteCode, size_t sizeShader)
//{
//	Mesh* mesh = nullptr;
//	try
//	{
//		mesh = new Mesh(filePath, shaderByteCode, sizeShader);
//	}
//	catch (...) {}
//
//	return mesh;
//}
