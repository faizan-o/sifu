/* Text.cpp */

#include "Text.h"
#include "../fonts/Font.h"
#include "../constants/Constants.h"
#include "../constants/Colors.h"
#include <algorithm>
#include <string>
#include <imgui.h>

using std::string;

float TextScale() {
    ImVec2 vp = ImGui::GetMainViewport()->Size;
    float sx = vp.x / Constants::BaseWindowWidth;
    float sy = vp.y / Constants::BaseWindowHeight;
    return std::clamp(std::min(sx, sy), 0.6f, 2.0f);
}

ImVec2 HeadingSize(const string& text, float scale) {
    ImGui::SetWindowFontScale(scale * TextScale());
    ImGui::PushFont(Font::Bold);

    ImVec2 size = ImGui::CalcTextSize(text.c_str());

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);
    return size;
}

ImVec2 TagLineSize(const string& text, float scale) {
    // Tags and headings both use the bold font at scale * TextScale()
    return HeadingSize(text, scale);
}

float ParagraphLineHeight() {
    ImGui::SetWindowFontScale(TextScale());
    ImGui::PushFont(Font::Regular);

    float h = ImGui::CalcTextSize("Ag").y;

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);
    return h;
}

float ParagraphHeight(const string& text, float wrapWidth) {
    ImGui::SetWindowFontScale(TextScale());
    ImGui::PushFont(Font::Regular);

    float h = ImGui::CalcTextSize(text.c_str(), nullptr, false, wrapWidth).y;

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);
    return h;
}


void Heading(string text, ImVec2 pos, float padding, float scale, ImVec4 color)
{
    const char* Title = text.c_str();

    ImGui::PushStyleColor(ImGuiCol_Text, color);

    ImGui::SetWindowFontScale(scale * TextScale());
    ImGui::PushFont(Font::Bold);

    ImVec2 titleSize = ImGui::CalcTextSize(Title);

    pos.x += padding;
    pos.y -= titleSize.y / 2.0f;

    ImGui::SetCursorPos(pos);
    ImGui::TextUnformatted(Title);

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleColor();
}

float Paragraph(string text, ImVec2 pos, float padX, float padY, Alignment alignment, ImVec4 color) {
    const char* textToRender = text.c_str();

    ImGui::PushStyleColor(ImGuiCol_Text, color);

    ImGui::SetWindowFontScale(TextScale());
    ImGui::PushFont(Font::Regular);

    ImVec2 paragraphTextSize = ImGui::CalcTextSize(textToRender);

    if (alignment == Alignment::RIGHT) {
        pos.x -= paragraphTextSize.x + padX;
    }
    else if (alignment == Alignment::LEFT) {
        pos.x += padX;
    }

    pos.y += padY;
    pos.y -= paragraphTextSize.y / 2.0f;

    ImGui::SetCursorPos(pos);

    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextUnformatted(textToRender);
    ImGui::PopTextWrapPos();

    // Height of what was actually drawn (counts wrapped lines)
    float renderedHeight = ImGui::GetItemRectSize().y;

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleColor();

    return renderedHeight;
}

void TagLine(string text, ImVec2 pos, float scale, float padX, float padY, ImVec4 color) {
    const char* charText = text.c_str();

    ImGui::PushStyleColor(ImGuiCol_Text, color);

    ImGui::SetWindowFontScale(scale * TextScale());
    ImGui::PushFont(Font::Bold);

    ImVec2 titleSize = ImGui::CalcTextSize(charText);

    pos.x += padX;
    pos.y += padY;

    pos.y -= titleSize.y / 2.0f;

    ImGui::SetCursorPos(pos);

    ImGui::TextUnformatted(charText);

    ImGui::PopFont();
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleColor();
}
