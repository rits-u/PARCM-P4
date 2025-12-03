#pragma once
//#include "SceneLoader.h"
//#include <grpcpp/grpcpp.h>
#include "../../../ThreadTool/ThreadPool.h"

class SceneLoader;
class SceneManager {
public:
	static SceneManager* get();
	static void initialize();
	static void destroy();
	SceneLoader* getLoader();
	void LoadScene(int SceneID);


private:
	//SceneLoader* loader;
	SceneManager();
	~SceneManager();
	SceneManager(SceneManager const&) {};
	SceneManager& operator=(SceneManager const&) {};
	static SceneManager* sharedInstance;

	std::unique_ptr<SceneLoader> loader;
	std::unique_ptr<ThreadPool> threadPool;
};