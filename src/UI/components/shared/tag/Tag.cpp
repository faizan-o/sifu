/* Tag.cpp */

#include "Tag.h"
#include "../text/Text.h"
#include "../constants/Colors.h"
#include "../fonts/Font.h"
#include <imgui.h>

namespace {
    ImVec4 WithAlpha(const ImVec4& c, float a) { return ImVec4(c.x, c.y, c.z, a); }

    // Padding and rounding are fractions of the text height, so the pill keeps the
    // same proportions at any text size / window size.
    constexpr float PaddingXEm = 0.90f;
    constexpr float PaddingYEm = 0.45f;
    constexpr float RoundingEm = 0.40f;

    struct TagMetrics {
        ImVec2 text;
        float padX;
        float padY;
        float rounding;
        ImVec2 size;
    };

    TagMetrics Measure(const std::string& text, float scale)
    {
        TagMetrics m;
        m.text = TagLineSize(text, scale);   // bold font, same scale as drawn

        m.padX = m.text.y * PaddingXEm;
        m.padY = m.text.y * PaddingYEm;
        m.rounding = m.text.y * RoundingEm;

        m.size = ImVec2(
            m.text.x + m.padX * 2.0f,
            m.text.y + m.padY * 2.0f
        );
        return m;
    }
}

ImVec2 TagSize(const std::string& text, float scale)
{
    return Measure(text, scale).size;
}

ImVec2 Tag(const std::string& text, ImVec2 pos, TagStyle style, float scale)
{
    const TagMetrics m = Measure(text, scale);

    ImVec4 background;
    ImVec4 foreground;

    if (style == TagStyle::Primary)
    {
        background = WithAlpha(Colors::PrimaryLightColor, 0.12f);
        foreground = Colors::PrimaryLightColor;
    }
    else
    {
        background = WithAlpha(Colors::White, 0.15f);
        foreground = WithAlpha(Colors::White, 0.85f);
    }

    // window-local -> screen space
    ImVec2 win = ImGui::GetWindowPos();
    ImVec2 screenMin(
        win.x + pos.x - ImGui::GetScrollX(),
        win.y + pos.y - ImGui::GetScrollY()
    );
    ImVec2 screenMax(screenMin.x + m.size.x, screenMin.y + m.size.y);

    ImGui::GetWindowDrawList()->AddRectFilled(
        screenMin, screenMax,
        ImGui::GetColorU32(background),
        m.rounding
    );

    // TagLine centers on pos.y, so pass the pill's vertical center
    TagLine(
        text,
        ImVec2(pos.x + m.padX, pos.y + m.size.y * 0.5f),
        scale,
        0.0f,
        0.0f,
        foreground
    );

    return m.size;
}
