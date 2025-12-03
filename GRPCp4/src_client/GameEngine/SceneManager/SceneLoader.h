#pragma once

#include <vector>
#include <grpcpp/grpcpp.h>
#include "../../../proto/generated/scene.pb.h"
#include "../../../proto/generated/scene.grpc.pb.h"

#include "../GraphicsEngine/Prerequisites.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GameObject/GameObjectManager.h"
#include "SceneManager.h"



class SceneLoader {
private:
	std::unique_ptr<SceneGRPC::Stub> stub;


public:
	SceneLoader(std::shared_ptr<grpc::Channel> channel);
	void PreloadScene(const int& SceneID);
	std::string StreamObjFile(const int& ModelID);
};