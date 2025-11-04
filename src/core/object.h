#pragma once

#include "defs.h"
#include "game.h"

#include <vector>

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

    virtual void addChild(Object* child) { m_children.push_back(child); }
    virtual void removeChild(Object* child)
    {
        m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    }

    ObjectType type() const { return m_type; }
    void setType(ObjectType type) { m_type = type; }

protected:
    Game& m_game{ Game::instance() };
    ObjectType m_type{ ObjectType::None };

    std::vector<Object*> m_children;
};
