#include "PreloadSceneTask.h"

PreloadSceneTask::PreloadSceneTask(int SceneID, std::shared_ptr<grpc::Channel> channel)
{
	this->sceneID = sceneID;
    this->loader = channel;
}

void PreloadSceneTask::OnStartTask()
{
    //std::cout << "[Thread] Preloading scene: " << sceneID << std::endl;

    //auto response = SceneLoader::GetSceneBlocking(sceneID);

    //// 2. Load OBJ models from server
    //for (const auto& model : response.models()) {
    //    int id = model.modelid();
    //    std::string name = model.modelname();

    //    std::cout << "   Loading model: " << name << std::endl;

    //    // Stream OBJ
    //    std::string data = SceneLoader::StreamObjFileBlocking(id);

    //    // Store mesh in engine cache (no GameObjects yet)
    //    MeshManager::Get()->LoadMeshFromMemory(id, data);
    //}

    //std::cout << "[Thread] Scene " << sceneID << " preload complete!\n";
    this->loader.GetScene(this->sceneID);
}
