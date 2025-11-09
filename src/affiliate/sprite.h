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
    static Sprite* addSpriteChild(ObjectInScreen* parent,
                                  std::string_view filePath,
                                  float scale = 1.0f);

    virtual void init() override {};
    virtual void render() override;

    void scaleSize(float scale) { m_size *= scale; }

    Texture texture() const { return m_texture; }
    virtual void setTexture(const Texture& texture);

    float angle() const { return m_texture.angle; }
    void setAngle(float angle) { m_texture.angle = angle; }

    bool isFlipped() const { return m_texture.isFlipped; }
    void setFlipped(bool isFlipped) { m_texture.isFlipped = isFlipped; }

protected:
    Texture m_texture;
};
