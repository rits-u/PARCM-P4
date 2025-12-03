#include "SceneManager.h"
#include "SceneLoader.h"
#include <grpcpp/grpcpp.h>    
#include "PreloadSceneTask.h"

SceneManager* SceneManager::sharedInstance = nullptr;

SceneManager* SceneManager::get() {
	return sharedInstance;
}

void SceneManager::initialize() {
	sharedInstance = new SceneManager();

	/*sharedInstance->loader = new SceneLoader(
		grpc::CreateChannel("localhost:50051",
			grpc::InsecureChannelCredentials())
	);*/

	sharedInstance->loader = std::make_unique<SceneLoader>(
		grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
	);

	sharedInstance->threadPool = std::make_unique<ThreadPool>(2);
	sharedInstance->threadPool->StartScheduling();
}

void SceneManager::destroy() {
	if (sharedInstance) {
		sharedInstance->threadPool->StopScheduling();
		delete sharedInstance;
		sharedInstance = nullptr;
	}

	/*if (!SceneManager::sharedInstance)
		return;

	delete SceneManager::sharedInstance;*/
}

SceneLoader* SceneManager::getLoader()
{
	return loader.get();
}

void SceneManager::LoadScene(int SceneID) {
	//loader->GetScene(SceneID);
	auto task = new PreloadSceneTask(SceneID, loader->getChannel());
	threadPool->ScheduleTasks(task);
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
