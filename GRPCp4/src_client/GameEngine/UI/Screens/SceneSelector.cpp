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
	if (ImGui::Button("Load")) {
		//SceneManager::get()->LoadScene(1);
		//std::cout << "how many: " << SceneManager::get()->preloadedScenes[1].sceneID << std::endl;
		SceneManager::get()->InstantiateScene("WasteLand");

		//std::cout << "HASUDHASUHD" << std::endl;
	}
	ImGui::End();

}
