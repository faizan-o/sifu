/* Font.cpp */

#include <imgui.h>
#include "Font.h"

namespace Font {

	ImFont* Bold = nullptr;
	ImFont* Medium = nullptr;
	ImFont* Regular = nullptr;

	void Initialize() {
		ImGuiIO& io = ImGui::GetIO();

		Regular = io.Fonts->AddFontFromFileTTF("assets/font/Inter_Regular.ttf", 18.0f);
		Medium = io.Fonts->AddFontFromFileTTF("assets/font/Inter_Medium.ttf", 18.0f);
		Bold = io.Fonts->AddFontFromFileTTF("assets/font/Inter_Bold.ttf", 18.0f);
	}
}
