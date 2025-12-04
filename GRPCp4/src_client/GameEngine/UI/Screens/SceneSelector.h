#pragma once
#include "../UIScreen.h"
#include "../UIManager.h"
#include "../UINames.h"
#include "../../GameObject/GameObjectManager.h"


class SceneLoader;
class GameObjectManager;

class SceneSelector : public UIScreen
{
public:
	SceneSelector();
	~SceneSelector();

	void draw() override;

private:
	void displayScenePanel(int ID, char c, std::string name);
	ImVec4 getColor(int ID);
};

