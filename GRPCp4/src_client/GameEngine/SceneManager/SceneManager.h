#pragma once
//#include "SceneLoader.h"
//#include <grpcpp/grpcpp.h>
#include "SceneLoadTask.h"

class SceneLoader;
class SceneManager {
public:
	static SceneManager* get();
	static void initialize();
	static void destroy();
	//SceneLoader* getLoader();
	void LoadScene(int SceneID);


private:
	SceneManager();
	~SceneManager();
	SceneManager(SceneManager const&) {};
	SceneManager& operator=(SceneManager const&) {};
	static SceneManager* sharedInstance;

private:
	SceneLoader* loader;
	//std::unique_ptr<SceneLoader> loader;
};