#pragma once
#include <grpcpp/grpcpp.h>
#include "../proto/generated/scene.grpc.pb.h"



class SceneServer final : public SceneGRPC::Service {

public:
	grpc::Status PreloadScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response);
	grpc::Status StreamObjFile(grpc::ServerContext* context, const ObjFileRequest* request, grpc::ServerWriter<ObjChunk>* writer);

	void RunServer();

private:
	std::string GetModelPath(int ID);
	void SetSceneProperties(SceneResponse* response, int SceneID);
	void AddModelToData(SceneResponse* response, int ModelID, std::string name);
	float RNG(int min, int max);

};