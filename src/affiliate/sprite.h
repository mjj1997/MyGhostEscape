#pragma once

#include "../core/object_affiliated.h"

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

class Sprite : public ObjectAffiliated
{
public:
    Sprite() = default;

    virtual void init() override {};
    virtual void render() override;

    Texture texture() const { return m_texture; }
    virtual void setTexture(const Texture& texture);

protected:
    Texture m_texture;
};
