#include "SceneLoader.h"
#include "../../../ThreadTool/IETThread.h"

SceneLoader::SceneLoader(std::shared_ptr<grpc::Channel> ch) : stub(SceneGRPC::NewStub(ch))
{
}


//client-side
void SceneLoader::PreloadScene(const int& SceneID) {
	MeshManager* meshManager = GraphicsEngine::get()->getMeshManager();

	SceneRequest request;
	request.set_sceneid(SceneID);

	std::cout << "Scene ID: " << SceneID << std::endl;

	SceneResponse response;
	grpc::ClientContext context;

	grpc::Status status = stub->PreloadScene(&context, request, &response);

	//std::cout << "models size: " << response.models_size() << std::endl;

	if (status.ok()) {
		SceneData sceneData;
		sceneData.sceneID = SceneID;
		sceneData.sceneName = response.scenename();

		SceneLoadProgress* progress = new SceneLoadProgress();
		SceneManager::get()->RegisterSceneProgress(SceneID, progress);
		//int64_t totalSceneBytes = 0;
		for (const auto& model : response.models()) {
			progress->totalBytes += model.size();
		}
		//int64_t bytesReceived = 0;

		for (const auto& model : response.models()) {
			int ID = model.modelid();
			std::string objData = this->StreamObjFile(ID, progress->bytesReceived, progress->totalBytes);
			MeshPtr mesh = meshManager->createMesh(ID, objData.data(), objData.size());
			
			Vector3D position = Vector3D(model.transform().position().x(), model.transform().position().y(), model.transform().position().z());
			Vector3D rotation = Vector3D(model.transform().rotation().x(), model.transform().rotation().y(), model.transform().rotation().z());
			Vector3D scale = Vector3D(model.transform().scale().x(), model.transform().scale().y(), model.transform().scale().z());
			MyTransform transform = MyTransform(position, rotation, scale);

			sceneData.models.push_back({ model.modelid(), model.modelname(), transform});
			
			//std::cout << "stored model: " << model.modelid() << " in mesh cache " << std::endl;
		}

	//	std::cout << "num models: " << sceneData.models.size()  << std::endl;
		SceneManager::get()->RegisterPreloadedScene(sceneData);

		std::cout << "Success: " << response.msg() << std::endl;
	}
	else {
		std::cout << "Fail" << std::endl;
	}
}

std::string SceneLoader::StreamObjFile(const int& ModelID, std::atomic<int64_t>& bytesReceived, int64_t totalSceneBytes)
{
	ObjFileRequest request;
	request.set_modelid(ModelID);
	grpc::ClientContext context;

	std::unique_ptr<grpc::ClientReader<ObjChunk>> reader(stub->StreamObjFile(&context, request));

	ObjChunk chunk;
	std::string objData;

	while (reader->Read(&chunk)) {
		
		objData.append(chunk.data());
		bytesReceived += chunk.data().size();
		/*float progress = (float)bytesReceived / totalSceneBytes;
		std::cout << "\rScene loading progress: " << int(progress * 100) << "%" << std::flush;*/
		IETThread::sleep(100);
	}

	grpc::Status status = reader->Finish();
	if (!status.ok()) {
		std::cout << "Stream failed : " << status.error_message() << std::endl;
		return "";
	}

	//return std::string();
	return objData;
}
