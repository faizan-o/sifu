#include "BasicScreen.h"
#include "../components//shared/constants/Colors.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

/*
- Header 1 Part
- Footer 1 Part
- Main Section 8 Parts
    - Hero 5 Parts
    - Card 3 Parts
*/

void BasicScreen(string name, GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(
        static_cast<float>(width),
        static_cast<float>(height)
    ));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::PushStyleColor(
        ImGuiCol_WindowBg,
        Colors::WindowBackground
    );

    ImGui::Begin(
        name.c_str(),
        nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoScrollbar
    );
}

void EndBasicScreen() {
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}
