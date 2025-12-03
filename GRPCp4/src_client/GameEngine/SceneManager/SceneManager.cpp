#include "SceneManager.h"

#include "SceneLoader.h"
#include <grpcpp/grpcpp.h> 
//  

SceneManager* SceneManager::sharedInstance = nullptr;

SceneManager* SceneManager::get() {
	return sharedInstance;
}

void SceneManager::initialize() {
	sharedInstance = new SceneManager();
	auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	sharedInstance->loader = new SceneLoader(channel);

	sharedInstance->threadPool = std::make_unique<ThreadPool>(2);
	sharedInstance->threadPool->StartScheduling();

	/*sharedInstance->loader = new SceneLoader(
		grpc::CreateChannel("localhost:50051",
			grpc::InsecureChannelCredentials())
	);*/
}

void SceneManager::destroy() {
	if (!SceneManager::sharedInstance)
		return;

	sharedInstance->threadPool->StopScheduling();
	delete SceneManager::sharedInstance;
	//sharedInstancereset();
}
//
//SceneLoader* SceneManager::getLoader()
//{
//	//return this->loader;
//}

void SceneManager::LoadScene(int SceneID) {
	//loader->GetScene(SceneID);
}

void SceneManager::ScheduleLoadScene(int SceneID)
{
	if (!loader || !threadPool)
		return;

	std::cout << "start schedule" << std::endl;
	SceneLoadTask* task = new SceneLoadTask(SceneID, loader);
	threadPool->ScheduleTasks(task);
}

void SceneManager::RegisterPreloadedScene(const SceneData& sceneData)
{
	this->preloadedScenes[sceneData.sceneName] = SceneData(sceneData);
	std::cout << "registered scene " << sceneData.sceneName << " with " << sceneData.models.size() << " models. \n";
}

void SceneManager::InstantiateScene(std::string sceneName)
{
	MeshManager* meshManager = GraphicsEngine::get()->getMeshManager();
	GameObjectManager* objManager = GameObjectManager::get();

	auto it = preloadedScenes.find(sceneName);
	if (it == preloadedScenes.end()) {
		std::cout << "[SCENE] " << sceneName << " is not loaded yet" << std::endl;
		return;
	}
	else {
		std::cout << "\n [SCENE] " << sceneName << " scene is found " << std::endl;
	}

	for (const auto& modelInfo : preloadedScenes[sceneName].models) {
		MeshPtr mesh = meshManager->getMesh(modelInfo.modelID);
		GameObject* obj = new GameObject(objManager->adjustName(modelInfo.modelName));
		obj->addComponent<MeshRenderer>(mesh);
		obj->setPosition(modelInfo.transform.localPosition);
		obj->setRotation(modelInfo.transform.localRotation);
		obj->setScale(modelInfo.transform.localScale);
		GameObjectManager::get()->addObject(obj);
	}
}

SceneLoadProgress* SceneManager::getProgressByID(int SceneID)
{
	return this->sceneProgress[SceneID];
}

void SceneManager::RegisterSceneProgress(int ID, SceneLoadProgress* progress)
{
	this->sceneProgress[ID] = progress;
}

SceneManager::SceneManager() {
	//SceneLoader* loader = new SceneLoader();
}

SceneManager::~SceneManager()
{
	SceneManager::sharedInstance = nullptr;
	//SceneManager::sharedInstance->loader = nullptr;
	//	SceneLoader::sharedInstance = nullptr;
}
