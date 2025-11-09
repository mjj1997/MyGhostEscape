#pragma once

#include "sprite.h"

class SpriteAnime : public Sprite
{
public:
    static SpriteAnime* addSpriteAnimeChild(ObjectInScreen* parent,
                                            std::string_view filePath,
                                            float scale = 1.0f);

    virtual void update(float deltaTime) override;

    virtual void setTexture(const Texture& texture) override;

    int currentFrame() const { return m_currentFrame; }
    void setCurrentFrame(int frame) { m_currentFrame = frame; }

    int totalFrames() const { return m_totalFrames; }
    void setTotalFrames(int frames) { m_totalFrames = frames; }

    int fps() const { return m_fps; }
    void setFps(int fps) { m_fps = fps; }

    float frameTimer() const { return m_frameTimer; }
    void setFrameTimer(float frameTimer) { m_frameTimer = frameTimer; }

private:
    int m_currentFrame{ 0 };
    int m_totalFrames{ 0 };
    int m_fps{ 10 };
    float m_frameTimer{ 0.0f };
};
