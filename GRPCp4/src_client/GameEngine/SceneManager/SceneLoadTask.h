#pragma once
#include "../../../ThreadTool/IWorkerAction.h"

//#include "SceneManager.h"


class SceneLoader;
class SceneLoadTask : public IWorkerAction {
public:
	SceneLoadTask(int sceneID, SceneLoader* loader);

	void OnStartTask() override;

private:
	int sceneID;
	SceneLoader* loader;
};