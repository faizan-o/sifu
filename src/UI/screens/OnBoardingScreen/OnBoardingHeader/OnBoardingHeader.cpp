#include "./OnBoardingHeader.h"

#include "../../../components/shared/constants/Colors.h"
#include "../../../components/shared/constants/Constants.h"
#include "../../../components/shared/fonts/Font.h"
#include "../../../components/shared/text/Text.h"

void OnBoardingHeader() {
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 reg = ImGui::GetWindowSize();
    ImVec2 size = ImVec2(
        reg.x,
        reg.y * Constants::OnBoardingHeaderHeight
    );

    ImDrawList* draw = ImGui::GetWindowDrawList();

    draw->AddRectFilled(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::ColorConvertFloat4ToU32(Colors::White),
        0.0f
    );

    float padding = size.x * Constants::DefaultHeaderScreenPaddingScaler;


    ImVec2 titlePos = ImVec2(
        ImGui::GetCursorPosX(),
        size.y / 2.0f
    );

    Heading(Constants::Name, titlePos, padding, 2.0f);


    ImGui::SameLine();

    const ImVec2 paraSize = ImGui::CalcTextSize(Constants::OnBoardingHeaderText.c_str());

    ImVec2 paraPosition = ImVec2(
        reg.x, 
        size.y / 2.0f
    );


    Paragraph(Constants::OnBoardingHeaderText, paraPosition, padding, 0.0f, Alignment::RIGHT);
    ImGui::SetCursorPos(ImVec2(0, size.y));
    ImGui::Dummy(size);
};

