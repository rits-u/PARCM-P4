#pragma once
#include "../GameEngine/WindowingSystem/Window.h"
#include "../GameEngine/GraphicsEngine/GraphicsEngine.h"
#include "../GameEngine/GraphicsEngine/RenderSystem/SwapChain.h"
#include "../GameEngine/InputSystem/InputListener.h"
#include "../GameEngine/Camera/Camera.h"
#include "../GameEngine/UI/UIManager.h"
#include "../GameEngine/GameObject/GameObjectManager.h"
#include "../GameEngine/GameObject/Types.h"
#include "../GameEngine/SceneManager/SceneManager.h"

#include <iostream>
#include <vector>
#include <random>

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mousePos) override;
	virtual void onLeftMouseDown(const Point& mousePos) override;
	virtual void onLeftMouseUp(const Point& mousePos) override;
	virtual void onRightMouseDown(const Point& mousePos) override;
	virtual void onRightMouseUp(const Point& mousePos) override;

private:
	void createCamera(Layer layer, float depth, bool enabled);


private:
	SwapChainPtr m_swap_chain;
	bool holding = false;
	std::vector<Camera*> sortedCameras;

};

