#include "SceneLoader.h"
//#include "../Mesh/MeshManager.h"


SceneLoader::SceneLoader(std::shared_ptr<grpc::Channel> channel) : stub(SceneGRPC::NewStub(channel))
{
}


//client-side
void SceneLoader::GetScene(const int& SceneID) {
	//MeshManager* meshManager = GraphicsEngine::get()->getMeshManager();
	MeshManager* meshManager = GraphicsEngine::get()->getMeshManager();

	SceneRequest request;
	request.set_sceneid(SceneID);

	SceneResponse response;
	grpc::ClientContext context;

	grpc::Status status = stub->GetScene(&context, request, &response);

	//std::cout << "models size: " << response.models_size() << std::endl;

	if (status.ok()) {
		for (const auto& model : response.models()) {
			int ID = model.modelid();
			std::string objData = this->StreamObjFile(ID);
			std::cout << "data size: " << objData.size() << std::endl;

			MeshPtr mesh = meshManager->createOrGetMesh(ID, objData.data(), objData.size());
			GameObjectManager* manager = GameObjectManager::get();
			GameObject* obj = new GameObject(manager->adjustName("Bunny"));

			obj->addComponent<MeshRenderer>(mesh);
			manager->addObject(obj);
			manager->setSelectedObject(obj);
			//Mesh* mesh = 
		}

		std::cout << "Success: " << response.msg() << std::endl;
	}
	else {
		std::cout << "Fail" << std::endl;
	}
}

std::string SceneLoader::StreamObjFile(const int& ModelID)
{
	ObjFileRequest request;
	request.set_modelid(ModelID);

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
