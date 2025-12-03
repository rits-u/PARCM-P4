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
		SceneManager::get()->LoadScene(10);		
	}
	ImGui::End();

}
