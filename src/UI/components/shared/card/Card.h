/* Card.h */
#pragma once

#include <string>
#include <imgui.h>

enum class CardStyle {
    Primary,    // white card, green button
    Secondary   // dark green card, yellow button
};

struct CardData {
    std::string tag;
    std::string heading;
    std::string description;
    std::string buttonLabel;

    CardData(std::string tag, std::string heading, std::string description, std::string buttonLabel)
        : tag(std::move(tag)), heading(std::move(heading)),
        description(std::move(description)), buttonLabel(std::move(buttonLabel)) {
    }
};

bool Card(const CardData& data, ImVec2 pos, ImVec2 size, CardStyle style, float marginX = 0.0f);
