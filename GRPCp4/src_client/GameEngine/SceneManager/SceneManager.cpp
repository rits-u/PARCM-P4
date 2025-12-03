#include "SceneManager.h"
#include "SceneLoader.h"
#include <grpcpp/grpcpp.h>    

SceneManager* SceneManager::sharedInstance = nullptr;

SceneManager* SceneManager::get() {
	return sharedInstance;
}

void SceneManager::initialize() {
	sharedInstance = new SceneManager();

	sharedInstance->loader = new SceneLoader(
		grpc::CreateChannel("localhost:50051",
			grpc::InsecureChannelCredentials())
	);
}

void SceneManager::destroy() {
	if (!SceneManager::sharedInstance)
		return;

	delete SceneManager::sharedInstance;
}

SceneLoader* SceneManager::getLoader()
{
	return this->loader;
}

void SceneManager::LoadScene(int SceneID) {
	loader->GetScene(SceneID);
}

SceneManager::SceneManager() {
	//SceneLoader* loader = new SceneLoader();
}

SceneManager::~SceneManager()
{
	SceneManager::sharedInstance = nullptr;
	SceneManager::sharedInstance->loader = nullptr;
//	SceneLoader::sharedInstance = nullptr;
}
