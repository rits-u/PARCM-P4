#include "SceneLoader.h"
#include "../Mesh/MeshManager.h"

#ifdef byte
#undef byte
#endif

SceneLoader::SceneLoader(std::shared_ptr<grpc::Channel> channel) : stub(SceneGRPC::NewStub(channel))
{
}


//client-side
void SceneLoader::GetScene(const int& SceneID) {
	//MeshManager* meshManager = 

	SceneRequest request;
	request.set_sceneid(SceneID);

	SceneResponse response;
	grpc::ClientContext context;

	grpc::Status status = stub->GetScene(&context, request, &response);

	if (status.ok()) {
		//for (const auto& model : response.models()) {
		//	int ID = model.modelid();
		//	std::string objData = this->StreamObjFile(ID);

		//	//Mesh* mesh = 
		//}


		//response.models().size();
		//std::string objData = this->StreamObjFile()

		std::cout << "Success: " << response.msg() << std::endl;
		//std::cout << "Success: " << response.status() << std::endl;
		//std::cout << "Message: " << response.msg() << std::endl;
	}
	else {
		std::cout << "Fail" << std::endl;
	}
}

std::string SceneLoader::StreamObjFile(const int& ModelID)
{
	ObjFileRequest request;
	request.modelid();

	grpc::ClientContext context;

	std::unique_ptr<grpc::ClientReader<ObjChunk>> reader(
		stub->StreamObjFile(&context, request)
	);

	ObjChunk chunk;
	std::string objData;

	while (reader->Read(&chunk)) {
		objData.append(chunk.data());
	}

	grpc::Status status = reader->Finish();
	if (!status.ok()) {
		std::cerr << "Stream failed: " << status.error_message() << std::endl;
		return "";
	}

	//return std::string();
	return objData;
}
