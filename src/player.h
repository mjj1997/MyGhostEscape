#pragma once

#include "core/actor.h"

class SpriteAnime;

class Player : public Actor
{
public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;

    void keyboardControl();
    void move(float deltaTime);
    void syncCamera();
    void checkState();

private:
    SpriteAnime* m_spriteIdle{ nullptr };
    SpriteAnime* m_spriteMove{ nullptr };
};
