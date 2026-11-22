#include "OnBoardingFooter.h"
#include "../../../components/shared/constants/Constants.h"
#include "../../../components/shared/text/Text.h"

void OnBoardingFooter() {
	ImVec2 reg = ImGui::GetWindowSize();

	const ImVec2 start = ImGui::GetCursorPos();
	const float availX = ImGui::GetContentRegionAvail().x;

	const ImVec2 size(availX, reg.y * Constants::OnBoardingFooterHeight);

	const float padX = reg.x * 0.5f * Constants::OnBoardingHeroSectionPaddingScaler;

	//const float centerY = start.y + size.y * 0.5f;

	Paragraph(Constants::FooterSentence1, ImVec2(start.x, start.y+Constants::FooterTextMargin), padX, 0.0f, Alignment::LEFT);

	Paragraph(Constants::FooterSentence2, ImVec2(start.x + availX, start.y + Constants::FooterTextMargin), padX, 0.0f, Alignment::RIGHT);

	ImGui::SetCursorPos(start);
	ImGui::Dummy(size);
		
}