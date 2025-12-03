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
	this->preloadedScenes[sceneData.sceneName] = new SceneData(sceneData);
	std::cout << "registered scene " << sceneData.sceneName << " with " << sceneData.models.size() << " models. \n";
}

void SceneManager::InstantiateScene(std::string sceneName)
{
	MeshManager* meshManager = GraphicsEngine::get()->getMeshManager();
	GameObjectManager* objManager = GameObjectManager::get();

	for (const auto& modelInfo : preloadedScenes[sceneName]->models) {
		MeshPtr mesh = meshManager->getMesh(modelInfo.modelID);
		GameObject* obj = new GameObject(objManager->adjustName(modelInfo.modelName));
		obj->addComponent<MeshRenderer>(mesh);
		obj->setPosition(modelInfo.transform.localPosition);
		obj->setRotation(modelInfo.transform.localRotation);
		obj->setScale(modelInfo.transform.localScale);
		GameObjectManager::get()->addObject(obj);
	}
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
