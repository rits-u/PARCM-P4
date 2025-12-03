#include "SceneServer.h"
#include <fstream>

grpc::Status SceneServer::GetScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response) {
	int ID = request->sceneid();
	SetSceneProperties(response, ID);

	//Model* model = response->add_models();
	//model->set_modelid(2);
	//model->set_modelname("Bunny");


	response->set_msg("Server got request: Scene " + std::to_string(ID));
	return grpc::Status::OK;
}

grpc::Status SceneServer::StreamObjFile(grpc::ServerContext* context, const ObjFileRequest* request, grpc::ServerWriter<ObjChunk>* writer) {
	std::string path = GetModelPath(request->modelid());
	std::ifstream file(path, std::ios::binary);
//	std::cout << "stream attempt from server" << std::endl;


	if (!file)
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found");
	else {
		//std::cout << "file found" << std::endl;
	}

	const size_t chunkSize = 64 * 1024; //64 kb per chunk
	std::vector<char> buffer(chunkSize);

	while (file) {
		file.read(buffer.data(), buffer.size());
		std::streamsize bytesRead = file.gcount();
		if (bytesRead == 0) break;

		ObjChunk chunk;
		chunk.set_data(buffer.data(), bytesRead);
		writer->Write(chunk);
	}

	return grpc::Status::OK;
}

void SceneServer::RunServer() {
	//create a server at this IP
	std::string serverAdd("0.0.0.0:50051");
	SceneServer service;

	//server builder
	grpc::ServerBuilder builder;
	builder.AddListeningPort(serverAdd, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	//start the server itself
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << serverAdd << std::endl;

	//wait for clients
	server->Wait();
}

std::string SceneServer::GetModelPath(int ID)
{
	std::string path;
	if (ID == 2) {
		path = "../../../src_server/Assets/Meshes/bunny.obj";
	}

	return path;
}

void SceneServer::SetSceneProperties(SceneResponse* response, int SceneID)
{
	switch (SceneID) {
	case 1:
		Model* model = response->add_models();
		model->set_modelid(2);
		model->set_modelname("Bunny");
		break;
	}
	//std::cout << "scene id: " << SceneID << std::endl;

}
