/* Card.cpp */
#include "../card/Card.h"
#include "../buttons/Button.h"
#include "../text/Text.h"
#include "../fonts/Font.h"
#include "../constants/Colors.h"
#include "../constants/Constants.h"
#include "../tag/Tag.h"
#include <imgui.h>

namespace {
    ImVec4 WithAlpha(const ImVec4& c, float a) { return ImVec4(c.x, c.y, c.z, a); }

    struct CardTheme {
        ImVec4 background;
        ImVec4 pillBackground;
        ImVec4 pillText;
        ImVec4 titleColor;
        ImVec4 bodyColor;
        ButtonStyle buttonStyle;
        TagStyle tagStyle;
    };

    CardTheme GetTheme(CardStyle style) {
        if (style == CardStyle::Secondary) {
            return {
                Colors::PrimaryDarkColor,
                WithAlpha(Colors::White, 0.15f),
                WithAlpha(Colors::White, 0.80f),
                Colors::White,
                WithAlpha(Colors::White, 0.75f),
                ButtonStyle::Secondary,
                TagStyle::Ghost
            };
        }
        return {
            Colors::White,
            WithAlpha(Colors::PrimaryLightColor, 0.12f),
            Colors::PrimaryLightColor,
            Colors::PrimaryDarkColor,
            Colors::Gray,
            ButtonStyle::Primary,
            TagStyle::Primary
        };
    }

    constexpr float TagScale = 0.8f;
    constexpr float TagPadX = 12.0f;
    constexpr float TagPadY = 8.0f;
}

bool Card(const CardData& data, ImVec2 pos, ImVec2 size, CardStyle style, float marginX) {
    const CardTheme theme = GetTheme(style);
    bool clicked = false;

    pos.x += marginX;
    size.x -= marginX * 2.0f;

    ImGui::SetCursorPos(pos);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, theme.background);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 14.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    // heading doubles as the unique child ID
    ImGui::BeginChild(data.heading.c_str(), size, false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor();

    // Inner padding scales with the card width, which scales with the window
    const float k = TextScale();
    const float PadX = ImGui::GetWindowSize().x * Constants::CardPaddingX;

    // ---- Tag pill (shared Tag component: pill and text scale together) ----
    const float tagCenterY = 34.0f * k;
    ImVec2 tagSize = TagSize(data.tag, TagScale);

    Tag(data.tag,
        ImVec2(PadX, tagCenterY - tagSize.y * 0.5f),
        theme.tagStyle,
        TagScale);

    // ---- Heading --------------------------------------------------------
    ImVec2 posHeading = ImGui::GetCursorPos();
    posHeading.y += Constants::CardSpacing;
    Heading(data.heading, posHeading, PadX, 2.0f, theme.titleColor);

    // ---- Description ----------------------------------------------------
    ImVec2 posPara = ImGui::GetCursorPos();
    posPara.y += Constants::CardSpacing;

    Paragraph(data.description, posPara, PadX, 0.0f, Alignment::LEFT, theme.bodyColor);

    // ---- Button (pinned bottom-left) -------------------------------------
    ImGui::SetCursorPos(ImVec2(PadX, size.y - 70.0f));
    clicked = Button(data.buttonLabel.c_str(), theme.buttonStyle);

    ImGui::EndChild();

    ImGui::BeginChild(
        data.heading.c_str(),
        size,
        false,
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse
    );

    // Draw card boundary
    ImVec2 cardMin = ImGui::GetWindowPos();
    ImVec2 cardMax = ImVec2(
        cardMin.x + ImGui::GetWindowSize().x,
        cardMin.y + ImGui::GetWindowSize().y
    );

    ImGui::GetWindowDrawList()->AddRect(
        cardMin,
        cardMax,
        ImGui::ColorConvertFloat4ToU32(Colors::BorderColor),
        14.0f,
        0,
        1.0f
    );

    ImGui::EndChild();
    //ImGui::PopStyleVar(2);
    //ImGui::PopStyleColor();

    return clicked;
}
