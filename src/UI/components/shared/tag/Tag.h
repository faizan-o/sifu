/* Tag.h */

#pragma once

#include <imgui.h>
#include <string>

enum class TagStyle
{
    Primary,    // light pill, green text
    Ghost       // translucent white pill, white text (for dark backgrounds)
};

// Size of the pill that Tag() will draw (text + scaled padding).
ImVec2 TagSize(const std::string& text, float scale = 1.0f);

// Draws a pill with text. `pos` is the pill's top-left in window-local coordinates.
// Text, padding and rounding all scale with the window. Returns the pill size.
ImVec2 Tag(
    const std::string& text,
    ImVec2 pos,
    TagStyle style = TagStyle::Primary,
    float scale = 1.0f
);
