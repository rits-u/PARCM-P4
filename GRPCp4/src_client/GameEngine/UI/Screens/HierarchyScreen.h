#pragma once
#include "../UIScreen.h"

#include "../../GameObject/GameObjectManager.h"

class HierarchyScreen : public UIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();

	void draw() override;
};

