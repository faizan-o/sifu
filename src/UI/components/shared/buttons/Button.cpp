/* Button.cpp */
#include "Button.h"
#include "../text/Text.h"
#include "../fonts/Font.h"
#include "../constants/Colors.h"
#include <imgui.h>

namespace {
    ImVec4 Shade(const ImVec4& c, float f) { return ImVec4(c.x * f, c.y * f, c.z * f, c.w); }
    ImVec4 WithAlpha(const ImVec4& c, float a) { return ImVec4(c.x, c.y, c.z, a); }

    // Padding and rounding are fractions of the font size, so the button keeps
    // the same proportions at any text size / window size.
    constexpr float PaddingXEm = 1.40f;
    constexpr float PaddingYEm = 0.70f;
    constexpr float RoundingEm = 0.55f;
}

bool Button(const char* label, ButtonStyle style, ImVec2 size) {
    ImVec4 bg, hover, active, text;

    switch (style) {
    case ButtonStyle::Primary:
        bg = Colors::PrimaryLightColor;
        hover = Shade(bg, 0.90f);
        active = Shade(bg, 0.80f);
        text = Colors::White;
        break;
    case ButtonStyle::Secondary:
        bg = Colors::Secondary;
        hover = Shade(bg, 0.92f);
        active = Shade(bg, 0.84f);
        text = Colors::PrimaryDarkColor;
        break;
    case ButtonStyle::Ghost:
    default:
        bg = WithAlpha(Colors::PrimaryDarkColor, 0.0f);
        hover = WithAlpha(Colors::PrimaryDarkColor, 0.08f);
        active = WithAlpha(Colors::PrimaryDarkColor, 0.16f);
        text = Colors::PrimaryDarkColor;
        break;
    }

    // Font first, so the padding below is based on the size the label is drawn at
    ImGui::SetWindowFontScale(TextScale());
    ImGui::PushFont(Font::Bold);

    const float em = ImGui::GetFontSize();

    ImGui::PushStyleColor(ImGuiCol_Button, bg);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, active);
    ImGui::PushStyleColor(ImGuiCol_Text, text);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, em * RoundingEm);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(em * PaddingXEm, em * PaddingYEm));

    bool clicked = ImGui::Button(label, size);

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(4);

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);

    return clicked;
}
