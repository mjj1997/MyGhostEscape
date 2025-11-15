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
    virtual void handleEvents(SDL_Event& event);
    virtual void update(float deltaTime);
    virtual void render();
    virtual void clean();

    virtual void addChild(Object* child) { m_children.push_back(child); }
    virtual void removeChild(Object* child)
    {
        m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    }

    ObjectType type() const { return m_type; }
    void setType(ObjectType type) { m_type = type; }

    bool isActive() const { return m_isActive; }
    void setActive(bool isActive) { m_isActive = isActive; }

    bool isNeedRemoved() const { return m_isNeedRemoved; }
    void setNeedRemoved(bool isNeedRemoved) { m_isNeedRemoved = isNeedRemoved; }

protected:
    Game& m_game{ Game::instance() };
    ObjectType m_type{ ObjectType::None };
    bool m_isActive{ true };
    bool m_isNeedRemoved{ false };

    std::vector<Object*> m_children;
};
