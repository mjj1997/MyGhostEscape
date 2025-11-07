#include "sprite.h"

Texture::Texture(std::string_view filePath)
{
    texture = Game::instance().assetStorage()->getImage(filePath);
    SDL_GetTextureSize(texture, &srcRect.w, &srcRect.h);
}

Sprite* Sprite::addSpriteChild(ObjectInScreen* parent, std::string_view filePath, float scale)
{
    auto sprite{ new Sprite };
    sprite->init();
    sprite->setTexture(Texture{ filePath });
    sprite->setParent(parent);
    sprite->scaleSize(scale);

    parent->addChild(sprite);
    return sprite;
}

void Sprite::render()
{
    if (m_texture.texture == nullptr)
        return;

    if (m_parent == nullptr)
        return;

    auto pos{ m_parent->screenPosition() + m_offset };
    m_game.renderTexture(m_texture, pos, m_size); // 使得渲染操作同 Sprite 类解耦
}

void Sprite::setTexture(const Texture& texture)
{
    m_texture = texture;
    m_size = glm::vec2{ texture.srcRect.w, texture.srcRect.h };
}
