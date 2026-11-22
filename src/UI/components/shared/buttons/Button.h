/* Button.h */
#pragma once

#include <imgui.h>

enum class ButtonStyle {
    Ghost,      // transparent, dark text
    Primary,    // green
    Secondary   // yellow
};

bool Button(const char* label, ButtonStyle style = ButtonStyle::Primary, ImVec2 size = ImVec2(0, 0));