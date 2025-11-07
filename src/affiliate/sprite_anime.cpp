#include "sprite_anime.h"

SpriteAnime* SpriteAnime::addSpriteAnimeChild(ObjectInScreen* parent,
                                              std::string_view filePath,
                                              float scale)
{
    auto spriteAnime{ new SpriteAnime };
    spriteAnime->init();
    spriteAnime->setTexture(Texture{ filePath });
    spriteAnime->setParent(parent);
    spriteAnime->scaleSize(scale);

    parent->addChild(spriteAnime);
    return spriteAnime;
}

void SpriteAnime::update(float deltaTime)
{
    m_frameTimer += deltaTime;
    if (m_frameTimer >= 1.0f / m_fps) {
        ++m_currentFrame;
        if (m_currentFrame >= m_totalFrames) {
            m_currentFrame = 0;
        }
        m_frameTimer = 0.0f;
    }
    m_texture.srcRect.x = m_currentFrame * m_texture.srcRect.w;
}

void SpriteAnime::setTexture(const Texture& texture)
{
    m_texture = texture;
    m_totalFrames = texture.srcRect.w / texture.srcRect.h;
    m_texture.srcRect.w = texture.srcRect.h;
    m_size = glm::vec2{ m_texture.srcRect.w, m_texture.srcRect.h };
}
