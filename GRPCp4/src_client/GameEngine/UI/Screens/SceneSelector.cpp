#include "SceneSelector.h"
#include "../../SceneManager/SceneManager.h"

SceneSelector::SceneSelector() : UIScreen("Scene Selector", true) {
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
	ImGui::Separator();

	//sceneManager get scenes
	this->displayScenePanel(1, 'A', "Waste Land");
	this->displayScenePanel(2, 'B', "Nowhere");
	this->displayScenePanel(3, 'C', "Somewhere");
	this->displayScenePanel(4, 'D', "Elsewhere");
	this->displayScenePanel(5, 'E', "Empty World");

	if (ImGui::Button("View All Scenes")) {
		SceneManager::get()->ViewAllScenes();
	}
	ImGui::NewLine();
	if (ImGui::Button("Remove All Scenes")) {
		SceneManager::get()->RemoveAllScenes();
	}
	ImGui::End();

}

void SceneSelector::displayScenePanel(int ID, char c, std::string name)
{
	ImGui::PushID(ID);
	ImGui::Text("Scene %c", c);
	ImGui::Text("Name: %s", name);
	ImGui::Indent();
	if (ImGui::Button("Load Scene")) {
		SceneManager::get()->ViewScene(ID);
	}
	ImGui::SameLine();
	if (ImGui::Button("Unload Scene")) {
		SceneManager::get()->DeleteObjectsInScene(ID);
	}
	SceneLoadProgress* progress = SceneManager::get()->getProgressByID(ID);
	if (progress) {
		float bar = (float)progress->bytesReceived / (float)progress->totalBytes;
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, this->getColor(ID));
		ImGui::ProgressBar(bar, ImVec2(0.f, 0.f));
		ImGui::PopStyleColor();
	}
	ImGui::Unindent();
	ImGui::NewLine();
	ImGui::Separator();
	ImGui::PopID();

}

ImVec4 SceneSelector::getColor(int ID)
{
	ImVec4 color;
	switch (ID) {
		case 1: color = ImVec4(0.2f, 0.7f, 0.3f, 1.0f); break; //green
		case 2: color = ImVec4(0.2f, 0.4f, 0.9f, 1.0f); break; //blue
		case 3: color = ImVec4(0.9f, 0.9f, 0.4f, 1.0f); break; //yellow
		case 4: color = ImVec4(0.5f, 0.3f, 0.7f, 1.0f); break; //purple
		case 5: color = ImVec4(0.7f, 0.2f, 0.2f, 1.0f); break; //red
	}
	return color;
}
