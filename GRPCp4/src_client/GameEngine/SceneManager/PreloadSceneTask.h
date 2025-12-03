#pragma once
#include "SceneLoader.h"
#include "../../../ThreadTool/IWorkerAction.h"

class PreloadSceneTask : public IWorkerAction
{
public:
	PreloadSceneTask(int SceneID, std::shared_ptr<grpc::Channel> channel);

	virtual void OnStartTask() override;

private:
	int sceneID;
	SceneLoader loader;
};