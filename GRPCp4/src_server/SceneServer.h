#pragma once
#include <grpcpp/grpcpp.h>
#include "../proto/generated/scene.grpc.pb.h"
#include "IETThread.h"


class SceneServer final : public SceneGRPC::Service {

public:
	grpc::Status GetScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response);
	grpc::Status StreamObjFile(grpc::ServerContext* context, const ObjFileRequest* request, grpc::ServerWriter<ObjChunk>* writer);

	void RunServer();
	//void run();

private:
	std::string GetModelPath(int ID);
	void AddModel(SceneResponse* response, int ModelID);
	void SetSceneProperties(SceneResponse* response, int SceneID);

};