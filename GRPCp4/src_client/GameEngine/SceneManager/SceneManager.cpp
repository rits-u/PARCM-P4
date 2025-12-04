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

	sharedInstance->threadPool = std::make_unique<ThreadPool>(5);
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
	std::cout << "\n [REGISTERED Scene] " << sceneData.sceneName << " with " << sceneData.models.size() << " models. \n";
}

void SceneManager::ViewScene(int SceneID, std::string sceneName)
{
	MeshManager* meshManager = GraphicsEngine::get()->getMeshManager();
	GameObjectManager* objManager = GameObjectManager::get();

	auto it = preloadedScenes.find(sceneName);
	if (it == preloadedScenes.end()) {
		std::cout << "\n [SCENE] " << sceneName << " is not loaded yet" << std::endl;
		return;
	}
	else {
		std::cout << "\n [SCENE] " << sceneName << " scene is found " << std::endl;
	}

	std::cout << "\n Viewing " << sceneName << "..." << std::endl;
	
	//std::vector<GameObject*> objs;
	for (const auto& modelInfo : preloadedScenes[sceneName].models) {
		MeshPtr mesh = meshManager->getMesh(modelInfo.modelID);
		std::cout << "model id in instantiate: " << modelInfo.modelID << std::endl;

		GameObject* obj = new GameObject(modelInfo.modelName);
		obj->addComponent<MeshRenderer>(mesh);
		obj->setPosition(modelInfo.transform.localPosition);
		obj->setRotation(modelInfo.transform.localRotation);
		obj->setScale(modelInfo.transform.localScale);
		GameObjectManager::get()->addObject(obj);
		this->sceneObjects[SceneID].push_back(obj);
	}

	std::cout << "Scene Objects Count: " << this->sceneObjects[SceneID].size() << std::endl;
}

//void SceneManager::ViewAllScenes()
//{
//	for (int i = 1; i <= 5; i++) {
//		for()
//	}
//}

SceneLoadProgress* SceneManager::getProgressByID(int SceneID)
{
	return this->sceneProgress[SceneID];
}

void SceneManager::RegisterSceneProgress(int ID, SceneLoadProgress* progress)
{
	this->sceneProgress[ID] = progress;
}

std::vector<GameObject*> SceneManager::GetSceneObjectsByID(int sceneID)
{
	return this->sceneObjects[sceneID];
}

void SceneManager::DeleteObjectsInScene(int SceneID)
{
	for (GameObject* obj : this->sceneObjects[SceneID]) {
		GameObjectManager::get()->deleteObject(obj);
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
