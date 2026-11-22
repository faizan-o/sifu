/* Constants.h */
#pragma once

#include <imgui.h>
#include <string>

using std::string;

namespace Constants {
	inline const string Name = "Fractal";
	inline const string OnBoarding = "OnBoarding";
	inline const string OnBoardingHeaderText = "Interactive Learning, Learn Beautifully";


	inline const float DefaultHeadingScalar = 2.0f;
	inline constexpr float DefaultHeaderScreenPaddingScaler = 1.0f / 12.0f;

	inline constexpr float OnBoardingHeaderHeight = 1.0f / 10.0f;
	inline constexpr float OnBoardingMainSectionHeight = 8.0f / 10.0f;
	inline constexpr float OnBoardingHeroSectionHeight = 5.0f / 8.0f;
	inline constexpr float OnBoardingCardSectionHeight = 3.0f / 8.0f;
	inline constexpr float OnBoardingFooterHeight = 1.0f / 7.0f;

	inline constexpr float OnBoardingHeroSectionPaddingScaler = 1.0f / 16.0f;
	inline const float HeroParaVS = 50.0f;
	inline const float HeroHeadingVS = 0.0f;
	inline constexpr float HeroCardMarginMultiplier = 1.0f / 40.0f;
	inline constexpr float CardPaddingX = 1.0f / 20.0f;

	inline const string MainSectionTable = "MainSectionTable";
	inline const string OnBoardingHeroSectionHeading1 = "Learn.";
	inline const string OnBoardingHeroSectionHeading2 = "Create.";
	inline const string OnBoardingHeroSectionHeading3 = "Explore.";
	inline const string HeroTextSectionTagLine1 = "A LITTLE CURIOSITY. LIMITLESS POSSIBILITY.";
	inline const string HeroTextSectionTagLine2 = "Big Ideas Start With A Little Discovery.";
	inline const string HeroTextSectionParagraph1 = "Create interactive lessons or explore the world through them.";
	inline const string HeroTextSectionParagraph2 = "A free learning space for curious minds and inspiring teachers.";

	inline const float BaseWindowWidth = 1100.0f;
	inline const float BaseWindowHeight = 800.0f;

	inline const float CardSpacing = 50.0f;
	inline const float FooterTextMargin = 50.0f;

	inline const string FooterSentence1 = "Free By Design. Yours To Discover.";
	inline const string FooterSentence2 = "Create Locally · Learn At Your Own Pace · No Subscription";


}

