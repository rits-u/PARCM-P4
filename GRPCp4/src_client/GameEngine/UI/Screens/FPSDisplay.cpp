#include "FPSDisplay.h"
#include "../../GraphicsEngine/EngineTime.h"

FPSDisplay::FPSDisplay() : UIScreen("FPS Display", true)
{
}

FPSDisplay::~FPSDisplay()
{
}

void FPSDisplay::draw()
{
	if (this->activeSelf) {
        ImGui::Begin("FPS Counter", nullptr,
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoFocusOnAppearing);

        ImVec4 color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        ImGui::TextColored(color, "FPS: %.2f", EngineTime::getFPS());

        ImGui::End();
	}
}