/* HeroTextSection.cpp */

#include "./MainSection.h"
#include "../../../components/shared/text/Text.h"
#include "../../../components/shared/constants/Constants.h"
#include <algorithm>
#include <imgui.h>

void HeroTextSection()
{
    const float k = TextScale();

    ImVec2 reg = ImGui::GetWindowSize();

    ImVec2 size = ImVec2(
        reg.x * 0.5f,
        reg.y * Constants::OnBoardingHeroSectionHeight
    );

    ImVec2 start = ImGui::GetCursorPos();

    // Width available in this cell, measured before anything moves the cursor
    const float cellAvailX = ImGui::GetContentRegionAvail().x;

    float padX = Constants::OnBoardingHeroSectionPaddingScaler * size.x;
    float padY = Constants::OnBoardingHeroSectionPaddingScaler * size.y;

    float slotHeight = size.y / 4.0f;

    float headingVS = Constants::HeroHeadingVS * k;
    float paraVS = Constants::HeroParaVS * k;

    // ---- Tag line 1 -----------------------------------------------------
    ImVec2 posTagLine1 = start;
    posTagLine1.y += slotHeight * 0.5f;

    TagLine(
        Constants::HeroTextSectionTagLine1,
        posTagLine1,
        1.2f,
        padX,
        0.0f
    );

    // ---- Headings -------------------------------------------------------
    const float headingScale = 3.5f;

    float headingHeight = HeadingSize("Ag", headingScale).y;

    float headingGroupHeight = headingHeight * 2.0f + headingVS;

    float headingStartY =
        start.y + slotHeight +
        (slotHeight - headingGroupHeight) * 0.5f;

    ImVec2 posHeadingOne = start;
    posHeadingOne.y = headingStartY + headingHeight * 0.5f;

    Heading(
        Constants::OnBoardingHeroSectionHeading1,
        posHeadingOne,
        padX,
        headingScale
    );

    float heading1Width =
        HeadingSize(Constants::OnBoardingHeroSectionHeading1, headingScale).x;

    ImVec2 posHeadingTwo = posHeadingOne;
    posHeadingTwo.x += heading1Width + padX;

    Heading(
        Constants::OnBoardingHeroSectionHeading2,
        posHeadingTwo,
        0.0f,
        headingScale
    );

    ImVec2 posHeadingThree = start;
    posHeadingThree.y = posHeadingOne.y + headingHeight + headingVS;

    Heading(
        Constants::OnBoardingHeroSectionHeading3,
        posHeadingThree,
        padX,
        headingScale
    );

    // ---- Tag line 2 -----------------------------------------------------
    const float tagLine2Scale = 1.6f;

    ImVec2 posTagLine2 = start;
    posTagLine2.y = start.y + slotHeight * 2.5f;

    TagLine(
        Constants::HeroTextSectionTagLine2,
        posTagLine2,
        tagLine2Scale,
        padX,
        0.0f
    );

    // ---- Paragraphs (anchored to the bottom of the section) -------------
    // Measure both paragraphs as they will wrap, then place the block so its
    // bottom edge sits at the bottom of the section (level with the image).
    const float wrapWidth = cellAvailX - padX;
    const float lineH = ParagraphLineHeight();
    const float paraGap = ImGui::GetStyle().ItemSpacing.y * k;

    float para1H = ParagraphHeight(Constants::HeroTextSectionParagraph1, wrapWidth);
    float para2H = ParagraphHeight(Constants::HeroTextSectionParagraph2, wrapWidth);
    float blockH = para1H + paraGap + para2H;

    const float bottomPad = 0.0f * k;   // raise this to lift the text off the bottom edge

    float blockTop = start.y + size.y - bottomPad - blockH;

    // never climb into tag line 2
    float tagLine2Bottom =
        posTagLine2.y +
        TagLineSize(Constants::HeroTextSectionTagLine2, tagLine2Scale).y * 0.5f;
    blockTop = std::max(blockTop, tagLine2Bottom + headingVS);

    // Paragraph() positions by the vertical centre of its first line
    ImVec2 posPara1 = start;
    posPara1.y = blockTop * 0.93;

    float para1Height = Paragraph(
        Constants::HeroTextSectionParagraph1,
        posPara1,
        padX,
        0.0f,
        Alignment::LEFT
    );

    ImVec2 posPara2 = posPara1;
    posPara2.y += para1Height + paraGap;

    Paragraph(
        Constants::HeroTextSectionParagraph2,
        posPara2,
        padX,
        0.0f,
        Alignment::LEFT
    );

    ImGui::SetCursorPos(start);
    ImGui::Dummy(size);
}
