/* MainSection.cpp */

#include "MainSection.h"
#include "../../../components/shared/constants/Constants.h"
#include "../../../components/shared/image/Image.h"

void MainSection() {

	ImVec2 reg = ImGui::GetWindowSize();
	ImVec2 size = ImVec2(reg.x, reg.y * Constants::OnBoardingMainSectionHeight);

	const CardData c1 = CardData(
		"FOR TEACHERS",
		"Design Mode",
		"Turn your knowledge into lessons that come alive. Build, preview, and share your own interactive decks.",
		"Create interactive lessons >"
	);

	const CardData c2 = CardData(
		"FOR LEARNERS", 
		"Study Mode",
		"Learn by doing, not just reading. Explore lessons, try new ideas, and celebrate every breakthrough.",
		"Start exploring >"
	);

	if (ImGui::BeginTable(Constants::MainSectionTable.c_str(), 2, ImGuiTableFlags_SizingStretchSame)) {
		ImGui::TableNextRow(ImGuiTableRowFlags_None, size.y * Constants::OnBoardingHeroSectionHeight);

		ImGui::TableNextColumn();
		HeroTextSection();

		ImGui::TableNextColumn();
		ImVec2 imgSize = ImVec2(size.x * 0.5f, size.y);
		Image::DrawImage("assets/images/primary.png", imgSize, ImVec2(0.0f, Constants::OnBoardingHeroSectionPaddingScaler));


		ImGui::TableNextRow(ImGuiTableRowFlags_None, size.y * Constants::OnBoardingCardSectionHeight);
		float cardH = reg.y * Constants::OnBoardingCardSectionHeight;

		ImGui::TableNextColumn();
		if (Card(c1, ImGui::GetCursorPos(), ImVec2(ImGui::GetContentRegionAvail().x, cardH), CardStyle::Primary, size.x * Constants::HeroCardMarginMultiplier)) {
			// open design mode
		}

		ImGui::TableNextColumn();
		if (Card(c2, ImGui::GetCursorPos(), ImVec2(ImGui::GetContentRegionAvail().x, cardH), CardStyle::Secondary, size.x * Constants::HeroCardMarginMultiplier)) {
		}

		ImGui::EndTable();
	}
}