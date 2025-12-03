#include "SceneSelector.h"
//#include "../../SceneManager/SceneLoader.h"
#include "../../SceneManager/SceneManager.h"

SceneSelector::SceneSelector() : UIScreen("Scene Selector") {
	this->activeSelf = true;
	//this->loader = SceneManager::get()->getLoader();
}
SceneSelector::~SceneSelector() {

}

void SceneSelector::draw()
{
	UINames uiNames;
	if (!activeSelf) return;

	ImGui::Begin(this->getName().c_str(), &this->activeSelf);

	ImGui::Text("Scene A");

	SceneLoadProgress* p1 = SceneManager::get()->getProgressByID(1);
	if (p1) {
		float prog = (float)p1->bytesReceived / (float)p1->totalBytes;
		std::cout << "\rScene 1 loading progress: " << int(prog * 100) << "%" << std::flush;
		//std::cout << "PROGRESS: " << (float)progress->bytesReceived << std::endl;
	}

	SceneLoadProgress* p2 = SceneManager::get()->getProgressByID(2);
	if (p2) {
		float prog = (float)p2->bytesReceived / (float)p2->totalBytes;
		std::cout << "\n\n\rScene 2 loading progress: " << int(prog * 100) << "%" << std::flush;
		//std::cout << "PROGRESS: " << (float)progress->bytesReceived << std::endl;
	}

	

	if (ImGui::Button("Load")) {
		//SceneManager::get()->LoadScene(1);
		//std::cout << "how many: " << SceneManager::get()->preloadedScenes[1].sceneID << std::endl;
		SceneManager::get()->InstantiateScene("WasteLand");


		//std::cout << "HASUDHASUHD" << std::endl;
	}

	ImGui::NewLine();
	ImGui::Text("Scene B");
	if (ImGui::Button("Load B")) {
		//SceneManager::get()->LoadScene(1);
		//std::cout << "how many: " << SceneManager::get()->preloadedScenes[1].sceneID << std::endl;
		SceneManager::get()->InstantiateScene("Nowhere");


		//std::cout << "HASUDHASUHD" << std::endl;
	}
	ImGui::End();

}
