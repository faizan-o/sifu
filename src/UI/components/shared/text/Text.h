/* Text.h */
#pragma once

#include <string>
#include <imgui.h>
#include "../constants/Constants.h"
#include "../constants/Colors.h"

enum class Alignment {
	LEFT,
	RIGHT
};

float TextScale();

ImVec2 HeadingSize(const std::string& text, float scale);
ImVec2 TagLineSize(const std::string& text, float scale);
float  ParagraphLineHeight();
float  ParagraphHeight(const std::string& text, float wrapWidth);


void Heading(std::string text, ImVec2 pos, float padding, float scale, ImVec4 color = Colors::PrimaryDarkColor);

float Paragraph(std::string text, ImVec2 pos, float padX, float padY, Alignment alignment, ImVec4 color = Colors::Gray);

void TagLine(std::string text, ImVec2 pos, float scale, float padX, float padY, ImVec4 color = Colors::PrimaryLightColor);
