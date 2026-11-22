/* OnBoardingScreen.cpp */

#include "OnBoardingScreen.h"
#include "OnBoardingHeader/OnBoardingHeader.h"
#include "OnBoardingFooter/OnBoardingFooter.h"
#include "MainSection/MainSection.h"
#include "../../components/shared/constants/Constants.h"

OnBoardingScreen::OnBoardingScreen(GLFWwindow* window)
{
	string window_name = Constants::Name + " - " + Constants::OnBoarding;
	BasicScreen(window_name, window);
	OnBoardingHeader();
	MainSection();
	OnBoardingFooter();
	EndBasicScreen();
}

