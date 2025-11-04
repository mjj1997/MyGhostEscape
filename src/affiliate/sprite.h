#pragma once

#include <string_view>

struct Texture
{
    Texture() = default;
    explicit Texture(std::string_view filePath);

    SDL_Texture* texture{ nullptr };
    SDL_FRect srcRect{ 0.0f, 0.0f, 0.0f, 0.0f };
    float angle{ 0.0f };
    bool isFlipped{ false };
};
