#pragma once

#include <string>
#include <cstdint>
#include <cstddef>
#include <imgui.h>

using std::string;

class Image {
public:
	struct Texture
	{
		unsigned int id;
		int width = 0;
		int height = 0;
		int channels = 0;
	};

	static bool DrawImage(const std::string&, ImVec2, ImVec2 = ImVec2(0.0f, 0.0f), ImVec2 = ImVec2(0.0f, 0.0f));

	static void UnloadImage(const std::string&);
	static void ClearCache();

	static size_t GetCachedImageCount();

private:
	static Texture* LoadTexture(const std::string&);
};


