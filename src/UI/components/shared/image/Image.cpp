/* Image.cpp */

#include "Image.h"

#include <imgui.h>
#include <glad/gl.h>

#include <unordered_map>
#include <iostream>
#include <cstdint>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace
{
    std::unordered_map<std::string, Image::Texture> g_TextureCache;
}

Image::Texture* Image::LoadTexture(const std::string& path)
{
    // Return cached texture if already loaded.
    auto it = g_TextureCache.find(path);

    if (it != g_TextureCache.end())
        return &it->second;

    int width = 0;
    int height = 0;
    int channels = 0;

    // Load image from disk.
    stbi_set_flip_vertically_on_load(false);

    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        0
    );

    if (!data)
    {
        std::cerr << "[ImageUtils] Failed to load: "
            << path << std::endl;

        return nullptr;
    }

    GLenum format = GL_RGBA;

    switch (channels)
    {
    case 1:
        format = GL_RED;
        break;

    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;

    default:
        std::cerr << "[ImageUtils] Unsupported channel count: "
            << channels << std::endl;

        stbi_image_free(data);
        return nullptr;
    }

    GLuint textureID = 0;

    GLint previousTexture = 0;
    GLint previousUnpackAlignment = 0;

    glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousUnpackAlignment);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE
    );

    glBindTexture(GL_TEXTURE_2D, previousTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, previousUnpackAlignment);

    stbi_image_free(data);

    Texture texture;
    texture.id = textureID;
    texture.width = width;
    texture.height = height;
    texture.channels = channels;

    auto result = g_TextureCache.emplace(path, texture);

    std::cout << "[ImageUtils] Loaded: "
        << path << std::endl;

    return &result.first->second;
}

bool Image::DrawImage(const std::string& path, ImVec2 size, ImVec2 padX, ImVec2 padY)
{
    if (path.empty() || size.x <= 0.0f || size.y <= 0.0f)
        return false;

    Texture* texture = LoadTexture(path);

    if (!texture)
        return false;


    float imgWidth = static_cast<float>(texture->width);
    float imgHeight = static_cast<float>(texture->height);

    const ImVec2 areaSize = size;

    const float paddingLeft = areaSize.x * padX.x;
    const float paddingRight = areaSize.x * padX.y;
    const float paddingTop = areaSize.y * padY.x;
    const float paddingBottom = areaSize.y * padY.y;

    const ImVec2 innerSize(
        areaSize.x - paddingLeft - paddingRight,
        areaSize.y - paddingTop - paddingBottom
    );

    if (innerSize.x <= 0.0f || innerSize.y <= 0.0f)
        return false;

    const float scale = std::min(
        innerSize.x / imgWidth,
        innerSize.y / imgHeight
    );

    const ImVec2 drawSize(
        imgWidth * scale,
        imgHeight * scale
    );

    ImVec2 areaPos = ImGui::GetCursorScreenPos();

    const ImVec2 imagePos(
        areaPos.x + paddingLeft + (innerSize.x - drawSize.x) * 0.5f,
        areaPos.y + paddingTop + (innerSize.y - drawSize.y) * 0.5f
    );

    ImGui::GetWindowDrawList()->AddImage(
        (ImTextureID)(intptr_t)texture->id,
        imagePos,
        ImVec2(
            imagePos.x + drawSize.x,
            imagePos.y + drawSize.y
        )
    );

    ImGui::Dummy(areaSize);

    return true;
}

void Image::UnloadImage(const std::string& path)
{
    auto it = g_TextureCache.find(path);

    if (it == g_TextureCache.end())
        return;

    glDeleteTextures(1, &it->second.id);

    g_TextureCache.erase(it);
}

void Image::ClearCache()
{
    for (auto& pair : g_TextureCache)
    {
        glDeleteTextures(1, &pair.second.id);
    }

    g_TextureCache.clear();
}

size_t Image::GetCachedImageCount()
{
    return g_TextureCache.size();
}