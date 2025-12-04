#pragma once
#include "../UIScreen.h"

class FPSDisplay : public UIScreen
{
public:
	FPSDisplay();
	~FPSDisplay();

	void draw() override;
};

