#pragma once

#include "defs.h"
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

    ObjectType type() const { return m_type; }
    void setType(ObjectType type) { m_type = type; }

protected:
    Game& m_game{ Game::instance() };
    ObjectType m_type{ ObjectType::None };
};
