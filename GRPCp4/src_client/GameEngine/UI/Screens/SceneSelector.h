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
	//void toggleUIScreen(String name);
	//SceneLoader* loader;
	float myColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

};

