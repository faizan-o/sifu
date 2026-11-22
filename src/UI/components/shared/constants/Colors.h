/* Colors.h */
#pragma once

#include <imgui.h>
#include <string>

namespace Colors{
	inline constexpr ImVec4 PrimaryLightColor = ImVec4(
		11.0f / 255.0f,
		129.0f / 255.0f,
		115.0f / 255.0f,
		1.0f
	);

	inline constexpr ImVec4 PrimaryDarkColor = ImVec4(
		23.0f / 255.0f,
		59.0f / 255.0f,
		51.0f / 255.0f,
		1.0f
	);

	inline constexpr ImVec4 White = ImVec4(
		255.0f / 255.0f,
		255.0f / 255.0f,
		255.0f / 255.0f,
		1.0f
	);

	inline constexpr ImVec4 WindowBackground = ImVec4(
		246.0f / 255.0f,
		245.0f / 255.0f,
		239.0f / 255.0f,
		1.0f
	);

	inline constexpr ImVec4 Secondary = ImVec4(
		243.0f / 255.0f,
		162.0f / 255.0f,
		11.0f / 255.0f,
		1.0f
	);

	inline constexpr ImVec4 Gray = ImVec4(
		98.0f / 255.0f,
		115.0f / 255.0f,
		106.0f / 255.0f,
		1.0f
	);

	inline constexpr ImVec4 BorderColor = ImVec4(
		98.0f / 255.0f,
		115.0f / 255.0f,
		106.0f / 255.0f,
		0.2f
	);

}

