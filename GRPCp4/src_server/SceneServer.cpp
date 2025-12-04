#include "SceneServer.h"
#include <fstream>
#include <random>

grpc::Status SceneServer::PreloadScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response) {
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
	//response->set
	switch (SceneID) {
	case 1:
		response->set_sceneid(1);
		response->set_scenename("Waste Land");
		AddModelToData(response, 2, "Bunny");

		/*Model* model = response->add_models();
		model->set_modelid(2);
		model->set_modelname("Bunny");*/

		break;
	case 2:
		response->set_sceneid(2);
		response->set_scenename("Nowhere");
		AddModelToData(response, 2, "mafuyu");
		AddModelToData(response, 2, "wasdasd");
		break;

	}
	//std::cout << "scene id: " << SceneID << std::endl;

}

void SceneServer::AddModelToData(SceneResponse* response, int ModelID, std::string name)
{
	
	Model* model = response->add_models();
	model->set_modelid(ModelID);
	model->set_modelname(name);
	
	Transform* t = model->mutable_transform();
	int min = 0; int max = 5;
	Vector3* pos = t->mutable_position(); 
	pos->set_x(RNG(min, max)); pos->set_y(RNG(min, max)); pos->set_z(RNG(min, max));

	min = 0; max = 360;
	Vector3* rot = t->mutable_rotation();
	rot->set_x(RNG(min, max)); rot->set_y(RNG(min, max)); rot->set_z(RNG(min, max));

	int n = RNG(1, 5);
	Vector3* sca = t->mutable_scale();
	sca->set_x(n); sca->set_y(n); sca->set_z(n);

	std::string path = GetModelPath(ModelID);
	std::ifstream file(path, std::ios::binary | std::ios::ate); //start at end of the file
	if (file) {
		model->set_size(file.tellg());
	}

	//model->set_trasf

}

float SceneServer::RNG(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return (float)distrib(gen);
}
