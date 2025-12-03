#include "SceneLoadTask.h"
#include "SceneLoader.h"


SceneLoadTask::SceneLoadTask(int sceneID, SceneLoader* loader) 
{
	this->sceneID = sceneID;
	this->loader = loader;
	
}

void SceneLoadTask::OnStartTask() {
	if (loader) {
		loader->PreloadScene(this->sceneID);
	}
}