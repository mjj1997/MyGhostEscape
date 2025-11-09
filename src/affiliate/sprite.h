#pragma once

#include "../core/object_affiliated.h"

#include <string_view>

struct Texture
{
    Texture() = default;
    explicit Texture(std::string_view filePath);

    float angle() const { return m_angle; }
    void setAngle(float angle) { m_angle = angle; }

    bool isFlipped() const { return m_isFlipped; }
    void setFlipped(bool isFlipped) { m_isFlipped = isFlipped; }

    SDL_Texture* texture{ nullptr };
    SDL_FRect srcRect{ 0.0f, 0.0f, 0.0f, 0.0f };
    float m_angle{ 0.0f };
    bool m_isFlipped{ false };
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

protected:
    Texture m_texture;
};
