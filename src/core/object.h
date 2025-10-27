#pragma once

#include "game.h"

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;

protected:
    Game& m_game{ Game::instance() };
};
