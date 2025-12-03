#include "ResourceManager.h"
#include <filesystem>
#include <iostream>

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* filePath)
{
    std::wstring fullPath = std::filesystem::absolute(filePath);
    auto it = mapResources.find(fullPath);

    if (it != mapResources.end())
        return it->second;
  //  std::cout << "hello" << std::endl;
    Resource* rawResource = this->createResourceFromFileConcrete(fullPath.c_str());

    if (rawResource) {
        ResourcePtr resource(rawResource);
        mapResources[fullPath] = resource;
        return resource;
    }



    return nullptr;
}


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
