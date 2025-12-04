#pragma once
//#include "SceneLoader.h"
//#include <grpcpp/grpcpp.h>
#include "../../../ThreadTool/ThreadPool.h"
#include "SceneLoadTask.h"
#include "../Math/MyTransform.h"
#include "../GameObject/GameObject.h"

struct SceneModelInfo {
	int modelID;
	std::string modelName;
	MyTransform transform;
};

struct SceneData {
	int sceneID;
	std::string sceneName;
	std::vector<SceneModelInfo> models;
};

struct SceneLoadProgress {
	std::atomic<int64_t> bytesReceived{ 0 };
	int64_t totalBytes{ 0 };
};

class SceneLoader;
class SceneManager {
public:
	static SceneManager* get();
	static void initialize();
	static void destroy();
	//SceneLoader* getLoader();
	void LoadScene(int SceneID);
	void ScheduleLoadScene(int SceneID);
	void RegisterPreloadedScene(const SceneData& sceneData);
	void ViewScene(int SceneID, std::string sceneName);
	void ViewAllScenes();
	SceneLoadProgress* getProgressByID(int SceneID);
	void RegisterSceneProgress(int ID, SceneLoadProgress* progress);
	std::vector<GameObject*> GetSceneObjectsByID(int sceneID);
	void DeleteObjectsInScene(int SceneID);
	void InstantiateSceneObject();

private:
	SceneManager();
	~SceneManager();
	SceneManager(SceneManager const&) {};
	SceneManager& operator=(SceneManager const&) {};
	static SceneManager* sharedInstance;


private:
	SceneLoader* loader;
	std::unique_ptr<ThreadPool> threadPool;
	std::unordered_map<std::string, SceneData> preloadedScenes;
	std::unordered_map<int, SceneLoadProgress*> sceneProgress;
	std::unordered_map<int, std::vector<GameObject*>> sceneObjects;
	
};